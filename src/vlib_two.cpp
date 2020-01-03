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
  return atan2(y,x) >= 0 ? atan2(y,x) * 180 / 3.14159 : 360 + (atan2(y,x) * 180 / 3.14159);
}
double tween(double percent, double a, double b) {
  double low = fmin(a,b);
  double high = fmax(a,b);
  if(a>b)  {
    return a - (abs(high - low) * percent);
  } else {
    return a + (abs(high - low) * percent);
  }
}
void vlib::two::spin_turn(int x, int y) {
  const double l[] = {1,1,1,0.7,-1,-0.7,-1,-1,1};
  const double r[] = {-1,0.7,1,1,1,-1,-1,-0.7};
  double part = joystickAngle(x,y) / 45;
  const int low = floor(part);
  const int high = ceil(part);
  const double percent = (joystickAngle(x,y) - low*45) / 45.0;

  left().spin(vex::directionType::rev, tween(percent, 100*l[low], 100*l[high]), vex::velocityUnits::pct);
  right().spin(vex::directionType::rev, tween(percent, 100*r[low], 100*r[high]), vex::velocityUnits::pct);  
}

void vlib::two::stop() {
  left().stop(vex::brakeType::hold);
  right().stop(vex::brakeType::hold);
}