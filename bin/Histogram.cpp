// Mykyta Haranko, BRIL, CERN
// BrilHistogram decoder class

// includes
#include </home/rnagasak/myproject/bril_histogram/components/bril_histogram/software/include/BrilHistogram.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <iterator>
#include <bitset>
#include <cstdlib>
#include <math.h>

////
// class
////
BrilHistogram::BrilHistogram (std::vector<uint32_t> pDataRaw): fDataRaw(pDataRaw) {
  try {
    // basic check of the header
    if ( ((fDataRaw.at(0) >> 24) & 0xff) != 0xff ) {
      throw "Frame header mismatch";
    }
    // check of the vector size
    if ( GetNwordsTotal() != fDataRaw.size() ) {
      throw "Vector size mismatch";
    }
  } 
  catch (const char *str) {
    std::cout << "Init exception: " << str << ", header : " << std::hex << fDataRaw.at(0) << ", vector size : " << fDataRaw.size() << std::dec << std::endl;
    exit(1);
  }
}

////
// get methods
//// 

// get list of masked units (modules, chips, etc)
const std::vector<uint16_t> BrilHistogram::GetMaskedUnits() {

	// create the vector
	std::vector<uint16_t> cMaskedUnitsList;

	// check that we have masks and errors
	if (GetNmaskErrorWords() > 0) {
		try {
			// get position of thr mask in raw vector
			uint16_t cMaskOffset = GetHeaderSize() + GetNcounterWords();
			uint16_t cMaskNwords = GetNwordsPerError();

			// check mask header
			if ( ((fDataRaw.at(cMaskOffset) >> 28) & 0xF) != 0xA ) {
				throw "Mask header mismatch";
			}

			// initial iteration parameters
			uint16_t cCurrentWord = cMaskOffset;
			uint8_t cCurrentBitOffset = 27;

			// iterate over units
			for (uint16_t cUnit = GetNunits(); cUnit > 0; cUnit--) {
				// make sure that we are not exceeding the vector length
				if (cCurrentWord > (cMaskOffset+cMaskNwords-1)) {
					throw "Out of mask range";
				}

				// parse unit bit
				if ( ((fDataRaw.at(cCurrentWord) >> cCurrentBitOffset) & 0x1) == 0x1 ) {
					cMaskedUnitsList.push_back(cUnit-1);
				}

				// update word and offset
				if (cCurrentBitOffset > 0) cCurrentBitOffset -= 1;
				else {
					cCurrentBitOffset = 31;
					cCurrentWord += 1;
				}
			}
		}
		catch (const char *str) {
			std::cout << "Mask parsing exception: " << str << std::endl;
			exit(1);
		}
	
	} 

	// return the list
	return cMaskedUnitsList;

}

// parse errors
const std::vector<BrilHistogramError> BrilHistogram::GetErrors() {

	// create the vector
	std::vector<BrilHistogramError> cErrorList;

	// check that we have errors (GetNwordsPerError() stands for one mask Nwords)
	if (GetNmaskErrorWords() > GetNwordsPerError()) {
		try {
			// get position of thr error in raw vector
			uint16_t cErrorOffset = GetHeaderSize() + GetNcounterWords() + GetNwordsPerError();
			uint16_t cNerrors = (GetNmaskErrorWords() / GetNwordsPerError()) - 1;

			// iterate over errors
			for (uint16_t cErrorId = 0; cErrorId < cNerrors; cErrorId++) {

				// initial iteration parameters
				uint16_t cCurrentWord = cErrorOffset + cErrorId*GetNwordsPerError();

				// check error header
				if ( ((fDataRaw.at(cCurrentWord) >> 28) & 0xF) != 0x5 ) {
					throw "Error header mismatch";
				}

				// parse orbit and bx counter
				uint32_t cOrbitCounter = ((fDataRaw.at(cCurrentWord) >> 12) & 0xFFFF);
				uint32_t cBxCounter = (((fDataRaw.at(cCurrentWord) >> 0) & 0xFFF) << 4) | ((fDataRaw.at(cCurrentWord+1) >> 28) & 0xF);
				std::vector<uint16_t> cUnitList;			
				
				// current bit offset
				cCurrentWord += 1;
				uint8_t cCurrentBitOffset = 27;

				// iterate over units
				for (uint16_t cUnit = GetNunits(); cUnit > 0; cUnit--) {
					// make sure that we are not exceeding the vector length
					if (cCurrentWord > fDataRaw.size()-1) {
						throw "Out of vector range";
					}

					// parse unit bit
					if ( ((fDataRaw.at(cCurrentWord) >> cCurrentBitOffset) & 0x1) == 0x1 ) {
						cUnitList.push_back(cUnit-1);
					}

					// update word and offset
					if (cCurrentBitOffset > 0) cCurrentBitOffset -= 1;
					else {
						cCurrentBitOffset = 31;
						cCurrentWord += 1;
					}
				}

				// create error object
				BrilHistogramError cError(cOrbitCounter, cBxCounter, cUnitList);

				// push it to the vector
				cErrorList.push_back(cError);

			} // end cError id loop
		} 
		catch (const char *str) {
			std::cout << "Error parsing exception: " << str << std::endl;
			exit(1);
		}
	
	} // end if n mask error words

	// return the list
	return cErrorList;

}

// and finally parse counters
const std::vector<uint32_t> BrilHistogram::GetCounters() {

	// vector for counters
	std::vector<uint32_t> cCounters;

	// counter offset (come immidiately after header data)
	uint16_t cCurrentWord = GetHeaderSize();
	uint16_t cCounterLastWord = GetHeaderSize() + GetNcounterWords() - 1;
	
	try {
		// now depending on the counter width parse
		if (GetCounterWidth() <= 16) {
			while (cCurrentWord <= cCounterLastWord) {
				cCounters.push_back((fDataRaw.at(cCurrentWord) >> 0) & 0xFFFF);
				cCounters.push_back((fDataRaw.at(cCurrentWord) >> 16) & 0xFFFF);
				cCurrentWord += 1;
			}
		} else if (GetCounterWidth() <= 32) {
			while (cCurrentWord <= cCounterLastWord) {
				cCounters.push_back(fDataRaw.at(cCurrentWord));
				cCurrentWord += 1;
			}
		} else {
			throw "Wrong counter width - has to be <= 32";
		}

		// check length of the resulting vector
		if ( cCounters.size() != GetNbins() ) {
			throw "Resulting counter vector is smaller than Nbins";
		}
	}
	catch (const char *str) {
		std::cout << "Counter parsing exception: " << str << std::endl;
		exit(1);
	}

	// return
	return cCounters;

}

void BrilHistogram::UpdateTCDSInfo(uint32_t pLhcFill, uint32_t pCmsRun, uint32_t pLumiSection, uint32_t pLumiNibble) {
    fDataRaw.at(4) = pLhcFill;
    fDataRaw.at(5) = pCmsRun;
    fDataRaw.at(6) = pLumiSection;
    fDataRaw.at(7) = pLumiNibble;
}
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

int  main()
{

  std::vector<uint32_t> data;
  data = generate_vector();

  BrilHistogram *myHist = new BrilHistogram (data);

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
 
  /* for (int i=0; i<data.size(); ++i)
     {
     std::cout << data[i] << std::endl;
     }

     std::cout << "" << std::endl;
     std::cout << data.size() << std::endl;
  */
  return 0;
}
