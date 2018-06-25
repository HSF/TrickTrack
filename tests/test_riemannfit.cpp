#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tricktrack/RiemannFit.h"
#include "tricktrack/Logger.h"

using namespace tricktrack;

TEST_CASE("RiemannFit method - Perfect Helix", "[integration]") {


  constexpr unsigned int nhits = 4;
   
   SECTION(" Fitting 4 points sampled from almost perfect helix ") {


    Matrix3xNd riemannHits = Matrix3xNd::Random(3,nhits);
    /// xyz coordinates for each hits in the columns 
    riemannHits.col(0) << 1., 0.0, -0.000001;
    riemannHits.col(1) << 0.000001, 1., 1.;
    riemannHits.col(2) << -1., 0.0, 2.;
    riemannHits.col(3) <<  0.001, -1, 3;

    Matrix3Nd hits_cov = Matrix3Nd::Identity(3*nhits,3*nhits);
    auto h = Helix_fit(riemannHits, hits_cov, 1, true, false);
    TT_INFO("parameters: ",  h.par);

   /* TT_INFO("charge " << h.q );
    TT_INFO("chi_2 circle " << h.chi2_circle );
    TT_INFO("chi_2 line " << h.chi2_line );
    TT_INFO("par " << h.par ); */

    REQUIRE(h.par(1) == Approx(1));
    

   }
   SECTION(" Fitting 4 points sampled from perfect helix ") {

    Matrix3xNd riemannHits = Matrix3xNd::Random(3,nhits);
    /// xyz coordinates for each hits in the columns 
    riemannHits.col(0) << 1., 0.0, 0.0;
    riemannHits.col(1) << 0.0, 1., 1.;
    riemannHits.col(2) << -1., 0.0, 2.;
    riemannHits.col(3) <<  0, -1, 3;

    Matrix3Nd hits_cov = Matrix3Nd::Identity(3*nhits,3*nhits);
    auto h = Helix_fit(riemannHits, hits_cov, 1, true, false);
    std::cout << "parameters " <<  h.par << std::endl;
    std::cout << "charge " << h.q << std::endl;
    std::cout << "chi_2 circle " << h.chi2_circle << std::endl;
    std::cout << "chi_2 line " << h.chi2_line << std::endl;
    std::cout << "par " << h.par << std::endl; 
    //REQUIRE(h.par(1) == Approx(1));


   }
  

}
