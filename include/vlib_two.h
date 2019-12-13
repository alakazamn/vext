#ifndef VLIB_TWO_H
#define VLIB_TWO_H

#include "vex.h"

#include "vlib_motor.h"

namespace vlib {
  class two {
  public:
    static void straight(int power, vlib::motor left, vlib::motor right) {
      vex::directionType direction =
          power > 0 ? vex::directionType::fwd : vex::directionType::rev;
      left.spin(direction, abs(power), vex::velocityUnits::pct);
      right.spin(direction, abs(power), vex::velocityUnits::pct);
    }
    static void turn(int x, int y, vlib::motor left, vlib::motor right) {
      if (x < -10) {
        left.spin(vex::directionType::fwd, abs(x), vex::velocityUnits::pct);
        right.spin(vex::directionType::fwd, x, vex::velocityUnits::pct);
      } else if (x > 10) {
        left.spin(vex::directionType::fwd, abs(x) * -1, vex::velocityUnits::pct);
        right.spin(vex::directionType::fwd, x, vex::velocityUnits::pct);
      }
    }
    static void stop(vlib::motor left, vlib::motor right) {
      left.stop(vex::brakeType::hold);
      right.stop(vex::brakeType::hold);
    }

  };
}
#endif
