#import "vex.h"

#ifndef VEXT_FOUR_CLASS_H
#define VEXT_FOUR_CLASS_H
/*-----------------------------------------------------------------------------*/
/** @file    v5_four.h
 * @brief   VEX provides a class called "motor_group" which allows a programmer
 *          to perform actions on multiple motors together, as if they were one.
 *          This class extends that functionality with actions specific to two
 *          motors, such as turning. It also provides the foundation for something
 *          like a two-motor chaindrive. 
 *          Use of the vlib_two class allows for easy controller binding using vlib's
 *          macros (btn or axs, found below).
 *//*---------------------------------------------------------------------------*/

namespace vext {

class four : public vex::motor_group {
private:
  /*We store the motor port instead of the motor object
  because the latter approach caused issues*/
  int32_t leftAPort;
  int32_t leftBPort;
  int32_t rightAPort;
  int32_t rightBPort;

public:
  /*
  * Creates a two-motor group, which is a subclass of the generic vex::motor_group.
  * Don't use this. It'll create memory problems. But I think it's required.
  */
  four() : vex::motor_group() {}
  ~four() {}

  /*
  * Creates a two-motor group, given a left motor and a right motor.
  * @param &m1 Address of left motor
  * @param &m2 Address of right motor
  */
  template <typename... Args>
  four(vex::motor &m1, vex::motor &m2, vex::motor &m3, vex::motor &m4) : vex::motor_group(m1, m2, m3, m4) {
    leftAPort = m1.index();
    leftBPort = m2.index();
    rightAPort = m3.index();
    rightBPort = m4.index();
  }

  /*
    Getters and Setters for specific motors in group (something missing from vex::motor_group)
  */
  vex::motor leftA() {
    return vex::motor(leftAPort, true);
  }
  vex::motor leftB() {
    return vex::motor(leftBPort, true);
  }
  vex::motor rightA() {
    return vex::motor(rightAPort, true);
  }
  vex::motor rightB() {
    return vex::motor(rightBPort, true);
  }

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
* Allows binding a vext::four motorgroup to a button pair
* @param int pow Velocity for all motors
* @param vex::controller::button up Button for positive velocity.
* @param vex::controller::button down Button for negative velocity.
* @param vext::four four Four-button motorgroup
*/
#define btn(pow, up, down, four)                                                \
  down.pressed([] { four.straight(-pow); });                                      \
  up.pressed([] { four.straight(pow); });                                     \
  down.released([] { four.stop(); });                                             \
  up.released([] { four.stop(); });

/*
* Allows binding a vext::four motorgroup to an joystick axis
* @param vex::controller::axis axis Joystick Axis for control.
* @param vext::four four Four-button motorgroup
*/
#define axs(axis, four)                                                    \
  static auto moveUpdate = [&] {                                               \
    if (axis.position() >= 10 || axis.position() <= -10) {                     \
      four.straight(axis.position());                                      \
    } else {                                                                   \
      four.stop();                                                              \
    }                                                                          \
  };                                                                           \
  axis.changed([] { moveUpdate(); });
};
} // namespace vlib

#endif // VCS_MOTOR_GROUP_CLASS_H