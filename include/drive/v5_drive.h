#include "vex.h"

#ifndef VEXT_DRIVE_H
#define VEXT_DRIVE_H

/*-----------------------------------------------------------------------------*/
/** @file   v5_drive.h
 * @brief   This abstract class should be implemented to add more types of 
 *          drives for vext. Currently two and four motor drives are supported.
 *//*---------------------------------------------------------------------------*/

namespace vext {

class drive {
protected:
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

  static double joystickAngle(int x, int y) {
    return atan2(y,x) >= 0 ? atan2(y,x) * 180 / 3.14159 : 360 + (atan2(y,x) * 180 / 3.14159);
  }
  static double tween(double percent, double a, double b) {
    double low = fmin(a,b);
    double high = fmax(a,b);
    if(a>b)  {
      return a - (abs(high - low) * percent);
    } else {
      return a + (abs(high - low) * percent);
    }
  }

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
  virtual void spinBy(double degrees, double speed) = 0;

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

  virtual void moveBy(double inches, double speed) = 0;

  /**
   * Drive a two-motor chaindrive bot in a straight line
   * @param speed The percentage of motor power to apply
   */

  virtual void straight(int power) = 0;

  /**
   * Turn a two-motor bot using the controller joysticks
   *
   * @param x The position of the horizontal joystick
   * @param y The position of the vertical joystick
   */
  
  virtual void turn(int x, int y) = 0;

  /**
   * Stop a two-motor bot and hold
   *
   * @param speed The percentage of motor power to apply
   * @param left Left motor
   * @param right Right motor
   */

  virtual void stop() = 0;

  /**
   * Binds bot movement (driver control) to two joysticks
   *
   * @param x The horizontal controller axis
   * @param y Left The vertical controller axis
   */
  virtual void bind(vex::controller::axis x, vex::controller::axis y) = 0;
};
} // namespace vlib
#endif
