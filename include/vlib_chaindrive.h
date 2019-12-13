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
#include "vlib_motor.h"
#include "vlib_two.h"

namespace vlib {


class chaindrive {
    private:
    int32_t leftPort;
    int32_t rightPort;

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
        leftPort = left;
        rightPort = right;
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
      void _spinBy(double degrees, double speed);

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

     void _moveBy(double inches, double speed);

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

    vlib::motor getLeft() {
      return motor(leftPort, true);
    }
    vlib::motor getRight() {
      return motor(rightPort);
    }
    /**
    * Convenience macros to spin the bot and perform an action when complete
    */

    #define spinWith(deg, vel, chain, callback) vex::thread task([] { chain._spinBy(deg, vel); callback(); });
    #define spinTo(deg, chain, callback) vex::thread task([] {chain._spinBy(deg, 100); callback(); });
    #define spinBy(deg, chain) vex::thread task([] { chain._spinBy(deg, 100); });

    /**
    * Convenience macros to move the bot and perform an action when complete
    */

    #define moveWith(inches, vel, chain, callback) vex::thread task([] { chain._moveBy(inches, vel); callback(); });
    #define moveTo(inches, chain, callback) vex::thread task([] {chain._moveBy(inches, 100); callback(); });
    #define moveBy(inches, chain) vex::thread task([] { chain._moveBy(inches, 100); });

    #define linkMotor(pow, up, down, l, r)  up.pressed([] { vlib::two::straight(-pow, l, r); }); down.pressed([] { vlib::two::straight(pow, l, r); }); up.released([] { vlib::two::stop(l, r); }); down.released([] { vlib::two::stop(l, r); });


};
} // namespace vlib
#endif
