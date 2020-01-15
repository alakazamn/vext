#include "vex.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_motorgroup.h                                            */
/*    Author:     James Pearman                                               */
/*    Created:    7 April 2019                                                */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEXT_MOTORS_CLASS_H
#define   VEXT_MOTORS_CLASS_H

namespace vext {
  
  class motors : public vex::motor_group {
    public:          
      ~motors();
      
      template <typename... Args>
      motors( vex::motor &m1, Args &... m2 ) : vex::motor_group(m1, m2...) { }

      void straight(int power);

      void stop();

      void stop_coast();

  };
}

#endif // VCS_MOTOR_GROUP_CLASS_H