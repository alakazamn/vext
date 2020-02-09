#include "vex.h"
#include "vext/motors/v5_four.h"
#include "vext/drive/v5_fwd.h"
#include "vext/v5_autons.h"

#ifndef VEXT_ID_H
#define VEXT_ID_H

/*-----------------------------------------------------------------------------*/
/* @file   v5_id.h
 * @brief   This class utilizes the vlib::four motorgroup to provide
 *          functionality for building a four-wheel drive.
 *          Controller binding is provided with a function,
 *          intended for two-stick control.
 *          Some of the methods are intended for use with autons.
 *          This class uses an inertial sensor to make more accurate
 *          movement
 *//*---------------------------------------------------------------------------*/

namespace vext {
    /*! \addtogroup drive
    *  @{
    */
    class id : public fwd {
    /*! @} */
    private:
        alliance allianceColor = alliance::RED;
    public:
      vex::inertial *inert;
      /*
      * Construct a chaindrive with left and right motors
      * @param left Left port
      * @param right Right port
      */
      id(vex::motor leftA ,vex::motor leftB, vex::motor rightA, vex::motor rightB, vex::inertial *i, double wheel, double diagonal) : fwd(leftA, leftB, rightA, rightB, wheel, diagonal) {
        inert = i;
      };

      /**
      * Rotate the robot by an specific amount of degrees, using an inertial sensor.
      *
      * Intended for use with autons.
      *
      * @param degrees Angle to spin bot, in degrees
      * @param speed The percentage of motor power to apply
      * @param left Left motor
      * @param right Right motor
      */
      void spinBy(double degrees, double speed, double kP, double kD);

      /**
      * Move the robot by an specific amount of inches, using an inertial sensor.
      *
      * Intended for use with autons.
      *
      * @param inches Distance to move, in inches
      * @param speed The percentage of motor power to apply
      * @param left Left motor
      * @param right Right motor
      */

      void moveBy(double inches, double speed);

      void calibrate() {
        inert->calibrate();
      }
      bool isCalibrating() {
        return inert->isCalibrating();
      }
      void setAlliance(alliance a) {
        allianceColor = a;
      }
      vext::alliance getAlliance() {
        return allianceColor;
      }
    };
} // namespace vext
#endif
