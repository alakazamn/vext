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
#include "vlib.cpp"


using namespace vex;

vlib::motor motorLeft = vlib::motor(PORT1);
vlib::motor motorRight = vlib::motor(PORT2, true);

int main() {
  /*vlib::two::forward(motorLeft, motorRight);
  task::sleep(1000);
  vlib::two::stop(motorLeft, motorRight);*/

  motorLeft.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  motorRight.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  task::sleep(1000);
  motorLeft.stop();
  motorRight.stop();

}
