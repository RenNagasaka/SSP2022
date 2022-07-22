#include </home/rnagasak/myproject/Data_Generate/GenerateDummyHistogram.cpp>
#include <iostream>
#include <vector>

int main(){
  
  DummyHistogramGenerator *mydata;
  std::vector<uint32_t> data = mydata->Random();

  BrilHistogram *myHist = new BrilHistogram (data);
  std::cout << (uint32_t) myHist->GetHeaderSize() << std::endl;

  return 0;
}
