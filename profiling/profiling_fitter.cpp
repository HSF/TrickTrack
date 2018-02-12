#include <cstdio>
#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>


#include "tricktrack/RiemannFit.h"

using namespace tricktrack;

int main() {

  for( unsigned int nhits = 3; nhits < 8; ++nhits) {

   

    Matrix3Nd hits_cov = Matrix3Nd::Identity(3*nhits,3*nhits);


    std::vector<double> durations;
  for (int i = 0; i < 200; ++i) {
    std::vector<Vector5d> res;
    res.reserve(2000);
		Matrix3xNd riemannHits = Matrix3xNd::Identity(3, nhits) * 30. +  Matrix3xNd::Random(3,nhits);
			/// xyz coordinates for each hits in the columns 
    constexpr double rep = 2000;
		std::clock_t startcputime = std::clock();
    for (int j = 0; j < rep; ++j) {
		auto h = Helix_fit(riemannHits, hits_cov, 1, false, false);
    //res.push_back(h.par);

     }
		double cpu_duration = (std::clock() - startcputime) / rep / (double)CLOCKS_PER_SEC;
    durations.push_back(cpu_duration);
    std::cout << nhits << "\t" << cpu_duration << std::endl; 

	}
  double average = std::accumulate( durations.begin(), durations.end(), 0.0)/durations.size(); 
  }

  return 0;
}
