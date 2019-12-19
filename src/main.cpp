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
#include "vex_units.h"
#include "vlib.h"
#include <future>

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
vex::controller Controller;

vex::motor LeftArm(vex::PORT6, true);
vex::motor RightArm(vex::PORT16);
vlib::two arm = vlib::two(LeftArm, RightArm);

vex::motor LeftFlapper(vex::PORT5, true);
vex::motor RightFlapper(vex::PORT15);
vlib::two intake = vlib::two(LeftFlapper, RightFlapper);

vex::motor LeftRamp(vex::PORT10, true);
vex::motor RightRamp(vex::PORT20);
vlib::two ramp = vlib::two(LeftRamp, RightRamp);

// A global instance of vex::competition
vex::competition Competition;

auto bot = vlib::chaindrive(vex::PORT1, vex::PORT2);

int alliance = 0;

// define your global instances of motors and other devices here

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
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  while(true) {
    if(Controller.ButtonLeft.pressing()) {
      alliance = 0;
      Brain.Screen.print("Run Auton");
      return;
    } else if(Controller.ButtonRight.pressing()) {
      alliance = 1;
      Brain.Screen.print("Don't run auton");
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
  // basic 4pt auton
  if(alliance == 0) {
    
    bot.moveBy(85, 100);
    arm.straight(100);
    vex::task::sleep(2000);
    intake.spin(vex::directionType::fwd, 100, vex::percentUnits::pct);
    arm.straight(-100);
    vex::task::sleep(2000);
    arm.stop();
    
  } else {
    
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
  bot.setMovesWhileTurns(false);
  bot.bind(Controller.Axis4, Controller.Axis3);
  axs(100, Controller.Axis2, arm);
  btn(75, Controller.ButtonL2, Controller.ButtonR1,
      intake);
  btn(60, Controller.ButtonUp, Controller.ButtonDown, ramp);

  Controller.ButtonL1.pressed([] { intake.straight(10); });
  Controller.ButtonL1.released([] { intake.stop(); });

  Controller.ButtonR2.pressed([] { intake.straight(-10); });
  Controller.ButtonR2.released([] { intake.stop(); });
}

//
// Main will set up the competition functions and callbacks.
//

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();
  Controller.ButtonA.pressed([] {
    autonomous();
  });
}
