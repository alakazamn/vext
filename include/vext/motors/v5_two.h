#import "vex.h"

#include "vex_units.h"
#include <cmath>
#include <iostream>
#include <math.h>       /* atan2 */

#ifndef VEXT_TWO_CLASS_H
#define VEXT_TWO_CLASS_H
/*-----------------------------------------------------------------------------*/
/** @file   v5_four.h
 * @brief   VEX provides a class called "motor_group" which allows a programmer
 *          to perform actions on multiple motors together, as if they were one.
 *          This class extends that functionality with actions specific to four
 *          motors, such as turning. It also provides the foundation for something
 *          like a four-motor chaindrive.
 *          Use of the vlib_four class allows for easy controller binding using vext's
 *          macros (btn or axs, found below).
 *//*---------------------------------------------------------------------------*/

namespace vext {

class two : public vex::motor_group {
private:
  /*We store the motor port instead of the motor object
  because the latter approach caused issues*/
  int32_t leftPort;
  int32_t rightPort;

public:
  /*
  * Creates a two-motor group, which is a subclass of the generic vex::motor_group.
  * Don't use this. It'll create memory problems. But I think it's required.
  */
  two() : vex::motor_group() {}
  ~two() {}

  /*
  * Creates a two-motor group, given a left motor and a right motor.
  * @param &m1 Address of left motor
  * @param &m2 Address of right motor
  */
  template <typename... Args>
  two(vex::motor &m1, vex::motor &m2) : vex::motor_group(m1, m2) {
    leftPort = m1.index();
    rightPort = m2.index();
  }

  /*
    Getters and Setters for specific motors in group (something missing from vex::motor_group)
  */
  vex::motor left() { return vex::motor(leftPort, true); }
  vex::motor right() { return vex::motor(rightPort); }

  /*
   * Makes the bot go straight with a set velocity
   * @param int power How fast the bot should go
   */
  void straight(int power);

  /*
   * Turns the bot based on joystick input
   * @param int x Horizontal Joystick position
   * @param int y Vertical Joystick position
   */
  void turn(int x, int y);


  /*
   * Turns the bot based on joystick input, with spin turns
   * @param int x Horizontal Joystick position
   * @param int y Vertical Joystick position
   */
  void spin_turn(int x, int y);

  /*
   * Applies stops both motors and applies brakeType::hold
   */
  void stop();

/*
* These (#define and the subsequent lines) are preprocessor
* macros that are used to sidestep a limitation in how C++ works.
*
* They are intended to make code
* more concise and readable elsewhere in the program.
*/

/*
* Allows binding a vlib::two motorgroup to a button pair
* @param int pow Velocity for both motors
* @param vex::controller::button up Button for positive velocity.
* @param vex::controller::button down Button for negative velocity.
* @param vlib::two two Two-button motorgrouup
*/
#define btn(pow, up, down, two)                                                \
  down.pressed([] { two.straight(-pow); });                                      \
  up.pressed([] { two.straight(pow); });                                     \
  down.released([] { two.stop(); });                                             \
  up.released([] { two.stop(); });

/*
* Allows binding a vlib::two motorgroup to an joystick axis
* @param vex::controller::axis axis Joystick Axis for control.
* @param vlib::two two Two-button motorgrouup
*/
#define axs(axis, two)                                                    \
  static auto moveUpdate = [&] {                                               \
    if (axis.position() >= 10 || axis.position() <= -10) {                     \
      two.straight(axis.position());                                      \
    } else {                                                                   \
      two.stop();                                                              \
    }                                                                          \
  };                                                                           \
  axis.changed([] { moveUpdate(); });
};
} // namespace vlib

#endif // VCS_MOTOR_GROUP_CLASS_H
