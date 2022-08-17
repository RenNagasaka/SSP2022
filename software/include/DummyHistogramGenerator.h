#include <BrilHistogram.cpp>
#include <iostream>
#include <vector>

class DummyHistogramGenerator {

 public:
  std::vector<uint32_t> generate_headers();
  std::vector<uint32_t> generate_counters_random();
  std::vector<uint32_t> generate_counters_single_bin(int bin_id, uint16_t bin_height);
  std::vector<uint32_t> Random();
  std::vector<uint32_t> SingleBin(int bin_id, uint16_t bin_height);
  std::vector<uint32_t> generate_albedo(std::vector<uint32_t> vector, double a,double b,int n);
  std::vector<uint32_t> Random_albedo(double a, double b, int n);
  std::vector<uint32_t> SingleBin_albedo(double a, double b, int n, int bin_id, uint16_t bin_height);
};

