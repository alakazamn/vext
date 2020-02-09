#import "vext/drive/v5_drive.h"

#import "vext/drive/v5_id.h"

#include "vex_units.h"
#include <iostream>
/*
 * Implementation of vlib::chaindrive methods
 */

double calculateAngle(double angle) {
      return (angle  > 180) ? angle - 360 : angle;
}
void vext::id::spinBy(double degrees, double speed, double kP, double kD) {
  double deg = degrees;
  if(vext::id::allianceColor == vext::alliance::BLUE) {
    deg *= -1;
  }
  while(deg > 180) {
    deg = 360-degrees;
  }
  while(deg < -180) {
    deg = 360+degrees;
  }
  std::cout << vext::id::allianceColor.toString() <<std::endl;
  //domain of degrees [-180, 180]
    double lastError = 0;

    while(calculateAngle(inert->angle(vex::rotationUnits::deg)) != deg) {
      const double error = deg - calculateAngle(inert->angle(vex::rotationUnits::deg));
      double dPart = ((error - lastError) / 10) * kD;

      double pID = (kP*error) + dPart;
      if(fabs(deg) < 10) {
        pID = pID > 10 ? 10 : pID;
        pID = pID < -10 ? -10 : pID;
      } else {
        pID = pID > speed ? speed : pID;
        pID = pID < -speed ? -speed : pID;
      }
      
      std::cout << error << "|" << calculateAngle(inert->angle(vex::rotationUnits::deg)) << "|" << deg << std::endl;
        leftA().spin(vex::directionType::fwd, pID,
                              vex::velocityUnits::pct);
        leftB().spin(vex::directionType::fwd, pID,
                              vex::velocityUnits::pct);
        rightA().spin(vex::directionType::rev, pID,
                              vex::velocityUnits::pct);
        rightB().spin(vex::directionType::rev, pID,
                              vex::velocityUnits::pct);
        vex::task::sleep(10);
    }
  std::cout << "?" << calculateAngle(inert->angle(vex::rotationUnits::deg)) << "|" << deg << std::endl;
  stop();
}
#define maxLeft std::max(leftA().rotation(vex::rotationUnits::rev), leftB().rotation(vex::rotationUnits::rev))
#define maxRight std::max(rightA().rotation(vex::rotationUnits::rev), rightB().rotation(vex::rotationUnits::rev))

void vext::id::moveBy(double inches, double speed) {
  resetRotation();
  //inert->resetRotation();

  double revs = inches / (wh * M_PI);
  vex::directionType dir = inches * speed > 0 ? vex::directionType::fwd : vex::directionType::rev;
  while(maxLeft < std::fabs(revs) || maxRight < std::fabs(revs)) {
    vex::controller Controller;

    double angle = (inert->angle(vex::rotationUnits::deg) > 180) ? inert->angle(vex::rotationUnits::deg) - 360 : inert->angle(vex::rotationUnits::deg);
    if(angle == 0) {
      leftA().spin(dir, speed,
                            vex::velocityUnits::pct);
      leftB().spin(dir, speed,
                            vex::velocityUnits::pct);
      rightA().spin(dir, speed,
                            vex::velocityUnits::pct);
      rightB().spin(dir, speed,
                            vex::velocityUnits::pct);
    }
    else if(angle < 0) {
      leftA().spin(dir, speed,
                            vex::velocityUnits::pct);
      leftB().spin(dir, speed,
                            vex::velocityUnits::pct);

      rightA().spin(dir, (speed/90) * (angle + 90),
                            vex::velocityUnits::pct);
      rightB().spin(dir, (speed/90) * (angle + 90),
                            vex::velocityUnits::pct);
    }
    else if(angle > 0) {
      leftA().spin(dir, (speed/90) * (-angle + 90),
                            vex::velocityUnits::pct);
      leftB().spin(dir, (speed/90) * (-angle + 90),
                            vex::velocityUnits::pct);

      rightA().spin(dir, speed,
                            vex::velocityUnits::pct);
      rightB().spin(dir, speed,
                            vex::velocityUnits::pct);
    }
    std::cout << angle << " | " << std::fabs(revs) << " | " << maxLeft << " | "<< maxRight << " | "<< std::endl;
  }
  stop();
}


// namespace vlib
