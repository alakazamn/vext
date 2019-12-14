#include "vex.h"
#include "vlib_two.h"

#ifndef VLIB_CHAINDRIVE_H
#define VLIB_CHAINDRIVE_H

/*-----------------------------------------------------------------------------*/
/** @file    vlib_two.h
 * @brief   This class utilizes the vlib::two motorgroup to provide 
 *          functionality for building a chaindrive.
 *          Controller binding is provided with a function.
 *          Some of the methods are intended for use with autons.
 *//*---------------------------------------------------------------------------*/

namespace vlib {

class chaindrive {
private:
  vlib::two motors;
  //bool moveWhileTurning;

  /*
  * Utility function to get the direction of an axis, with some
  * cutoff filtering to make sure the press was intentional.
  * @param axis Just the axis of the controller you want to check.
  * @return int Positive for up, negative for down, zero for neutral.
  */
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

  /**
   * Drive a two-motor chaindrive bot in a straight line
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
  
  /*void setMovesWhileTurns(bool val);

  bool getMovesWhileTurns();*/

  /**
   * Stop a two-motor bot and hold
   *
   * @param speed The percentage of motor power to apply
   * @param left Left motor
   * @param right Right motor
   */

  void stop();

  /**
   * Binds bot movement (driver control) to two joysticks
   *
   * @param x The horizontal controller axis
   * @param y Left The vertical controller axis
   */
  void bind(vex::controller::axis x, vex::controller::axis y);
};
} // namespace vlib
#endif
