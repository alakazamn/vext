#import "vlib_motor.h"

void vlib::motor::rotateDeg(double degrees) {
  vex::motor::rotateFor(degrees, vex::rotationUnits::deg);
}
  void vlib::motor::rotateToDeg(double degrees) {
  vex::motor::rotateTo(degrees, vex::rotationUnits::deg);
}