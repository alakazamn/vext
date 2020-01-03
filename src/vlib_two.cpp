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

double joystickAngle(int x, int y) {
  return atan2(x,y) >= 0 ? atan2(x,y) * 180 / 3.14159 : 360 + (atan2(x,y) * 180 / 3.14159);
}
double tween(double percent, double low, double high) {
  return low + (high - low) * percent;
}
void vlib::two::spin_turn(int x, int y) {
  const double l[] = {1,1,1,0.7,-1,-0.7,-1,-1,-1,1};
  const double r[] = {-1,0.7,1,1,1,-1,-1,-0.7,-1};
  double part = joystickAngle(x,y) / 45;
  const int low = floor(part);
  const int high = ceil(part);
  const double percent = (joystickAngle(x,y) - low*45) / 45.0;
  right().spin(vex::directionType::fwd, 100*tween(percent, r[low], r[high]), vex::velocityUnits::pct);
  left().spin(vex::directionType::rev, 100*tween(percent, l[low], l[high]), vex::velocityUnits::pct);
}

void vlib::two::stop() {
  left().stop(vex::brakeType::hold);
  right().stop(vex::brakeType::hold);
}