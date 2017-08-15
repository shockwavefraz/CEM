/**
* @file SimEngine.cpp
* @brief Implementation of the Simulation Engine class *
* @author Ben Frazier*
* @date 08/15/2017 */
#include "SimEngine.h"

/**
* @brief Default Constructor
*
**/
SimEngine::SimEngine()
{
}

/**
* @brief Constructor with a file name
*
* @param fileName Name of the file to read as input
**/
SimEngine::SimEngine(std::string inputFileName, std::string outputFileName)
{
   ipError_ = ip_.ReadInputFile(inputFileName);
   ipError_ = ip_.GetInputStruct(input_);

   fdtd_.InitializeEngine(input_);
   
   dLogger_.CreateFile(outputFileName);
   dLogger_.WriteDataHeader(input_);
}

/**
* @brief Run the simulation
*
**/
void SimEngine::Run()
{

for(int time = input_.startTime_; time < input_.stopTime_; time++)
  {
    fdtd_.UpdateFields(time);
    fdtd_.SetEFieldSource(0,time);
    dLogger_.WriteDataArray(fdtd_.getEField());   
  }
}
