#ifndef TRICKTRACK_RIEMANNFIT_H
#define TRICKTRACK_RIEMANNFIT_H

#include <Eigen/Core>
#include <Eigen/Eigenvalues>

using namespace std;

namespace tricktrack {

using namespace Eigen;

constexpr double d = 1.e-4;         //!< used in numerical derivative (J2 in Circle_fit())
constexpr unsigned int max_nop = 8;  //!< In order to avoid use of dynamic memory

using MatrixNd = Eigen::Matrix<double, Dynamic, Dynamic, 0, max_nop, max_nop>;
using ArrayNd = Eigen::Array<double, Dynamic, Dynamic, 0, max_nop, max_nop>;
using Matrix2Nd = Eigen::Matrix<double, Dynamic, Dynamic, 0, 2 * max_nop, 2 * max_nop>;
using Matrix3Nd = Eigen::Matrix<double, Dynamic, Dynamic, 0, 3 * max_nop, 3 * max_nop>;
using Matrix2xNd = Eigen::Matrix<double, 2, Dynamic, 0, 2, max_nop>;
using Array2xNd = Eigen::Array<double, 2, Dynamic, 0, 2, max_nop>;
using Matrix3xNd = Eigen::Matrix<double, 3, Dynamic, 0, 3, max_nop>;
using MatrixNx3d = Eigen::Matrix<double, Dynamic, 3, 0, max_nop, 3>;
using MatrixNx5d = Eigen::Matrix<double, Dynamic, 5, 0, max_nop, 5>;
using VectorNd = Eigen::Matrix<double, Dynamic, 1, 0, max_nop, 1>;
using Vector2Nd = Eigen::Matrix<double, Dynamic, 1, 0, 2 * max_nop, 1>;
using Vector3Nd = Eigen::Matrix<double, Dynamic, 1, 0, 3 * max_nop, 1>;
using RowVectorNd = Eigen::Matrix<double, 1, Dynamic, 1, 1, max_nop>;
using RowVector2Nd = Eigen::Matrix<double, 1, Dynamic, 1, 1, 2 * max_nop>;
using Matrix5d = Eigen::Matrix<double, 5, 5>;
using Matrix6d = Eigen::Matrix<double, 6, 6>;
using Vector5d = Eigen::Matrix<double, 5, 1>;
using u_int    = unsigned int;

struct circle_fit {
  Vector3d par;  //!< parameter: (X0,Y0,R)
  Matrix3d cov;
  /*!< covariance matrix: \n
      |cov(X0,X0)|cov(Y0,X0)|cov( R,X0)| \n
      |cov(X0,Y0)|cov(Y0,Y0)|cov( R,Y0)| \n
      |cov(X0, R)|cov(Y0, R)|cov( R, R)|
  */
  int q;  //!< particle charge
  double chi2;
};

struct line_fit {
  Vector2d par;  //!<(cotan(theta),Zip)
  Matrix2d cov;
  /*!<
      |cov(c_t,c_t)|cov(Zip,c_t)| \n
      |cov(c_t,Zip)|cov(Zip,Zip)|
  */
  double chi2;
};

struct helix_fit {
  Vector5d par;  //!<(phi,Tip,pt,cotan(theta)),Zip)
  Matrix5d cov;
  /*!< ()->cov() \n
      |(phi,phi)|(Tip,phi)|(p_t,phi)|(c_t,phi)|(Zip,phi)| \n
      |(phi,Tip)|(Tip,Tip)|(p_t,Tip)|(c_t,Tip)|(Zip,Tip)| \n
      |(phi,p_t)|(Tip,p_t)|(p_t,p_t)|(c_t,p_t)|(Zip,p_t)| \n
      |(phi,c_t)|(Tip,c_t)|(p_t,c_t)|(c_t,c_t)|(Zip,c_t)| \n
      |(phi,Zip)|(Tip,Zip)|(p_t,Zip)|(c_t,Zip)|(Zip,Zip)|
  */
  int q;  //!< particle charge
  double chi2_circle;
  double chi2_line;
  Vector4d fast_fit;
  VectorXd time;  // TO FIX just for profiling
};


/*!
    \brief A very fast helix fit: it fits a circle by three points (first, middle
    and last point) and a line by two points (first and last).

    \param hits points to be fitted

    \return result in this form: (X0,Y0,R,tan(theta)).

    \warning points must be passed ordered (from internal layer to external) in
    order to maximize accuracy and do not mistake tan(theta) sign.

    \details This fast fit is used as pre-fit which is needed for:
    - weights estimation and chi2 computation in line fit (fundamental);
    - weights estimation and chi2 computation in circle fit (useful);
    - computation of error due to multiple scattering.
*/

Vector4d Fast_fit(const Matrix3xNd& hits);

/*!
    \brief Fit a generic number of 2D points with a circle using Riemann-Chernov
    algorithm. Covariance matrix of fitted parameter is optionally computed.
    Multiple scattering (currently only in barrel layer) is optionally handled.

    \param hits2D 2D points to be fitted.
    \param hits_cov2D covariance matrix of 2D points.
    \param fast_fit pre-fit result in this form: (X0,Y0,R,tan(theta)).
    (tan(theta) is not used).
    \param error flag for error computation.
    \param scattering flag for multiple scattering

    \return circle circle_fit:
    -par parameter of the fitted circle in this form (X0,Y0,R); \n
    -cov covariance matrix of the fitted parameter (not initialized if
    error = false); \n
    -q charge of the particle; \n
    -chi2.

    \warning hits must be passed ordered from inner to outer layer (double hits
    on the same layer must be ordered too) so that multiple scattering is
    treated properly.
    \warning Multiple scattering for barrel is still not tested.
    \warning Multiple scattering for endcap hits is not handled (yet). Do not
    fit endcap hits with scattering = true !

    \bug for small pt (<0.3 Gev/c) chi2 could be slightly underestimated.
    \bug further investigation needed for error propagation with multiple
    scattering.
*/

circle_fit Circle_fit(const Matrix2xNd& hits2D, const Matrix2Nd& hits_cov2D,
                      const Vector4d& fast_fit, VectorNd const & rad,
                      const bool& error = true,
                      const bool& scattering = false);



/*!
    \brief Fit of helix parameter cotan(theta)) and Zip by projection on the
    pre-fitted cylinder  and line fit on its surface.

    \param hits hits coordinates.
    \param hits_cov covariance matrix of the hits.
    \param circle cylinder parameter, their covariance (if computed, otherwise
    uninitialized) and particle charge.
    \param fast_fit result of the previous fast fit in this form:
    (X0,Y0,R,cotan(theta))).
    \param error flag for error computation.

    \return line line_fit:
    -par parameter of the line in this form: (cotan(theta)), Zip); \n
    -cov covariance matrix of the fitted parameter; \n
    -chi2.

    \warning correlation between R and z are neglected, this could be relevant
    if geometry detector provides sloped modules in the R/z plane.

    \bug chi2 and errors could be slightly underestimated for small eta (<0.2)
    when pt is small (<0.3 Gev/c).

    \todo multiple scattering treatment.

    \details Line fit is made by orthogonal distance regression where
    correlation between coordinates in the transverse plane (x,y) and z are
    neglected (for a barrel + endcap geometry this is a very good
    approximation).
    Covariance matrix of the fitted parameter is optionally computed.
    Multiple scattering is not handled (yet).
    A fast pre-fit is performed in order to evaluate weights and to compute
    errors.
*/

line_fit Line_fit(const Matrix3xNd& hits, const Matrix3Nd& hits_cov, const circle_fit& circle,
                  const Vector4d& fast_fit, const bool& error = true);

/*!
    \brief Helix fit by three step:
    -fast pre-fit (see Fast_fit() for further info); \n
    -circle fit of hits projected in the transverse plane by Riemann-Chernov
        algorithm (see Circle_fit() for further info); \n
    -line fit of hits projected on cylinder surface by orthogonal distance
        regression (see Line_fit for further info). \n
    Points must be passed ordered (from inner to outer layer).

    \param hits Matrix3xNd hits coordinates in this form: \n
        |x0|x1|x2|...|xn| \n
        |y0|y1|y2|...|yn| \n
        |z0|z1|z2|...|zn|

    \param hits_cov Matrix3Nd covariance matrix in this form (()->cov()): \n

   |(x0,x0)|(x1,x0)|(x2,x0)|.|(y0,x0)|(y1,x0)|(y2,x0)|.|(z0,x0)|(z1,x0)|(z2,x0)| \n
   |(x0,x1)|(x1,x1)|(x2,x1)|.|(y0,x1)|(y1,x1)|(y2,x1)|.|(z0,x1)|(z1,x1)|(z2,x1)| \n
   |(x0,x2)|(x1,x2)|(x2,x2)|.|(y0,x2)|(y1,x2)|(y2,x2)|.|(z0,x2)|(z1,x2)|(z2,x2)| \n
       .       .       .    .    .       .       .    .    .       .       .     \n
   |(x0,y0)|(x1,y0)|(x2,y0)|.|(y0,y0)|(y1,y0)|(y2,x0)|.|(z0,y0)|(z1,y0)|(z2,y0)| \n
   |(x0,y1)|(x1,y1)|(x2,y1)|.|(y0,y1)|(y1,y1)|(y2,x1)|.|(z0,y1)|(z1,y1)|(z2,y1)| \n
   |(x0,y2)|(x1,y2)|(x2,y2)|.|(y0,y2)|(y1,y2)|(y2,x2)|.|(z0,y2)|(z1,y2)|(z2,y2)| \n
       .       .       .    .    .       .       .    .    .       .       .     \n
   |(x0,z0)|(x1,z0)|(x2,z0)|.|(y0,z0)|(y1,z0)|(y2,z0)|.|(z0,z0)|(z1,z0)|(z2,z0)| \n
   |(x0,z1)|(x1,z1)|(x2,z1)|.|(y0,z1)|(y1,z1)|(y2,z1)|.|(z0,z1)|(z1,z1)|(z2,z1)| \n
   |(x0,z2)|(x1,z2)|(x2,z2)|.|(y0,z2)|(y1,z2)|(y2,z2)|.|(z0,z2)|(z1,z2)|(z2,z2)|

   \param B magnetic field in the center of the detector in Gev/cm/c
   unit, in order to perform pt calculation.
   \param error flag for error computation.
   \param scattering flag for multiple scattering treatment.
   (see Circle_fit() documentation for further info).

   \warning see Circle_fit(), Line_fit() and Fast_fit() warnings.

   \bug see Circle_fit(), Line_fit() and Fast_fit() bugs.
*/

helix_fit Helix_fit(const Matrix3xNd& hits, const Matrix3Nd& hits_cov, const double& B,
                    const bool& error = true, const bool& scattering = false);

} // namespace tricktrack

#endif /* TRICKTRACK_RIEMANNFIT_H */
