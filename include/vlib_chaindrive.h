/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Michael                                                   */
/*    Created:      Fri May 24 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef VLIB_CHAINDRIVE_H
#define VLIB_CHAINDRIVE_H

#include "vex.h"
#include "vlib_two.h"

namespace vlib {

class chaindrive {
private:
  vlib::two motors;

  static int direction(vex::controller::axis axis) {
    if (axis.position() > 10) {
      return 1;
    } else if (axis.position() < -10) {
      return -1;
    } else
      return 0;
  }

public:
  /*
   * Construct a chaindrive with left and right motors
   * @param left Left port
   * @param right Right port
   */
  chaindrive(int32_t left, int32_t right) {
    auto leftMotor = vex::motor(left, true);
    auto rightMotor = vex::motor(right);
    motors = two(leftMotor, rightMotor);
  };

  /**
   * Rotate the robot by an specific amount of degrees.
   *
   * Internal and blocking.
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
   * Internal and blocking.
   *
   * @param inches Distance to move, in inches
   * @param speed The percentage of motor power to apply
   * @param left Left motor
   * @param right Right motor
   */

  void moveBy(double inches, double speed);

  /**
   * Drive a two-motor bot in a straight line
   *
   * @param speed The percentage of motor power to apply
   */

  void straight(int power);

  /**
   * Turn a two-motor bot using the controller joysticks
   *
   * @param x The position of the horizontal joystick
   * @param y The position of the vertical joystick
   */

  void turn(int x, int y);

  /**
   * Stop a two-motor bot and hold
   *
   * @param speed The percentage of motor power to apply
   * @param left Left motor
   * @param right Right motor
   */

  void stop();

  void bind(vex::controller::axis x, vex::controller::axis y);

  void link(int pow, vex::controller::button up, vex::controller::button down);
  
  };
} // namespace vlib
#endif
