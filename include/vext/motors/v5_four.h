#import "vex.h"

#ifndef VEXT_FOUR_CLASS_H
#define VEXT_FOUR_CLASS_H
/*-----------------------------------------------------------------------------*/
/* @addtogroup Motors
 * @file    v5_four.h
 * @brief   VEX provides a class called "motor_group" which allows a programmer
 *          to perform actions on multiple motors together, as if they were one.
 *          This class extends that functionality with actions specific to two
 *          motors, such as turning. It also provides the foundation for something
 *          like a two-motor chaindrive.
 *          Use of the vlib_two class allows for easy controller binding using vlib's
 *          macros (btn or axs, found below).
 *//*---------------------------------------------------------------------------*/

namespace vext {

  /*! \addtogroup motors
  *  @{
  */
class four : public vex::motor_group {
  /*! @} */
private:
  vex::motor *leftAP;
  vex::motor *leftBP;
  vex::motor *rightAP;
  vex::motor *rightBP;

public:

  ~four() {}

  /*
  * Creates a four-motor group, given a left motor and a right motor.
  * @param &m1 Address of left motor
  * @param &m2 Address of right motor
  */
  template <typename... Args>
  four(vex::motor m1, vex::motor m2, vex::motor m3, vex::motor m4) : vex::motor_group(m1, m2, m3, m4) {
    leftAP = &m1;
    leftBP = &m2;
    rightAP = &m3;
    rightBP = &m4;
  }

  /*
    Getters and Setters for specific motors in group (something missing from vex::motor_group)
  */
  vex::motor leftA() {
    return *leftAP;
  }
  vex::motor leftB() {
    return *leftBP;
  }
  vex::motor rightA() {
    return *rightAP;
  }
  vex::motor rightB() {
    return *rightBP;
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

#define u_btn(powUp, powDown, up, down, four)                                                \
  down.pressed([] { four.straight(-powDown); });                                      \
  up.pressed([] { four.straight(powUp); });                                     \
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
