#import "vext/drive/v5_drive.h"
#import "vext/motors/v5_four.h"
#include "vex_units.h"
#include <cmath>
#include <iostream>
#include <math.h>       /* atan2 */

/*
 * Implementation of vlib::two methods
 */

void vext::four::straight(int power) {
  vex::directionType direction =
      power > 0 ? vex::directionType::fwd : vex::directionType::rev;
  leftA().spin(direction, abs(power), vex::percentUnits::pct);
  leftB().spin(direction, abs(power), vex::percentUnits::pct);
  rightA().spin(direction, abs(power), vex::percentUnits::pct);
  rightB().spin(direction, abs(power), vex::percentUnits::pct);
}

void vext::four::turn(int x, int y) {
      leftA().spin(vex::directionType::fwd, (x + y)/1, vex::velocityUnits::pct);
      leftB().spin(vex::directionType::fwd, (x + y)/1, vex::velocityUnits::pct);
      rightA().spin(vex::directionType::rev, (x - y)/1, vex::velocityUnits::pct);
      rightB().spin(vex::directionType::rev, (x - y)/1, vex::velocityUnits::pct);
}

void vext::four::stop() {
  leftA().stop(vex::brakeType::hold);
  leftB().stop(vex::brakeType::hold);
  rightA().stop(vex::brakeType::hold);
  rightB().stop(vex::brakeType::hold);
}
