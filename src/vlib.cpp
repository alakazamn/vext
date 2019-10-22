/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Michael                                                   */
/*    Created:      Fri May 24 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#include <future>

namespace vlib {

  class motor : public vex::motor {
  public:
    motor( int32_t index ) : vex::motor(index) {}
    motor( int32_t index, bool reverse ) : vex::motor(index, reverse) {}
    ~motor() {}

    void rotateDeg(double degrees) {
      vex::motor::rotateFor(degrees, vex::rotationUnits::deg);
    }
    void rotateToDeg(double degrees) {
      vex::motor::rotateTo(degrees, vex::rotationUnits::deg);
    }
  };

  class two {
  public:
    static void straight(int power, vlib::motor left, vlib::motor right) {
      vex::directionType direction = power > 0 ? vex::directionType::fwd : vex::directionType::rev;
      left.spin(direction, abs(power), vex::velocityUnits::pct);
      right.spin(direction, abs(power), vex::velocityUnits::pct);
    }
    static void turn(int x, int y, vlib::motor left, vlib::motor right) {
      if(x < -10)
      {
        right.spin(vex::directionType::fwd, x, vex::velocityUnits::pct);
        left.spin(vex::directionType::fwd, abs(x), vex::velocityUnits::pct);
      }
      else if (x > 10)
      {
        right.spin(vex::directionType::fwd, x, vex::velocityUnits::pct);
        left.spin(vex::directionType::fwd, abs(x) * -1, vex::velocityUnits::pct);
      }

    }
    static void stop(vlib::motor left, vlib::motor right) {
      left.stop();
      right.stop();
    }
  };
  class controls {
  public:
    static void bindTwo(vex::controller::axis x, vex::controller::axis y, vex::controller::button b, vlib::motor left, vlib::motor right) {
      bool inverted = false;
      static auto moveUpdate = [&] {

        if (direction(y) != 0 && direction(x) == 0) { //axis 1 and axis 3
          if(inverted) {
            two::straight(-1 * y.position(), left, right);
          } else {
            two::straight(y.position(), left, right);
          }
        }
        else if (direction(x) != 0) {
          two::turn(x.position(), y.position(), right, left);
        }
        else {
          two::stop(left, right);
        }
      };
      y.changed([] {
        moveUpdate();
      });
      x.changed([] {
        moveUpdate();
      });
      static auto invertControls = [&] {
        inverted = !inverted;
      };
      b.pressed([] {
        invertControls();
      });
    }
  private:
    static int direction(vex::controller::axis axis) {
      if(axis.position()>10) {
        return 1;
      } else if(axis.position() < -10) {
        return -1;
      }
      else return 0;
    }
  };
}
