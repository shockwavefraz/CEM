/**
* @file SimManager.h
* @brief Header File for the Simulation Manager class
* @details The SimManager provides the top most interface to the underlying simulation. It controls the SimEngine and covers exception handling
* @author Ben Frazier
* @date 08/14/2017
**/

#ifndef SIM_MANAGER_H
#define SIM_MANAGER_H

#include "SimEngine/SimEngine.h"
#include "InputParser/InputParser.h"


#include "InputDataInterface.h"
#include "SourceControlInterface.h"
 
#include "SourceControlFactory.h"
#include "ComputeEngineFactory.h"
#include "DataLoggerFactory.h"
#include  "TimeControl.h"

#include <string>

namespace CEM
{
  class SimManager
  {
  public:
    SimManager(std::string inputFileName, std::string outputFileName);
    int Run();

  private:
    //member functions
    std::unique_ptr<SimEngine>createSimEngine();
    void Update();
    void Initialize();
    
    //member variables
    std::unique_ptr<SimEngine> engine_ptr_;  /*!< Simulation engine member variable for running the simulation */
    std::shared_ptr<TimeControl> time_ptr_; /*!< Time Controller member */

    //input members
    std::shared_ptr<InputParser> ip_;  /*!< InputParser member variable for reading the input configuration file */
    std::shared_ptr<InputDataInterface> input_;  /*!< InputData used to retrieve the input from the InputParserYAML class. */

    //control members
    std::shared_ptr<SourceControlInterface> source_ptr_;  /*!< Pointer to the source controller */
    std::shared_ptr<ComputeEngineInterface> compute_ptr_;/*!< FDTD member variable pointer for handling FDTD computations.*/
    std::shared_ptr<DataLoggerInterface> dLogger_ptr_; /*!< DataLogger member variable pointer for handling writing out to a file */

    //factory members
    ComputeEngineFactory computeFactory_;  /*!< Factory to generate the FDTD type */
    DataLoggerFactory dlFactory_;  /*!< Factory to generate the Data Logger type */
    SourceControlFactory sourceFactory_;  /*!< Factory to generate the source */

  };
}

#endif
