#import "vlib_two.h"
#include "vex_units.h"
#include <cmath>
#include <iostream>
#include <math.h>       /* atan2 */

/*
 * Implementation of vlib::two methods
 */

void vlib::two::straight(int power) {
  vex::directionType direction =
      power < 0 ? vex::directionType::fwd : vex::directionType::rev;
  left().spin(direction, abs(power), vex::percentUnits::pct);
  right().spin(direction, abs(power), vex::percentUnits::pct);
}

void vlib::two::turn(int x, int y) {
  if (x < -10) {
    left().spin(vex::directionType::fwd, abs(x)*.8, vex::velocityUnits::pct);
    right().spin(vex::directionType::fwd, x*.8, vex::velocityUnits::pct);
  } else if (x > 10) {
    left().spin(vex::directionType::fwd, abs(x) * -.8, vex::velocityUnits::pct);
    right().spin(vex::directionType::fwd, x*.8, vex::velocityUnits::pct);
  }
}

void vlib::two::spin_turn(int x, int y) {

}

void vlib::two::stop() {
  left().stop(vex::brakeType::hold);
  right().stop(vex::brakeType::hold);
}