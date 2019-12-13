#ifndef VLIB_MOTOR_H
#define VLIB_MOTOR_H

#include "vex.h"

namespace vlib {
  class motor : public vex::motor {
  public:
    motor(int32_t index) : vex::motor(index) {}
    motor(int32_t index, bool reverse) : vex::motor(index, reverse) {}
    ~motor() {}

    void rotateDeg(double degrees);
    void rotateToDeg(double degrees);
  };

}
#endif
