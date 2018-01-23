#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tricktrack/RiemannFit.h"

using namespace tricktrack;

TEST_CASE("RiemannFit methods", "[interface]") {

  double a1 = 4.;

   

  REQUIRE(a1*a1 == sqr(a1));


  Matrix3xNd hits = Matrix3xNd::Random(3,3);
  /*
  hits << 0.0, 0.0, 0.0,
          1.0, 0.0, 0.0,
          2.0, 0.0, 0.0;
          */
  Matrix3Nd hits_cov = Matrix3Nd::Random(9,9);
  auto h = Helix_fit(hits, hits_cov, 1);
  std::cout << "charge " << h.q << std::endl;
  std::cout << "chi_2 circle " << h.chi2_circle << std::endl;
  std::cout << "chi_2 line " << h.chi2_line << std::endl;
  std::cout << "par " << h.par << std::endl; 
  

}
