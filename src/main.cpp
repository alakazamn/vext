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

#include <future>
#include "vex_global.h"
#include "vlib.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
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

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
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

void autonomous( void ) {
  //basic 4pt auton
  
  LeftFlapper.spin(directionType::fwd, 100, percentUnits::pct);
  RightFlapper.spin(directionType::fwd, 100, percentUnits::pct);
  bot.moveBy(42, 10);
  bot.spinBy(170,5);
  bot.moveBy(40,10);
  bot.moveBy(3,10);
  ramp.straight(20);
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

void usercontrol( void ) {
    bot.bind(Controller.Axis4, Controller.Axis3);
    axs(100, Controller.Axis2, arm);
    btn(100, Controller.ButtonL2, Controller.ButtonR2, intake); //for intake (flip these)
    btn(50, Controller.ButtonUp, Controller.ButtonDown, ramp);
}

//
// Main will set up the competition functions and callbacks.
//

int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
        
    Controller.ButtonA.pressed([] {
      autonomous();
    });
}
