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
#import "vex.h"

#ifndef VLIB_MOTOR_GROUP_CLASS_H
#define VLIB_MOTOR_GROUP_CLASS_H
/*-----------------------------------------------------------------------------*/
/** @file    vex_motorgroup.h
 * @brief   Motor group class header
 *//*---------------------------------------------------------------------------*/

namespace vlib {

class two : public vex::motor_group {
private:
  int32_t leftPort;
  int32_t rightPort;

public:
  two() : vex::motor_group() {}
  ~two() {}

  template <typename... Args>
  two(vex::motor &m1, vex::motor &m2) : vex::motor_group(m1, m2) {
    leftPort = m1.index();
    rightPort = m2.index();
  }

  vex::motor left() { return vex::motor(leftPort, true); }
  vex::motor right() { return vex::motor(rightPort); }

  void straight(int power);
  void turn(int x, int y);
  void stop();
  
  #define btn(pow, up, down, two)                                         \
    up.pressed([] { two.straight(-pow); });                         \
    down.pressed([] { two.straight(pow); });                        \
    up.released([] { two.stop(); });                                  \
    down.released([] { two.stop(); });

  #define axs(pow, up, down, two)                                         \
    up.pressed([] { two.straight(-pow); });                         \
    down.pressed([] { two.straight(pow); });                        \
    up.released([] { two.stop(); });                                  \
    down.released([] { two.stop(); });
  };
} // namespace vlib

#endif // VCS_MOTOR_GROUP_CLASS_H