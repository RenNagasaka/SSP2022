#include </home/rnagasak/myproject/bril_histogram/components/bril_histogram/software/src/BrilHistogram.cpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <iterator>
#include <bitset>
#include <cstdlib>
#include <math.h>


std::vector<uint32_t> generate_counters () {
  std::vector<uint32_t> counters;

  int N_bunch = 3564;
  for (int i=0; i<N_bunch/2+1; ++i)
    {
      int RANDOM_1 = rand()%201;
      int RANDOM_2 = rand()%201;

      counters.push_back((RANDOM_1 << 16) | (RANDOM_2 << 0));
    }

  return counters;
}

std::vector<uint32_t> generate_vector () {
  uint16_t TOTAL_PACKAGE_SIZE = 1792;
  uint8_t HEADER_SIZE = 9;
  uint16_t HISTOGRAM_TYPE = rand()%64;
  uint16_t HISTOGRAM_ID = rand()%1024;
  uint16_t N_BINS = 3564;
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

  result.push_back((Counter_Overflow << 32) | (Increment_Overflow << 31) | (0 << 20) | (ORBIT_COUNTER << 0));

  result.push_back((LHC_Fill << 0));

  result.push_back((CMS_Run_Number << 0));

  result.push_back((Lumi_Section << 0));

  result.push_back((Lumi_Nibble << 0));

  result.push_back((NUMBER_OF_WORDS_PER_ERROR << 24) | (NUMBER_OF_UNITS << 16) | (NUMBER_OF_MASK_AND_ERROR_WORDS << 0));

  // now counters                                                                                                                                                     
  std::vector<uint32_t> counters = generate_counters();
  result.insert(result.end(), counters.begin(), counters.end());

  // return                                                                                                                                                           
  return result;
}

int main(){

  std::vector<uint32_t> Data;
  Data = generate_vector();

  BrilHistogram *myHist = new BrilHistogram (Data);

  //std::cout << (std::vector<uint32_t>) myHist->GetDataRaw() << std::endl;                                                                                           
  std::cout << "NwordsTotal = " << (uint16_t) myHist->GetNwordsTotal() << std::endl;
  std::cout << "HeaderSize = " << (int) myHist->GetHeaderSize() << std::endl;
  std::cout << "Nbins = " << (uint16_t) myHist->GetNbins() << std::endl;
  std::cout << "Nunits = " << (uint16_t) myHist->GetNunits() << std::endl;
  std::cout << "NcounterWords = " << (uint16_t) myHist->GetNcounterWords() << std::endl;
  std::cout << "IncrementWidth = " << (int) myHist->GetIncrementWidth() << std::endl;
  std::cout << "CounterWidth = " << (uint8_t) myHist->GetCounterWidth() << std::endl;
  std::cout << "NwordsPerError = " << (uint8_t) myHist->GetNwordsPerError() << std::endl;
  std::cout << "HistogramID = " << (uint16_t) myHist->GetHistogramID() << std::endl;
  std::cout << "HistogramType = " << (uint16_t) myHist->GetHistogramType() << std::endl;
  std::cout << "LhcFill = " << (uint32_t) myHist->GetLhcFill() << std::endl;
  std::cout << "CmsRun = " << (uint32_t) myHist->GetCmsRun() << std::endl;
  std::cout << "LumiSection = " << (uint32_t) myHist->GetLumiSection() << std::endl;
  std::cout << "LumiNibble = " << (uint32_t) myHist->GetLumiNibble() << std::endl;
  std::cout << "OrbitCounter = " << (uint32_t) myHist->GetOrbitCounter() << std::endl;
  std::cout << "CounterOverflow = " << (bool) myHist->GetCounterOverflow() << std::endl;
  std::cout << "IncrementOverflow = " << (bool) myHist->GetIncrementOverflow() << std::endl;
  std::cout << "NmaskErrorWords = " << (uint16_t) myHist->GetNmaskErrorWords() << std::endl;


  return 0;
}
