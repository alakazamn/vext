#include "vex.h"

#import "drive/v5_drive.h"
#include <cmath>
#include <iostream>
#include <math.h>       /* atan2 */

/*
 * Implementation of vlib::drive methods
 */

bool moveWhileTurning = false;
 
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

void vext::drive::straight(int power) {
  vex::directionType direction =
      power < 0 ? vex::directionType::fwd : vex::directionType::rev;
  left().spin(direction, std::abs(power), vex::percentUnits::pct);
  right().spin(direction, std::abs(power), vex::percentUnits::pct);
}

void vext::drive::turn(int x, int y) {
  if (x < -10) {
    left().spin(vex::directionType::fwd, std::abs(x)*.8, vex::velocityUnits::pct);
    right().spin(vex::directionType::fwd, x*.8, vex::velocityUnits::pct);
  } else if (x > 10) {
    left().spin(vex::directionType::fwd, std::abs(x) * -.8, vex::velocityUnits::pct);
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
    return a - (std::abs(high - low) * percent);
  } else {
    return a + (std::abs(high - low) * percent);
  }
}
void vext::drive::spin_turn(int x, int y) {
  const double l[] = {1,1,1,0.7,-1,-0.7,-1,-1,1};
  const double r[] = {-1,0.7,1,1,1,-1,-1,-0.7};
  double part = joystickAngle(x,y) / 45;
  const int low = floor(part);
  const int high = ceil(part);
  const double percent = (joystickAngle(x,y) - low*45) / 45.0;

  left().spin(vex::directionType::rev, tween(percent, 100*l[low], 100*l[high]), vex::velocityUnits::pct);
  right().spin(vex::directionType::rev, tween(percent, 100*r[low], 100*r[high]), vex::velocityUnits::pct);  
}

void vext::drive::setMovesWhileTurns(bool val) { moveWhileTurning = val; }

bool vext::drive::getMovesWhileTurns() { return moveWhileTurning; }

void vext::drive::bind(vex::controller::axis x, vex::controller::axis y) {
  static auto moveUpdate = [&] {
    if (::direction(y) != 0 && ::direction(x) == 0) { // axis 1 and axis 3
      if (!getMovesWhileTurns()) {
        straight(y.position());
      } else {
        spin_turn(x.position(), y.position());
      }
    } else if (::direction(x) != 0) {
      if (getMovesWhileTurns()) {
        spin_turn(x.position(), y.position());
      } else {
        turn(x.position(), y.position());
      }
    } else {
      stop();
    }
  };

  y.changed([] { moveUpdate(); });
  x.changed([] { moveUpdate(); });
}
void vext::drive::spinBy(double degrees, double speed) {
  double revs = ((degrees / 360.0) * 13.70) / 4;
  left().rotateFor(-revs, vex::rotationUnits::rev, speed,  vex::velocityUnits::pct, false);
  right().rotateFor(revs, vex::rotationUnits::rev, speed, vex::velocityUnits::pct, true);
}

void vext::drive::moveBy(double inches, double speed) {
  double revs = inches / (5 * M_PI);
  left().rotateFor(revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  right().rotateFor(revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, true);
}
void vext::drive::stop() {
  left().stop();
  right().stop();
}
