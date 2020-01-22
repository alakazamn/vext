
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

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  while (true) {
    if (Controller.ButtonY.pressing()) {
      alliance = 0;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Red Alliance");
      return;
    } else if (Controller.ButtonA.pressing()) {
      alliance = 1;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Blue Alliance");
      return;
    } else if (Controller.ButtonB.pressing()) {
      alliance = 2;
      Brain.Screen.clearScreen();
      Brain.Screen.print("1pt");
      return;
    } else if (Controller.ButtonX.pressing()) {
      alliance = 3;
      Brain.Screen.print("deplohy");
      return;
    }
  }
  return;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
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
void printScrn(const char *format) {
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print(format);
}

void updateSpeedMode(int speedMode) {
  switch (speedMode) {
  case 0:
    printScrn("Stack Mode 50");
    Controller.rumble("....");
    bot.setMaxTorque(50, percentUnits::pct);
    break;
  case 1:
    printScrn("Move Mode 75");
    Controller.rumble("--");
    bot.setMaxTorque(75, percentUnits::pct);
    break;
  case 2:
    printScrn("Maximum Overdrive 100");
    Controller.rumble(".-.-");
    bot.setMaxTorque(100, percentUnits::pct);
    break;
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  ramp.resetRotation();

  bot.setMovesWhileTurns(true);
  bot.bind(Controller.Axis1, Controller.Axis3); // Bind bot control to axis
                                                // (X,Y)
  btn(100, Controller.ButtonL1, Controller.ButtonR1,
      intake); // Bind R1 and L1 to the intake
  btn(100, Controller.ButtonY, Controller.ButtonX, tower);
  //btn(100, Controller.ButtonY, Controller.ButtonX, ramp);

  Controller.ButtonDown.pressed([] {
    speedMode = speedMode != 2 ? speedMode + 1 : 0;
    updateSpeedMode(speedMode);
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
// Main will set up the competition functions and callbacks.
//

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  //pre_auton();
  //Controller.ButtonLeft.pressed([] { autonomous(); });
}
