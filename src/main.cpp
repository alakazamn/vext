
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Michael                                                   */
/*    Created:      Fri May 24 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "v5_apitypes.h"
#include "vex.h"
#include <iostream>

#include "vex_global.h"
#include "vex_thread.h"
#include "vex_units.h"
#include "vext.h"
#include <future>
#include <type_traits>

#include "redacted.h"

using namespace vex;

vex::brain Brain;
vex::controller Controller;
vex::competition Competition;

vext::motor ramp(PORT5, gearSetting::ratio18_1, true); // ramp
vext::motor tower(PORT1, gearSetting::ratio6_1, false);

vex::motor IntakeA(vex::PORT8, gearSetting::ratio18_1, true);
vex::motor IntakeB(vex::PORT3, gearSetting::ratio18_1);
auto intake = vext::two(IntakeA, IntakeB);

vex::motor LeftMotor(PORT19, gearSetting::ratio18_1, true);
vex::motor RightMotor(PORT12, gearSetting::ratio18_1, false);
vex::motor LeftMotor2(PORT20, gearSetting::ratio18_1, true);
vex::motor RightMotor2(PORT11, gearSetting::ratio18_1, false);

vex::limit rampDetector(Brain.ThreeWirePort.A);
vext::fwd bot = vext::fwd(LeftMotor, LeftMotor2, RightMotor, RightMotor2);

static int speedMode = 2;
int alliance = 2;

void pre_auton(void) {
  redacted::pre_auton(Controller, Brain);
  return;
}

void autonomous(void) {
  redacted::auton(bot, intake, ramp, tower);

  /*// ramp.straight(100);
  // basic 4pt auton
  // blue
  if (alliance == 0) {
    bot.moveBy(52, 35);
    intake.stop();
    bot.spinBy(-145, 20);
    bot.moveBy(39, 20);
    ramp.straight(200);
    bot.moveBy(-20, 100);
  } else if (alliance == 1) {
    // red
    bot.moveBy(52, 35);
    intake.stop();
    bot.spinBy(145, 20);
    bot.moveBy(39, 20);
    ramp.straight(200);
    vex::this_thread::sleep_for(5000);
    bot.moveBy(-20, 100);
  }

  else if (alliance == 2) {
    bot.moveBy(-60, 20);
    vex::task::sleep(1000);
    bot.moveBy(50, 20);
    vex::task::sleep(1000);
  }*/
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  Sets up all the controller binds using the macros from vext              */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  bot.setMovesWhileTurns(true);
  bot.bind(Controller.Axis1, Controller.Axis3); // Bind bot control to axis 1 and 3
                                                // (X,Y)
  btn(100, Controller.ButtonL1, Controller.ButtonR1,
      intake); // Bind L1 and R1 to the intake
  btn(100, Controller.ButtonY, Controller.ButtonX, tower);

  Controller.ButtonDown.pressed([] {
    speedMode = speedMode != 2 ? speedMode + 1 : 0;
    redacted::updateSpeedMode(speedMode, bot);
  });

  Controller.Axis2.changed([] {
    if(redacted::rampMacroActivated()) {
      return;
    }
    std::cout << ramp.temperature(vex::temperatureUnits::fahrenheit) << std::endl;
    if (Controller.ButtonUp.pressing() && (Controller.Axis2.value() > 0 || rampDetector.pressing() == false)) {
      ramp.spin(directionType::fwd, Controller.Axis2.value(),
                velocityUnits::pct);
    } else {
      ramp.stop((brakeType::coast));
    }
  });
  Controller.ButtonB.pressed([] {
    redacted::rampDown(ramp, intake);
  });
}

//
// Do not modify, except to comment out the last linex
//

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  Controller.ButtonA.pressed([] { autonomous(); }); //for testing
}
