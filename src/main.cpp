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
#include "vlib.h"
#include <future>
#include <type_traits>

using namespace vex;

vex::brain Brain;
vex::controller Controller;
vex::competition Competition;

motor Lift = motor(PORT5, gearSetting::ratio18_1, true); //ramp
motor tower = motor(PORT1, gearSetting::ratio6_1, false);

vex::motor LeftFlapper(vex::PORT3, true);
vex::motor RightFlapper(vex::PORT8);
vext::motors intake = vext::motors(LeftFlapper, RightFlapper);

motor LeftMotor = motor(PORT19, gearSetting::ratio18_1, true);
motor RightMotor = motor(PORT12, gearSetting::ratio18_1, false);
motor LeftMotor2 = motor(PORT20, gearSetting::ratio18_1, true);
motor RightMotor2 = motor(PORT11, gearSetting::ratio18_1, false);

auto bot = vext::fwd(LeftMotor, LeftMotor2, RightMotor, RightMotor2);

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
  while(true) {
    if(Controller.ButtonY.pressing()) {
      alliance = 0;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Red Alliance");
      return;
    } else if(Controller.ButtonA.pressing()) {
      alliance = 1;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Blue Alliance");
      return;
    }
    else if(Controller.ButtonB.pressing())
    {
      alliance = 2;
      Brain.Screen.clearScreen();
      Brain.Screen.print("1pt");
      return;
    }
    else if (Controller.ButtonX.pressing())
    {
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

void autonomous(void)
 {
  //ramp.straight(100);
  // basic 4pt auton
  //blue
  if(alliance == 0) {
    bot.moveBy(52, 35);
    intake.stop();
    bot.spinBy(-145, 20);
    bot.moveBy(39, 20);
    ramp.straight(200);
    bot.moveBy(-20, 100);
  } else if (alliance == 1) {
    //red
    bot.moveBy(52, 35);
    intake.stop();
    bot.spinBy(145, 20);
    bot.moveBy(39, 20);
    ramp.straight(200);
    vex::this_thread::sleep_for(5000);
    bot.moveBy(-20, 100);
  }

  else if (alliance ==  2)
  {
    bot.moveBy(-60, 20);
    vex::task::sleep(1000);
    bot.moveBy(50, 20);
    vex::task::sleep(1000);
  }
}

void updateSpeedMode(int speedMode) {
   switch(speedMode) {
     case 0:
         Controller.Screen.clearScreen();
         Controller.Screen.setCursor(1,1);
         Controller.Screen.print("Stack Mode 50");
         Controller.rumble(".");
         bot.setMaxTorque(50, percentUnits::pct);
       break;
     case 1:
         Controller.Screen.clearScreen();
         Controller.Screen.setCursor(1,1);
         Controller.Screen.print("Move Mode 75");
         Controller.rumble("..");
         bot.setMaxTorque(75, percentUnits::pct);
         break;
     case 2:
         Controller.Screen.clearScreen();
         Controller.Screen.setCursor(1,1);
         Controller.Screen.print("Maximum Overdrive 100");
         Controller.rumble("-");
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
  bot.setMovesWhileTurns(true);
  bot.bind(Controller.Axis4, Controller.Axis3);
  axs(100, Controller.Axis2, arm);
  btn(100, Controller.ButtonL2, Controller.ButtonR2,
      intake);
  btn(100, Controller.ButtonX, Controller.ButtonY, tower);

  Controller.ButtonL1.pressed([] { intake.straight(100); });
  Controller.ButtonL1.released([] { intake.stop(); });

  Controller.ButtonR1.pressed([] { intake.straight(-100); });
  Controller.ButtonR1.released([] { intake.stop(); });

   Controller.ButtonLeft.pressed([] {
    speedMode = speedMode != 0 ? speedMode-1 : 2;
    updateSpeedMode(speedMode);
  });
  Controller.ButtonRight.pressed([] {
    speedMode = speedMode != 2 ? speedMode+1 : 0;
    updateSpeedMode(speedMode);
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
  pre_auton();
  Controller.ButtonLeft.pressed([] {
    autonomous();
  });
}
