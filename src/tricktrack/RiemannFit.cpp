#include "tricktrack/RiemannFit.h"

namespace tricktrack {

helix_fit Helix_fit(const Matrix3xNd& hits, const Matrix3Nd& hits_cov, const double& B,
                    const bool& error, const bool& scattering) {
  u_int n = hits.cols();
  VectorNd rad = (hits.block(0, 0, 2, n).colwise().norm());

  // Fast_fit gives back (X0, Y0, R, theta) w/o errors, using only 3 points.
  const Vector4d fast_fit = Fast_fit(hits);

  circle_fit circle = Circle_fit(hits.block(0, 0, 2, n), hits_cov.block(0, 0, 2 * n, 2 * n),
                                 fast_fit, rad, error, scattering);

  const line_fit line = Line_fit(hits, hits_cov, circle, fast_fit, error);

  par_uvrtopak(circle, B, error);

  helix_fit helix;
  helix.par << circle.par, line.par;
  if (error) {
    helix.cov = MatrixXd::Zero(5, 5);
    helix.cov.block(0, 0, 3, 3) = circle.cov;
    helix.cov.block(3, 3, 2, 2) = line.cov;
  }
  helix.q = circle.q;
  helix.chi2_circle = circle.chi2;
  helix.chi2_line = line.chi2;

  return helix;
}

line_fit Line_fit(const Matrix3xNd& hits, const Matrix3Nd& hits_cov, const circle_fit& circle,
                  const Vector4d& fast_fit, const bool& error) {
  u_int n = hits.cols();
  // PROJECTION ON THE CILINDER
  Matrix2xNd p2D(2, n);
  MatrixNx5d Jx(n, 5);

  // x & associated Jacobian
  // cfr https://indico.cern.ch/event/663159/contributions/2707659/attachments/1517175/2368189/Riemann_fit.pdf
  // Slide 11
  // a ==> -o i.e. the origin of the circle in XY plane, negative
  // b ==> p i.e. distances of the points wrt the origin of the circle.
  const Vector2d o(circle.par(0), circle.par(1));
  for (u_int i = 0; i < n; ++i) {  // x
    Vector2d p = hits.block(0, i, 2, 1) - o;
    const double cross = cross2D(-o, p);
    const double dot = (-o).dot(p);
    // atan2(cross, dot) give back the angle in the transverse plane so tha the final equation reads:
    // x_i = -q*R*theta (theta = angle returned by atan2)
    const double atan2_ = -circle.q * atan2(cross, dot);
    p2D(0, i) = atan2_ * circle.par(2);

    // associated Jacobian, used in weights and errors computation
    const double temp0 = -circle.q * circle.par(2) * 1. / (sqr(dot) + sqr(cross));
    double d_X0 = 0, d_Y0 = 0, d_R = 0.;  // good approximation for big pt and eta
    if (error) {
      d_X0 = - temp0 * ((p(1) + o(1)) * dot - (p(0) - o(0)) * cross);
      d_Y0 = temp0 * ((p(0) + o(0)) * dot - (o(1) - p(1)) * cross);
      d_R = atan2_;
    }
    const double d_x = temp0 * (o(1) * dot + o(0) * cross);
    const double d_y = temp0 * (-o(0) * dot + o(1) * cross);
    Jx.row(i) << d_X0, d_Y0, d_R, d_x, d_y;
  }
  // Math of d_{X0,Y0,R,x,y} all verified by hand

  // y
  p2D.row(1) = hits.row(2);


  // WEIGHT COMPUTATION
  VectorNd x_err2 = X_err2(hits_cov, circle, Jx, error, n);
  VectorNd y_err2 = hits_cov.block(2 * n, 2 * n, n, n).diagonal();

  const VectorNd err2_inv = Weight_line(x_err2, y_err2, fast_fit(3));
  const VectorNd weight = err2_inv * 1. / err2_inv.sum();
  // COST FUNCTION

  // compute
  // r0 represents the weighted mean of "x" and "y".
  const Vector2d r0 = p2D * weight;
  // This is the X  vector that will be used to build the
  // scatter matrix S = X^T * X
  const Matrix2xNd X = p2D.colwise() - r0;
  Matrix2d A = Matrix2d::Zero();
  for (u_int i = 0; i < n; ++i) {
    A += err2_inv(i) * (X.col(i) * X.col(i).transpose());
  }
  // minimize
  double chi2;
  Vector2d v = min_eigen2D(A, chi2);
  // n *= (chi2>0) ? 1 : -1; //TO FIX
  const double c = -v.transpose() * r0;

  // COMPUTE LINE PARAMETER
  line_fit line;
  line.par << -v(0) / v(1),                          // cotan(theta))
      -c * sqrt(sqr(v(0)) + sqr(v(1))) * 1. / v(1);  // Zip
  line.chi2 = abs(chi2);

  // ERROR PROPAGATION
  if (error) {
    const double v0_2 = sqr(v(0));
    const double v1_2 = sqr(v(1));

    Matrix3d C;  // cov(v,c)
    {
      double norm_chernov = 0.;
      for (u_int i = 0; i < n; ++i)
        norm_chernov += err2_inv(i) * (v(0) * p2D(0, i) + v(1) * p2D(1, i) + c)
          * (v(0) * p2D(0, i) + v(1) * p2D(1, i) + c);
      norm_chernov /= float(n);
      // Indeed it should read:
      // * compute the average error in the orthogonal direction: err2_inv.cwiseInverse().sum()/sqr(n)
      // * normalize the A(0,0)+A(1,1) dividing by err2_inv.sum(), since those have been weighted
      const double norm = (err2_inv.cwiseInverse().sum())*err2_inv.sum()*1./sqr(n);
      const double sig2 = 1./(A(0,0) + A(1,1))*norm;
//      const double sig2 = 1. / (A(0, 0) + A(1, 1));
      C(0, 0) = sig2 * v1_2;
      C(1, 1) = sig2 * v0_2;
      C(0, 1) = C(1, 0) = -sig2 * v(0) * v(1);
      const VectorNd weight_2 = (weight).array().square();
      const Vector2d C0(weight_2.dot(x_err2), weight_2.dot(y_err2));
      C.block(0, 2, 2, 1) = C.block(2, 0, 1, 2).transpose() = -C.block(0, 0, 2, 2) * r0;
      C(2, 2) = v0_2 * C0(0) + v1_2 * C0(1) + C0(0) * C(0, 0) + C0(1) * C(1, 1) +
                (r0.transpose() * C.block(0, 0, 2, 2) * r0);
    }

    Matrix<double, 2, 3> J;  // Jacobian of (v,c) -> (cotan(theta)),Zip)
    {
      const double t0 = 1. / v(1);
      const double t1 = sqr(t0);
      const double sqrt_ = sqrt(v1_2 + v0_2);
      const double t2 = 1. / sqrt_;
      J << -t0, v(0) * t1, 0, -c * v(0) * t0 * t2, v0_2 * c * t1 * t2, -sqrt_ * t0;
    }

    line.cov = J * C * J.transpose();
  }

  return line;
}

} // namespace tricktrack
