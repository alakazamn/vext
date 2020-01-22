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

/*void redacted::straight(double degrees, double speed, bool coast) //This method is used as a fast way to write in straights and the ability to coast is also given
{
  LeftMotor.resetRotation();
  LeftMotor2.resetRotation();
  RightMotor.resetRotation();
  RightMotor2.resetRotation();
  LeftMotor.startRotateTo(degrees,rotationUnits::deg,speed,velocityUnits::pct);
  LeftMotor2.startRotateTo(degrees,rotationUnits::deg,speed,velocityUnits::pct);
  RightMotor.rotateTo(degrees,rotationUnits::deg,speed,velocityUnits::pct);
  RightMotor2.rotateTo(degrees,rotationUnits::deg,speed,velocityUnits::pct);
  if(coast==true)
  {
    LeftMotor.stop(brakeType::coast);
    LeftMotor2.stop(brakeType::coast);
    RightMotor.stop(brakeType::coast);
    RightMotor2.stop(brakeType::coast);
  }
  while(LeftMotor.isSpinning()&&RightMotor.isSpinning())
  {
    wait(10);
  }
}*/
