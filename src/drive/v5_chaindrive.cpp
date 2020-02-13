#include "vext.h"

#include <iostream>
/*
 * Implementation of vlib::chaindrive methods
 */

void vext::chaindrive::spinBy(double degrees, double speed) {
  double revs = ((degrees / 360.0) * 13.70) / 4;
  motors.left().spinFor(-revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors.right().spinFor(revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, true);
}

void vext::chaindrive::moveBy(double inches, double speed) {
  double revs = inches / (5 * M_PI);
  motors.left().spinFor(-revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors.right().spinFor(-revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, true);
}

void vext::chaindrive::straight(int power) { motors.straight(power); }

void vext::chaindrive::turn(int x, int y) { motors.turn(x, y); }

void vext::chaindrive::stop() { motors.stop(); }

void vext::chaindrive::bind(vex::controller::axis x, vex::controller::axis y) {
  static auto moveUpdate = [&] {
    if (axisDirection(y) != 0 || axisDirection(x) !=0) { // axis 1 and axis 3
      turn(x.position(), y.position());
    } else {
      stop();
    }
  };

  y.changed([] { moveUpdate(); });
  x.changed([] { moveUpdate(); });
}

// namespace vlib
