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
void GUIScreenRed()
{
  Brain.Screen.setFillColor(vex::color::red);
  Brain.Screen.setPenColor(vex::color::black);
  Brain.Screen.clearScreen();
  Brain.Screen.drawRectangle(0,0,240,136);
  Brain.Screen.drawRectangle(0,136,240,136);
  Brain.Screen.drawRectangle(241,0,240,136);
  Brain.Screen.drawRectangle(241,136,240,136);
  //need to addd text
  vex::task::sleep(5000);
  while (true) 
  {
    if (Brain.Screen.yPosition() < 136){
    if (Brain.Screen.xPosition() < 240) {
      Brain.Screen.clearScreen();
      Brain.Screen.print("Auton 1 Selected");
      //add auton value here
      alliance = 5;
      break;
    }
    else{
           Brain.Screen.clearScreen();
      Brain.Screen.print("Auton 2 Selected");
       //add other auton value here
       alliance = 6;
       break;
    }
     
  }
  if (Brain.Screen.yPosition() > 136)
  {
    if (Brain.Screen.xPosition() < 240)
    {
           Brain.Screen.clearScreen();
      Brain.Screen.print("Auton 3 Selected");
      //add auton value
      alliance = 7;
      break;
    }
    else if (Brain.Screen.xPosition() > 240)
    {
           Brain.Screen.clearScreen();
      Brain.Screen.print("Auton 4 Selected");
      //add auton value
      alliance = 8;
      break;
    }
  }
  }
  
}
void GUIScreenBlue()
{
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(vex::color::blue);
  Brain.Screen.drawRectangle(0,0,240,136);
  Brain.Screen.drawRectangle(0,136,240,136);
  Brain.Screen.drawRectangle(241,0,240,136);
  Brain.Screen.drawRectangle(241,136,240,136);
  //need to add text
  vex::task::sleep(5000);
  while (true)
  {
   if (Brain.Screen.yPosition() < 136){
    if (Brain.Screen.xPosition() < 240) {
           Brain.Screen.clearScreen();
      Brain.Screen.print("Auton 1 Selected");
      alliance = 1;
      //add auton value here
      break;
    }
    else{
           Brain.Screen.clearScreen();
      Brain.Screen.print("Auton 2 Selected");
      alliance = 2;
       //add other auton value here
      break;
    }
     
  }
  if (Brain.Screen.yPosition() > 136)
  {
    if (Brain.Screen.xPosition() < 240)
    {
           Brain.Screen.clearScreen();
      Brain.Screen.print("Auton 3 Selected");
      //add auton value
      alliance = 3;
      break;
    }
    else if (Brain.Screen.xPosition() > 240)
    {
           Brain.Screen.clearScreen();
      Brain.Screen.print("Auton 4 Selected");
      //add auton value
      alliance = 4;
      break;
    }
  }
  }
}
void pre_auton(void) {
  /*// All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Brain.Screen.setPenColor(vex::color::black);
  Brain.Screen.setFillColor(vex::color::blue);
  Brain.Screen.drawRectangle(0,0,240,272);
  Brain.Screen.setFillColor(vex::color::red);
  Brain.Screen.drawRectangle(241,0,240,272);
  Brain.Screen.setFont(monoXL);
  Brain.Screen.printAt(320,125,"Red");
  Brain.Screen.setFillColor(vex::color::blue);
  Brain.Screen.printAt(75,125,"Blue");
  while(true)
  {
    int x = Brain.Screen.xPosition();
    int y = Brain.Screen.yPosition();
    if (x <=240 && y > 0)
    {
      GUIScreenBlue();
      break;
    }
    if (x > 240 && y > 0)
    {
      GUIScreenRed();
      break;
    }
  }*/
  auto test = vlib::VNode(vex::color::blue);

  vlib::GUI::instance()->add(&test);
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
  bot.setMovesWhileTurns(true);
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
