/**
* @file FDTDFactory.cpp
* @brief Implementation of the FDTD Factory class
* @author Ben Frazier
* @date 08/15/2017 */

#include "FDTDFactory.h"
#include "Interfaces/FDTDInterface.h"

namespace CEM
{
  FDTDFactory::FDTDFactory()
  {
  }

   std::unique_ptr<FDTDInterface> FDTDFactory::createComputationalEngine(InputData & input)
   {
     std::unique_ptr<FDTDInterface> fdtd (new FDTD_1D(input));
     return fdtd;
   }

}

