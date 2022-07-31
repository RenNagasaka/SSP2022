#include <BrilHistogram.cpp>
#include <iostream>
#include <vector>

class DummyHistogramGenerator {

 public:
  std::vector<uint32_t> generate_headers();
  std::vector<uint32_t> generate_counters_random();
  std::vector<uint32_t> generate_counters_single_bin(int bin_id);
  std::vector<uint32_t> Random();
  std::vector<uint32_t> SingleBin(int bin_id);
};

