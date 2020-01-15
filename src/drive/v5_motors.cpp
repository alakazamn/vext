#import "vex.h"
#import "drive/v5_motors.h"
#include <cstdlib>

/*
 * Implementation of vlib::chaindrive methods
 */

vext::motors::~motors() {

}

void vext::motors::straight(int power) {
  vex::directionType direction =
      power < 0 ? vex::directionType::fwd : vex::directionType::rev;
  this->spin(direction, std::abs(power), vex::percentUnits::pct);
}

void vext::motors::stop_coast() {
  this->setStopping(vex::brakeType::coast);
  vex::motor_group::stop();
}

void vext::motors::stop() {
  this->setStopping(vex::brakeType::hold);
  vex::motor_group::stop();
}
