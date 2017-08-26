/**
* @file SourceControlInterface.h
* @brief Abstract virtual class for the SourceControl class, defines the interface
* @author Ben Frazier
* @date 08/17/2017 */

#ifndef SOURCE_CONTROL_INTERFACE_H
#define SOURCE_CONTROL_INTERFACE_H

namespace CEM
{
  class SourceControlInterface
  {
  public:

    //source
    double getInputSource(double time);

  };

}//end namespace CEM

#endif