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
#include "vlib.cpp"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::controller Controller;
vlib::motor RightMotor(vex::PORT2);
vlib::motor LeftMotor(vex::PORT1, true);
vlib::motor RightArm(vex::PORT16);
vlib::motor LeftArm(vex::PORT6, true);
vlib::motor RightFlapper(vex::PORT15);
vlib::motor LeftFlapper(vex::PORT5, true);
vlib::motor LeftRamp(vex::PORT10);
vlib::motor RightRamp(vex::PORT20, true);

// A global instance of vex::competition
vex::competition Competition;

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
  //basic 1pt auton
 /* vlib::two::straight(-100, LeftFlapper, RightFlapper);
  task::sleep(4000);
  vlib::two::stop(LeftFlapper, RightFlapper);*/
  LeftFlapper.spin(directionType::fwd, 100, percentUnits::pct);
  RightFlapper.spin(directionType::fwd, 100, percentUnits::pct);
  moveTo(63, LeftMotor, RightMotor, [] {
    LeftFlapper.stop();
    RightFlapper.stop();
      spinTo(195, LeftMotor, RightMotor, [] {
          moveTo(50, LeftMotor, RightMotor, [] {

          })
      });
  });
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

    vlib::controls::bindMove(Controller.Axis1, Controller.Axis3, Controller.ButtonB, LeftMotor, RightMotor);
    bind(30, Controller.ButtonR1, Controller.ButtonR2, LeftArm, RightArm);
    bind(100, Controller.ButtonL1, Controller.ButtonL2, LeftFlapper, RightFlapper);
    bind(50, Controller.ButtonUp, Controller.ButtonDown, LeftRamp, RightRamp);
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
        
    Controller.ButtonX.pressed([] {
      autonomous();
    });
}
