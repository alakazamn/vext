#import "drive/v5_drive.h"
#import "drive/v5_two.h"
#include "vex_units.h"
#include <cmath>
#include <iostream>
#include <math.h>       /* atan2 */

/*
 * Implementation of vlib::two methods
 */

void vext::two::straight(int power) {
  vex::directionType direction =
      power > 0 ? vex::directionType::fwd : vex::directionType::rev;
  left().spin(direction, abs(power), vex::percentUnits::pct);
  right().spin(direction, abs(power), vex::percentUnits::pct);
}

void vext::two::turn(int x, int y) {
  const double l[] = {1,1,1,0.7,-1,-0.7,-1,-1,1};
  const double r[] = {-1,0.7,1,1,1,-1,-1,-0.7};
  double part = vext::drive::joystickAngle(x,y) / 45;
  const int low = floor(part);
  const int high = ceil(part);
  const double percent = (vext::drive::joystickAngle(x,y) - low*45) / 45.0;

  left().spin(vex::directionType::rev, vext::drive::tween(percent, 100*l[low], 100*l[high]), vex::velocityUnits::pct);
  right().spin(vex::directionType::rev, vext::drive::tween(percent, 100*r[low], 100*r[high]), vex::velocityUnits::pct);  
}

void vext::two::stop() {
  left().stop(vex::brakeType::hold);
  right().stop(vex::brakeType::hold);
}