#import "vlib_chaindrive.h"

#include "vex_units.h"

/*
* Implementation of vlib::chaindrive methods
*/

//void vlib::chaindrive::setMovesWhileTurns(bool val) { moveWhileTurning = val; }

//bool vlib::chaindrive::getMovesWhileTurns() { return moveWhileTurning; }

void vlib::chaindrive::spinBy(double degrees, double speed) {
  double revs = ((degrees / 360.0) * 13.70) / 4;
  motors.left().spinFor(-revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors.right().spinFor(revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, true);
}

void vlib::chaindrive::moveBy(double inches, double speed) {
  double revs = inches / (5 * M_PI);
  motors.left().spinFor(-revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors.right().spinFor(-revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, true);
}

void vlib::chaindrive::straight(int power) { motors.straight(power); }

void vlib::chaindrive::turn(int x, int y) { motors.turn(x, y); }

void vlib::chaindrive::stop() { motors.stop(); }

void vlib::chaindrive::bind(vex::controller::axis x, vex::controller::axis y) {
  static auto moveUpdate = [&] {
    if (direction(y) != 0 && direction(x) == 0) { // axis 1 and axis 3
      straight(y.position());
    } else if (direction(x) != 0) {
      /*if (getMovesWhileTurns()) {
        spin_turn(x.position(), y.position());
      } else {*/
        turn(x.position(), y.position());
      //}
    } else {
      stop();
    }
  };

  y.changed([] { moveUpdate(); });
  x.changed([] { moveUpdate(); });
}

// namespace vlib
