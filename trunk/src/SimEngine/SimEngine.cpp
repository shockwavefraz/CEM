/**
* @file SimEngine.cpp
* @brief Implementation of the Simulation Engine class
* @author Ben Frazier*
* @date 08/15/2017 */
#include "SimEngine.h"

namespace CEM
{
  //************************************************************
  /**
   * @brief Constructor with file names
   *
   * @param input Pointer to the input data structure
   **/
  SimEngine::SimEngine(std::shared_ptr<InputDataInterface> input)
  {

  }

  //************************************************************  
  /**
   * @brief Update the simulation
   * @param time The current time
   * @param compute The pointer to the computational engine
   * @param dlogger The pointer to the data logger
   * @param source The pointer to the source controller
   **/
  void SimEngine::Update(std::shared_ptr<TimeControlInterface> time, std::shared_ptr<ComputeEngineInterface> compute, std::shared_ptr<DataLoggerInterface> dlogger, std::shared_ptr<SourceControlInterface> source)
  {
    compute->UpdateFields(time->getCurrentTime(), source);

    if (time->timeToLogData())
      dlogger->WriteDataArray(compute->getEField(),time->getCurrentTime(),"/EField");
 }

}//end namespace CEM

