#include <BrilHistogram.cpp>
#include <iostream>
#include <vector>
#include <math.h>

class DummyHistogramGenerator {

 public:
  std::vector<uint32_t> generate_headers();
  std::vector<uint32_t> generate_counters_random();
  std::vector<uint32_t> generate_counters_single_bin();
  std::vector<uint32_t> Random();
  std::vector<uint32_t> SingleBin();
};

