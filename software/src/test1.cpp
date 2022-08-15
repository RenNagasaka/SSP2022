#include "DummyHistogramGenerator.cpp"
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
  
  DummyHistogramGenerator *mydata;
  std::vector<uint32_t> data = mydata->SingleBin_albedo(0.1, 1, 30);
 
  BrilHistogram *myHist = new BrilHistogram (data);

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
