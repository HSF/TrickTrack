#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tricktrack/RiemannFit.h"

using namespace tricktrack;

TEST_CASE("RiemannFit methods", "[interface]") {


  constexpr unsigned int nhits = 4;
   


  Matrix3xNd riemannHits = Matrix3xNd::Zero(3,nhits);
  /// xyz coordinates for each hits in the columns 
  riemannHits.col(0) << 1, 0, 0;
  riemannHits.col(1) << 0, 1, 1;
  riemannHits.col(2) << -1, 0, 2;
  riemannHits.col(3) <<  0, -1, 3;

  Matrix3Nd hits_cov = Matrix3Nd::Random(3*nhits,3*nhits);
  auto h = Helix_fit(riemannHitshits, hits_cov, 1);
  std::cout << "charge " << h.q << std::endl;
  std::cout << "chi_2 circle " << h.chi2_circle << std::endl;
  std::cout << "chi_2 line " << h.chi2_line << std::endl;
  std::cout << "par " << h.par << std::endl; 
  

}
