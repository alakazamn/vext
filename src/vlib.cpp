/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Michael                                                   */
/*    Created:      Fri May 24 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "vex_global.h"
#include "vex_units.h"

#include <future>

namespace vlib {

class motor : public vex::motor {
public:
  motor(int32_t index) : vex::motor(index) {}
  motor(int32_t index, bool reverse) : vex::motor(index, reverse) {}
  ~motor() {}

  void rotateDeg(double degrees) {
    vex::motor::rotateFor(degrees, vex::rotationUnits::deg);
  }
  void rotateToDeg(double degrees) {
    vex::motor::rotateTo(degrees, vex::rotationUnits::deg);
  }
};
class two {
private:
public:
  static void _spinBy(double degree, double vel, vlib::motor left, vlib::motor right) {
      double revs = ((degree/360.0) * 13.70)/4;
      left.spinFor(-revs, vex::rotationUnits::rev, vel, vex::velocityUnits::pct, false);
      right.spinFor(revs, vex::rotationUnits::rev, vel, vex::velocityUnits::pct, true);
  }
  static void _moveBy(double inches, double vel, vlib::motor left, vlib::motor right) {
      double revs = inches / (5 * M_PI);
      left.spinFor(-revs, vex::rotationUnits::rev, vel, vex::velocityUnits::pct, false);
      right.spinFor(-revs, vex::rotationUnits::rev, vel, vex::velocityUnits::pct, true);
  }
  #define spinWith(deg, vel, left, right, callback) vex::thread task([] { vlib::two::_spinBy(deg, vel, left, right); callback(); });
  #define spinTo(deg, left, right, callback) vex::thread task([] {vlib::two::_spinBy(deg, 100, left, right); callback(); });
  #define spinBy(deg, left, right) vex::thread task([] { vlib::two::_spinBy(deg, 100, left, right); });

  #define moveWith(inches, vel, left, right, callback) vex::thread task([] { vlib::two::_moveBy(inches, vel, left, right); callback(); });
  #define moveTo(inches, left, right, callback) vex::thread task([] {vlib::two::_moveBy(inches, 100, left, right); callback(); });
  #define moveBy(inches, left, right) vex::thread task([] { vlib::two::_moveBy(inches, 100, left, right); });

  static void straight(int power, vlib::motor left, vlib::motor right) {
    vex::directionType direction =
        power > 0 ? vex::directionType::fwd : vex::directionType::rev;
    left.spin(direction, abs(power), vex::velocityUnits::pct);
    right.spin(direction, abs(power), vex::velocityUnits::pct);
  }
  static void turn(int x, int y, vlib::motor left, vlib::motor right) {
    if (x < -10) {
      left.spin(vex::directionType::fwd, x, vex::velocityUnits::pct);
      right.spin(vex::directionType::fwd, abs(x), vex::velocityUnits::pct);
    } else if (x > 10) {
      left.spin(vex::directionType::fwd, x, vex::velocityUnits::pct);
      right.spin(vex::directionType::fwd, abs(x) * -1, vex::velocityUnits::pct);
    }
  }
  static void stop(vlib::motor left, vlib::motor right) {
    left.stop(vex::brakeType::hold);
    right.stop(vex::brakeType::hold);
  }

};
class controls {
public:
  static void bindMove(vex::controller::axis x, vex::controller::axis y,
                       vex::controller::button b, vlib::motor left,
                       vlib::motor right) {
    bool inverted = false;
    static auto moveUpdate = [&] {
      if (direction(y) != 0 && direction(x) == 0) { // axis 1 and axis 3
        if (inverted) {
          two::straight(y.position(), left, right);
        } else {
          two::straight(-1 * y.position(), left, right);
        }
      } else if (direction(x) != 0) {
        two::turn(x.position(), y.position(), right, left);
      } else {
        two::stop(left, right);
      }
    };
    y.changed([] { moveUpdate(); });
    x.changed([] { moveUpdate(); });
    static auto invertControls = [&] {
      inverted = !inverted;
    };
    b.pressed([] { invertControls(); });
  }
  #define bind(pow, up, down, l, r)  up.pressed([] { vlib::two::straight(pow, l, r); }); down.pressed([] { vlib::two::straight(-pow, l, r); }); up.released([] { vlib::two::stop(l, r); }); down.released([] { vlib::two::stop(l, r); });

private:
  static int direction(vex::controller::axis axis) {
    if (axis.position() > 10) {
      return 1;
    } else if (axis.position() < -10) {
      return -1;
    } else
      return 0;
  }
};
} // namespace vlib
