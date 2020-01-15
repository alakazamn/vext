#import "vex.h"
#include "v5_motors.h"

#ifndef VEXT_DRIVE_CLASS_H
#define VEXT_DRIVE_CLASS_H
/*-----------------------------------------------------------------------------*/
/** @file    vext_ .h
 * @brief   

 *//*---------------------------------------------------------------------------*/

namespace vext {

class drive : public vex::motor_group {
public:

  template <typename... Args>
  drive(vex::motor &m1, Args &... m2) : vex::motor_group(m1, m2...) {}
  
  /*
    Getters and Setters for specific motors in group (something missing from vex::motor_group)
  */
  virtual vex::motor_group left() = 0;
  virtual vex::motor_group right() = 0;
  
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
  void stop_coast();

  /*
   * Applies stops both motors and applies brakeType::hold
   */
  void stop();

  /**
   * Rotate the robot by an specific amount of degrees.
   *
   * Intended for use with autons.
   *
   * @param degrees Angle to spin bot, in degrees
   * @param speed The percentage of motor power to apply
   * @param left Left motor
   * @param right Right motor
   */
  void spinBy(double degrees, double speed);

  /**
   * Move the robot by an specific amount of inches.
   *
   * Intended for use with autons.
   *
   * @param inches Distance to move, in inches
   * @param speed The percentage of motor power to apply
   * @param left Left motor
   * @param right Right motor
   */

  void moveBy(double inches, double speed);

  void setMovesWhileTurns(bool val);

  bool getMovesWhileTurns();

  /**
   * Binds bot movement (driver control) to two joysticks
   *
   * @param x The horizontal controller axis
   * @param y Left The vertical controller axis
   */
  void bind(vex::controller::axis x, vex::controller::axis y);
};
} // namespace vlib

#endif // VEXT_DRIVE_CLASS_H