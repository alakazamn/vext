#include "vex.h"
#include "v5_four.h"
#include "drive/v5_drive.h"

#ifndef VEXT_FWD_H
#define VEXT_FWD_H

/*-----------------------------------------------------------------------------*/
/** @file   vlib_chaindrive.h
 * @brief   This class utilizes the vlib::two motorgroup to provide 
 *          functionality for building a chaindrive.
 *          Controller binding is provided with a function.
 *          Some of the methods are intended for use with autons.
 *//*---------------------------------------------------------------------------*/

namespace vext {

class fwd : public drive {
private:
  vext::four motors;
  bool moveWhileTurning;
public:
  /*
   * Construct a chaindrive with left and right motors
   * @param left Left port
   * @param right Right port
   */
  fwd(vex::motor &leftA ,vex::motor &leftB, vex::motor &rightA, vex::motor &rightB) {
    motors = vext::four(leftA, leftB, rightA, rightB);
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
  
  void spin_turn(int x, int y);

  void setMovesWhileTurns(bool val);

  bool getMovesWhileTurns();

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

  /** 
    * @prog_lang{block|cpp|pro}
    * @drawer_cat{setting}
    * @block_sig{Motor.setMaxTorque(50,percent);}
    * @cpp_sig{Motor.setMaxTorque(50,vex::percentUnits::pct);}
    * @brief Sets the max torque of the motor.
    * @param value Sets the amount of torque.
    * @param units The measurement unit for the torque value.
    */
  void            setMaxTorque( double value, vex::percentUnits units );
};
} // namespace vext
#endif
