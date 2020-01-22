#include "v5_apitypes.h"
#include "vex.h"
#include "vext.h"

#include "redacted.h"

using namespace vex;

bool macroOn = false;


void wait(double miliseconds)
{
  task::sleep(miliseconds);
}

void straight(vext::fwd bot, double degrees, double speed, bool coast) //This method is used as a fast way to write in straights and the ability to coast is also given
{
  bot.resetRotation();
  bot.rotateTo(degrees,rotationUnits::deg,speed,velocityUnits::pct);

  if(coast==true)
  {
    bot.stopCoast();
  }
  while(bot.motors.leftA().isSpinning()&&bot.motors.rightA().isSpinning())
  {
    wait(10);
  }
}

void robotTurn(vext::fwd bot, double degrees, double speed) //This method is used as a fast way to write in turns
{
  bot.resetRotation();
  bot.motors.leftA().startRotateTo(degrees,rotationUnits::deg,speed,velocityUnits::pct);
  bot.motors.leftB().startRotateTo(degrees,rotationUnits::deg,speed,velocityUnits::pct);
  bot.motors.rightA().rotateTo(-degrees,rotationUnits::deg,speed,velocityUnits::pct);
  bot.motors.rightB().rotateTo(-degrees,rotationUnits::deg,speed,velocityUnits::pct);
  while(bot.motors.leftA().isSpinning()&&bot.motors.rightA().isSpinning())
  {
    wait(10);
  }
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

static int fieldPosition;
static int alliance;

void redacted::pre_auton(vex::controller Controller, vex::brain Brain) {
/* ==============================================================================================
  Begin auton selector code. Allows us to choose which autons to use before plugging into the field
  ================================================================================================= */
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(1,1);
  Controller.Screen.print("Blue Press A");
  Controller.Screen.setCursor(2,1);
  Controller.Screen.print("Red Press B");
  while (true)
  {
    if (Controller.ButtonA.pressing())
    {
      alliance=0;
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1,1);
      Controller.Screen.print("Blue5L Press Left");
      Controller.Screen.setCursor(2,1);
      Controller.Screen.print("Blue1R Press Right");
      Controller.Screen.setCursor(3,1);
      Controller.Screen.print("Bypass Press X");
      break;
    }
    else if (Controller.ButtonB.pressing())
    {
      alliance=1;
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1,1);
      Controller.Screen.print("Red5R Press Right");
      Controller.Screen.setCursor(2,1);
      Controller.Screen.print("Red1L Press Left");
      Controller.Screen.setCursor(3,1);
      Controller.Screen.print("Bypass Press X");
      break;
    }
  }
  while(true)
  {
    if (alliance == 0)
    {
      if (Controller.ButtonLeft.pressing())
      {
        fieldPosition=1;
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print("Blue 5pt Left");
        break;
      }
      else if (Controller.ButtonRight.pressing())
      {
        fieldPosition=3;
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print("Blue 1pt Right");
        break;
      }
      else if (Controller.ButtonX.pressing())
      {
        fieldPosition=4;
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print("Auton Bypassed");
        break;
      }
    }
    else if (alliance == 1)
    {
      if (Controller.ButtonRight.pressing())
      {
        fieldPosition=2;
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print("Red 5pt Right");
        break;
      }
      else if (Controller.ButtonLeft.pressing())
      {
        fieldPosition=3;
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print("Red 1pt Left");
        break;
      }
      else if (Controller.ButtonX.pressing())
      {
        fieldPosition=4;
        Controller.Screen.clearScreen();
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print("Auton Bypassed");
        break;
      }
    }
  }
}

void deploy(vext::two intake, vex::motor tower, vex::motor ramp) //This method is used to deploy the ramp in the beginning of the match
{
  //Lift.rotateTo(1000,rotationUnits::deg,100,velocityUnits::pct);
  intake.spin(directionType::rev, 100, velocityUnits::pct);
  wait(100);
  tower.startRotateTo(500, rotationUnits::deg, 80, velocityUnits::pct); 
  //Tower2.startRotateTo(-500, rotationUnits::deg, 80, velocityUnits::pct);
  task::sleep(300); //500
  tower.stop(brakeType::hold);
  //Tower2.stop(brakeType::hold);
  ramp.startRotateTo(1000,rotationUnits::deg,100,velocityUnits::pct);
  tower.startRotateTo(-500, rotationUnits::deg, 50, velocityUnits::pct); 
  //Tower2.startRotateTo(500, rotationUnits::deg, 50, velocityUnits::pct);
  task::sleep(500);
  intake.stop();
  task::sleep(100);
}

void printScrn(const char *format) {
  vex::controller Controller;

  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print(format);
}

void redacted::updateSpeedMode(int speedMode, vext::fwd bot) {
  vex::controller Controller;
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
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void redacted::auton(vext::fwd bot, vext::two intake, vex::motor ramp, vex::motor tower) {
  switch(fieldPosition)
  {
    case 1: //Blue Single 5 Pt
    {
    deploy(intake, tower, ramp);
    intake.spin(directionType::fwd, 100, velocityUnits::pct);
    straight(bot, 200,30, true);
    straight(bot, 500,20, false);
    straight(bot, -200, 40, false);
    robotTurn(bot,-400, 50);
    straight(bot, 600, 30, true);
    intake.stop();
    intake.spin(directionType::rev, 30, velocityUnits::pct);
    redacted::rampDown(ramp,intake);
    intake.spin(directionType::rev, 30, velocityUnits::pct);
    straight(bot, -500, 30, true);
    ramp.rotateTo(-400, rotationUnits::deg, 50, velocityUnits::pct);
    ramp.stop();
    break;
    }
    case 2: //Red Single 5pt
    {
    deploy(intake, tower, ramp);
    intake.spin(directionType::fwd, 100, velocityUnits::pct);
    straight(bot, 200,30, true);
    straight(bot, 500,20, false);
    straight(bot, -200, 40, false);
    robotTurn(bot,400, 50);
    straight(bot, 600, 30, true);
    intake.stop();
    intake.spin(directionType::rev, 60, velocityUnits::pct);
    redacted::rampDown(ramp, intake);
    straight(bot, -500, 30, true);
    ramp.rotateTo(900, rotationUnits::deg, 50, velocityUnits::pct);
    ramp.stop();
    break;
    }
    case 3: //Either Alliance 1 pt
    {
      straight (bot, -1125, 50, false);
      straight (bot, 300, 50, true);
      deploy(intake, tower, ramp);
      break;
    }
    case 4:
    {
      break;
    }
  }
}

void redacted::rampDown(vex::motor ramp, vext::two intake) 
//This method is used in the auton to place the tower
{
  if(!macroOn) {
    macroOn = true;
  }
  else {
    macroOn = false;
    return;
  }
  ramp.rotateTo(1000, rotationUnits::deg, 100, velocityUnits::pct);
  intake.startRotateFor(-2000, rotationUnits::deg, 50, velocityUnits::pct);
  intake.startRotateFor(-2000, rotationUnits::deg, 50, velocityUnits::pct);
  ramp.rotateFor(1500, rotationUnits::deg, 75, velocityUnits::pct);
  intake.stop();
  macroOn = true;
}

