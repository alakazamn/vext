#import "vext/drive/v5_drive.h"

#import "vext/drive/v5_fwd.h"

#include "vex_units.h"
#include <iostream>
/*
 * Implementation of vlib::chaindrive methods
 */

void vext::fwd::spinBy(double degrees, double speed) {
  resetRotation();
  double revs = ((degrees / 360.0) * diag) / 4;
  motors.leftA().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors.leftB().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors.rightA().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, false);
  motors.rightB().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, true);
}

void vext::fwd::moveBy(double inches, double speed) {
  resetRotation();
  double revs = inches / (wh * M_PI);
  motors.leftA().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors.leftB().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors.rightA().rotateFor(vex::directionType::rev, revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, false);
  motors.rightB().rotateFor(vex::directionType::rev, revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, true);
}

void vext::fwd::straight(int power) { motors.straight(power); }

void vext::fwd::turn(int x, int y) { motors.turn(x, y); }

void vext::fwd::stop() { motors.stop(); }

void vext::fwd::stopCoast() { motors.setStopping(vex::brakeType::coast); motors.stop(); }

void vext::fwd::setMaxTorque(double value, vex::percentUnits units) {
  motors.leftA().setMaxTorque(value, units);
  motors.leftB().setMaxTorque(value, units);
  motors.rightA().setMaxTorque(value, units);
  motors.rightB().setMaxTorque(value, units);
}

void vext::fwd::resetRotation() {
  motors.leftA().resetRotation();
  motors.leftB().resetRotation();
  motors.rightA().resetRotation();
  motors.rightB().resetRotation();
}

void vext::fwd::rotateTo( double rotation, vex::rotationUnits units, double velocity, vex::velocityUnits units_v ) {
  motors.leftA().startRotateTo(rotation,units,velocity,units_v);
  motors.leftB().startRotateTo(rotation,units,velocity,units_v);
  motors.rightA().rotateTo(rotation,units,velocity,units_v);
  motors.rightB().rotateTo(rotation,units,velocity,units_v);
}

void vext::fwd::bind(vex::controller::axis x, vex::controller::axis y) {
  static auto moveUpdate = [&] {
    if (direction(y) != 0 || direction(x) !=0) { // axis 1 and axis 3
      turn(x.position(), y.position());
    } else {
      stop();
    }
  };

  y.changed([] { moveUpdate(); });
  x.changed([] { moveUpdate(); });
}


// namespace vlib
