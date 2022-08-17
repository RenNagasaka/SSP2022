#include "../include/DummyHistogramGenerator.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

  //generate headers
std::vector<uint32_t> DummyHistogramGenerator::generate_headers () {
    uint16_t TOTAL_PACKAGE_SIZE = 1836;
    uint8_t HEADER_SIZE = 9;
    uint16_t HISTOGRAM_TYPE = rand()%64;
    uint16_t HISTOGRAM_ID = rand()%1024;
    uint16_t N_BINS = 3654;
    uint8_t INCREMENT_WIDTH = 1;
    uint8_t COUNTER_WIDTH = 100;
    uint16_t N_COUNTER_WORDS = rand()%65536;
    uint16_t NUMBER_OF_MASK_AND_ERROR_WORDS = 100;
    bool Counter_Overflow = 0;
    bool Increment_Overflow = 0;
    uint16_t NUMBER_OF_UNITS = rand()%256;
    uint8_t NUMBER_OF_WORDS_PER_ERROR = 100;
    uint32_t ORBIT_COUNTER = 1000;
    uint32_t LHC_Fill = rand()%(int)pow(2,32);
    uint32_t CMS_Run_Number = rand()%(int)pow(2,32);
    uint32_t Lumi_Section = rand()%(int)pow(2,32);
    uint32_t Lumi_Nibble = rand()%(int)pow(2,32);
    int N_bunch = 3654;
    std::vector<uint32_t> result;

    result.push_back((0xFF << 24) | (HEADER_SIZE << 16) | (TOTAL_PACKAGE_SIZE << 0));
    result.push_back((HISTOGRAM_TYPE << 26) | (HISTOGRAM_ID << 16) | (N_BINS << 0));
    result.push_back((COUNTER_WIDTH << 24) | (INCREMENT_WIDTH << 16) | (N_COUNTER_WORDS << 0));
    result.push_back((Counter_Overflow << 31) | (Increment_Overflow << 30) | (0 << 20) | (ORBIT_COUNTER << 0));
    result.push_back((LHC_Fill << 0));
    result.push_back((CMS_Run_Number << 0));
    result.push_back((Lumi_Section << 0));
    result.push_back((Lumi_Nibble << 0));
    result.push_back((NUMBER_OF_WORDS_PER_ERROR << 24) | (NUMBER_OF_UNITS << 16) | (NUMBER_OF_MASK_AND_ERROR_WORDS << 0));

    return result;
  }
  // generate counter payload at random number ranging [0,200]
std::vector<uint32_t> DummyHistogramGenerator::generate_counters_random () {
    std::vector<uint32_t> counters;
    int N_bunch = 3654;

    for (int i=0; i<N_bunch/2; ++i)
      {
        int RANDOM_1 = rand()%201;
        int RANDOM_2 = rand()%201;

        counters.push_back((RANDOM_1 << 16) | (RANDOM_2 << 0));
      }
    return counters;
  }
  // generate counter payload at single bin
std::vector<uint32_t> DummyHistogramGenerator::generate_counters_single_bin (int bin_id, uint16_t bin_height) {
    std::vector<uint32_t> counters;
    int N_bunch = 3654;

    for (int i=0; i<N_bunch/2; ++i)
      {
        if (i == bin_id/2)
          {
            if (bin_id%2 == 0)
              {
                counters.push_back((0 << 16) | (bin_height << 0));
              }
            else
              {
                counters.push_back((bin_height << 16) | (0 << 0));
              }
          }
        else
          {
            counters.push_back((0 << 16) | (0 << 0));
          }
      }
    return counters;
  }

  // combine headers and random counter payload
std::vector<uint32_t> DummyHistogramGenerator::Random(){                                     
    std::vector<uint32_t> counters = generate_counters_random();
    std::vector<uint32_t> result = generate_headers();

    result.insert(result.end(), counters.begin(), counters.end());
    return result;
  }
  // combine headers and single bin counter payload
std::vector<uint32_t> DummyHistogramGenerator::SingleBin(int bin_id=rand()%(3564), uint16_t bin_height = 1){
  std::vector<uint32_t> counters = generate_counters_single_bin(bin_id, bin_height);
    std::vector<uint32_t> result = generate_headers();

    result.insert(result.end(), counters.begin(), counters.end());
    return result;
  }
// generate albedo vector

std::vector<uint32_t> DummyHistogramGenerator::generate_albedo(std::vector<uint32_t> vector, double a, double b, int n)
{
  int N_bunch = 3654;
  std::vector<uint32_t> vector_albedo;
  double bin1;
  double bin2;
  double x1;
  double x2;
  int m;
  int l;

  for (int i=0; i<vector.size(); ++i)
    {
      bin1 = 0;
      bin2 = 0;
      for (int j=0; j<n/2; ++j)
      	{
	  m = (N_bunch+i-j-1)%(N_bunch/2);
	  l = (N_bunch+i-j-1)%(N_bunch/2);
      	  x1 = ((vector[m] >> 16) & (0xFFFF));
      	  x2 = ((vector[l] >> 0) & (0xFFFF));
	  bin1 = bin1 + x1*a*exp(-b*(2*j)) + x2*a*exp(-b*(2*j+1));

	  m = (N_bunch+i-j)%(N_bunch/2);
          l = (N_bunch+i-j-1)%(N_bunch/2);
          x1 = ((vector[m] >> 0) & (0xFFFF));
      	  x2 = ((vector[l] >> 16) & (0xFFFF));
	  bin2 = bin2 + x1*a*exp(-b*(2*j)) + x2*a*exp(-b*(2*j+1));
      	} 

      vector_albedo.push_back(((int)bin2 << 16) | ((int)bin1 << 0));
    }

  return vector_albedo;
}

  // combine headers and random counter payload with albedo
std::vector<uint32_t> DummyHistogramGenerator::Random_albedo(double a, double b, int n){                                     
    std::vector<uint32_t> counters = generate_counters_random();
    std::vector<uint32_t> result = generate_headers();
    std::vector<uint32_t> albedo = generate_albedo(counters, a, b, n);

    std::transform(counters.begin(), counters.end(), albedo.begin(), counters.begin(), std::plus<uint32_t>());
    result.insert(result.end(), counters.begin(), counters.end());
    return result;
  }
  // combine headers and single bin counter payload with albedo
std::vector<uint32_t> DummyHistogramGenerator::SingleBin_albedo(double a, double b, int n, int bin_id=rand()%(3564+1), uint16_t bin_height = 1){
  std::vector<uint32_t> counters = generate_counters_single_bin(bin_id, bin_height);
    std::vector<uint32_t> result = generate_headers();
    std::vector<uint32_t> albedo = generate_albedo(counters, a, b, n);

    std::transform(counters.begin(), counters.end(), albedo.begin(), counters.begin(), std::plus<uint32_t>());
    result.insert(result.end(), counters.begin(), counters.end());
    return result;
  }
