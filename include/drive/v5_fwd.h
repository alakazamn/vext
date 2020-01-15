#import "vex.h"
#include "v5_drive.h"

#ifndef VEXT_FWD_CLASS_H
#define VEXT_FWD_CLASS_H
/*-----------------------------------------------------------------------------*/
/** @file    vlib_fwd.h
 * @brief   FOUR WHEEL DRIVE TODO ADD MORE INFO
 *//*---------------------------------------------------------------------------*/

namespace vext {

class fwd : public vext::drive {
private:
  /*We store the motor port instead of the motor object
  because the latter approach caused issues*/
  motor_group left_group;
  motor_group right_group;

public:
  /*
  * Creates a two-motor group, which is a subclass of the generic vex::motor_group.
  * Don't use this. It'll create memory problems. But I think it's required.
  */
  ~fwd() {}

  /*
  * Creates a two-motor group, given a left motor and a right motor.
  * @param &m1 Address of left motor
  * @param &m2 Address of right motor
  */
  template <typename... Args>
  fwd(vex::motor &left1, vex::motor &left2, vex::motor &right1, vex::motor &right2) : vext::drive(left1, left2, right1, right2) {
    left_group = vex::motor_group(left1, left2);
    right_group = vex::motor_group(right1, right2);
  }

  /*
    Getters and Setters for specific motors in group (something missing from vex::motor_group)
  */
  vex::motor_group left();
  vex::motor_group right();

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
#define btn(pow, up, down, fwd)                                                \
  down.pressed([] { fwd.straight(-pow); });                                      \
  up.pressed([] { fwd.straight(pow); });                                     \
  down.released([] { fwd.stop(); });                                             \
  up.released([] { fwd.stop(); });

#define btnCoast(pow, up, down, fwd)                                                \
  down.pressed([] { fwd.straight(-pow); });                                      \
  up.pressed([] { fwd.straight(pow); });                                     \
  down.released([] { fwd.stop_coast(); });                                             \
  up.released([] { fwd.stop_coast(); });

/*
* Allows binding a vlib::two motorgroup to an joystick axis
* @param int pow Velocity for both motors
* @param vex::controller::axis axis Joystick Axis for control.
* @param vlib::two two Two-button motorgrouup
*/
#define axs(pow, axis, fwd)                                                    \
  static auto moveUpdate = [&] {                                               \
    if (axis.position() >= 10 || axis.position() <= -10) {                     \
      fwd.straight(axis.position());                                      \
    } else {                                                                   \
      fwd.stop();                                                              \
    }                                                                          \
  };                                                                           \
  axis.changed([] { moveUpdate(); });
};
} // namespace vlib

#endif // VEXT_FWD_CLASS_H