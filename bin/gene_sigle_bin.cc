#include <vector>
#include <iostream>
#include <stdlib.h>
#include <iterator>
#include <bitset>
#include <cstdlib>
#include <math.h>


/* define function generating binary random number [0,N] in vector format
void random_binary(std::vector<int>& v, int& N, int n, int m)
{
  int k = rand()%(N+1);
  for (int i=n; i<m; ++i)
    {
      int l = k/int(pow(2,m-1-i));
      v.push_back(l%2);
    }
}
*/

// define function converting decimal number N to binary in vector format 
void generate_binary_vector(std::vector<int>& v, int& N, int n, int m)
{
  for (int i=n; i<m; ++i)
    {
      int l = N/int(pow(2,m-1-i));
      v.push_back(l%2);
    }
}



int main()
{
  int TOTAL_PACKAGE_SIZE = 65535;
  int HEADER_SIZE = 200;// for now
  int HISTOGRAM_TYPE = rand()%64;
  int HISTOGRAM_ID = rand()%1024;
  int N_BINS = 3564;//for now
  int INCREMENT_WIDTH = 0;// 
  int COUNTER_WIDTH = 100;// for now
  int N_COUNTER_WORDS = rand()%65536;
  int NUMBER_OF_MASK_AND_ERROR_WORDS = 100;
  int Counter_Overflow = 0;
  int Increment_Overflow = 0;
  int NUMBER_OF_UNITS = rand()%256;
  int NUMBER_OF_WORDS_PER_ERROR = 100;
  int ORBIT_COUNTER = 1000;//for now
  int LHC_Fill = rand()%(int)pow(2,32);
  int CMS_Run_Number = rand()%(int)pow(2,32);
  int Lumi_Section = rand()%(int)pow(2,32);
  int Lumi_Nibble = rand()%(int)pow(2,32);

  std::vector<std::vector<int> > Data;

  int Word_Number;
  int N_bunch = 3654;

  std::vector<std::vector<int> > Header;
  Header.push_back(std::vector<int>());

  //Word #0
  Word_Number = 0;
  Header.push_back(std::vector<int>());
  generate_binary_vector(Header[Word_Number], TOTAL_PACKAGE_SIZE, 0, 16);
  generate_binary_vector(Header[Word_Number], HEADER_SIZE, 16, 24);
  int all_1 = 255;//all 1
  generate_binary_vector(Header[Word_Number], all_1, 24, 32);

  //Word #1
  Word_Number = 1;
  Header.push_back(std::vector<int>());
  generate_binary_vector(Header[Word_Number], N_BINS, 0, 16);
  generate_binary_vector(Header[Word_Number], HISTOGRAM_ID, 16, 26);
  generate_binary_vector(Header[Word_Number], HISTOGRAM_TYPE, 26, 32);

  //Word #2
  Word_Number = 2;
  Header.push_back(std::vector<int>());
  generate_binary_vector(Header[Word_Number], N_COUNTER_WORDS, 0, 16);
  generate_binary_vector(Header[Word_Number], INCREMENT_WIDTH, 16, 24);
  generate_binary_vector(Header[Word_Number], COUNTER_WIDTH, 24, 32);

  //Word #3
  Word_Number = 3;
  Header.push_back(std::vector<int>());
  generate_binary_vector(Header[Word_Number], ORBIT_COUNTER, 0, 20);
  int all_0 = 0;//Nan
  generate_binary_vector(Header[Word_Number], all_0, 20, 30);
  generate_binary_vector(Header[Word_Number], Counter_Overflow, 30, 31);
  generate_binary_vector(Header[Word_Number], Increment_Overflow, 31, 32);

  //Word #4 LHC Fill
  Word_Number = 4;
  Header.push_back(std::vector<int>());
  generate_binary_vector(Header[Word_Number], LHC_Fill, 0, 32);

  //Word #5 CMS Run Number       
  Word_Number = 5;
  Header.push_back(std::vector<int>());
  generate_binary_vector(Header[Word_Number], CMS_Run_Number, 0, 32);

  //Word #6 Lumi Section 
  Word_Number = 6;
  Header.push_back(std::vector<int>());
  generate_binary_vector(Header[Word_Number], Lumi_Section, 0, 32);

  //Word #7 Lumi Nibble 
  Word_Number = 7;
  Header.push_back(std::vector<int>());
  generate_binary_vector(Header[Word_Number], Lumi_Nibble, 0, 32);

  //Word #8     
  Word_Number = 8;
  Header.push_back(std::vector<int>());
  generate_binary_vector(Header[Word_Number], NUMBER_OF_MASK_AND_ERROR_WORDS, 0, 16);
  generate_binary_vector(Header[Word_Number], NUMBER_OF_UNITS, 16, 26);
  generate_binary_vector(Header[Word_Number], NUMBER_OF_WORDS_PER_ERROR, 26, 32);

  //Word #>8 Counter Payload;
  std::vector<std::vector<int> > Counter_Payload;

  int N = rand()%N_bunch;
  for(int i=0; i<N_bunch; i++)
    {
      if (i == N)
	{
	  if (i%2 == 0)
	    {
	      Counter_Payload.push_back(std::vector<int>());
	      all_1 = 1;
	      generate_binary_vector(Counter_Payload[i/2], all_1, 0, 16);
      	    }
	  else
	    {
	      all_1 = 1;
	      generate_binary_vector(Counter_Payload[i/2], all_1, 16, 32);
      	    }
	}
      else
	{
	  if (i%2 == 0)
	    {
	      Counter_Payload.push_back(std::vector<int>());
	      all_0 = 0;
	      generate_binary_vector(Counter_Payload[i/2], all_0, 0, 16);
	    }
	  else
	    {
	      all_0 = 0;
	      generate_binary_vector(Counter_Payload[i/2], all_0, 16, 32);
	    }
	}
    }

  Data.insert(Data.end(), Header.begin(), Header.end());
  Data.insert(Data.end(), Counter_Payload.begin(), Counter_Payload.end());
 
  for (int i = 0; i < Data.size(); i++)
    {
      for (int j = 0; j < Data[i].size(); j++)
        {
	  std::cout << Data[i][j] << " ";
	  if (Data[i][j]==1)
{
  std::cout<<"There is!!!"<<std::endl;
 }
        }    
      std::cout << std::endl;
    }

  /*  for (int i = 0; i < Counter_Payload.size(); i++)
    {
      for (int j = 0; j < Counter_Payload[i].size(); j++)
        {
	  if (Counter_Payload[i][j] == 1)
	    {
	  std::cout << "There is a sigle bin!!!" << std::endl;
	    }
        }
    }
  */
  return 0;
}
