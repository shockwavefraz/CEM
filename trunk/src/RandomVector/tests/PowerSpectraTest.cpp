#include "PowerSpectraFunctions.h"
#include <algorithm>
#include <iterator>
#include <math.h>

#include <gperftools/heap-profiler.h>
#include "DataLogger_HDF5.h"

#include <string>
  using std::string;

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;

namespace PowerSpectra
{
namespace Power_Spectra_Test
{
namespace testing
{

	
    class PowerSpectraTest : public Test
    {
    protected:
        PowerSpectraTest(){}
        ~PowerSpectraTest(){}

    virtual void SetUp()
      {
	 	eps = 1e-10;
	 	dl = new DataLoggerHDF5("PowerSpectra.h5");
      }
      virtual void TearDown(){ delete dl; }
	  DataLoggerHDF5* dl;
	  double dk;
	  double eps;

    };

//Test 1 - Elfouhaily power spectra
  TEST_F(PowerSpectraTest, Elfouhaily)
  {
  HeapProfilerStart("prefix.000") ;
  	double L = 20000;
  	double N = 40000;
  	double phi = 0.0;
  	double age = 0.84;
  	double U10 = 10;
  	double dk = 2*M_PI/L;
	
	std::vector<double> k;
	
	for(int i = 0; i < N/2 + 1; i++)
	{
		k.push_back(i*dk);
	}
	
	double testKp = 9.81*age*age/(U10*U10);
	
	std::vector<double> S = Elfouhaily(k,U10,age,phi);
	dl->WriteData(S, "Elfouhaily");
	dl->WriteData(k, "k");
	HeapProfilerDump("done");
	HeapProfilerStop(); 	
  }
  
  
} // namespace testing
} // namespace Power_Spectra_Test
} // namespace PowerSpectra
