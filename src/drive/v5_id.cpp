#import "vext/drive/v5_drive.h"

#import "vext/v5_pd.h"

#import "vext/drive/v5_id.h"

#include "vex_units.h"
#include <iostream>
/*
 * Implementation of vlib::chaindrive methods
 */

double calculateAngle(double angle) {
  return (angle > 180) ? angle - 360 : angle;
}
void vext::id::spinBy(double degrees, double speed) {
  double deg = degrees;
  if (vext::id::allianceColor == vext::alliance::BLUE) {
    deg *= -1;
  }
  while (deg > 180) {
    deg = 360 - degrees;
  }
  while (deg < -180) {
    deg = 360 + degrees;
  }
  std::cout << vext::id::allianceColor.toString() << std::endl;
  // domain of degrees [-180, 180]
  auto pd = vext::pd();
  while (true) {
    double pID = pd.calculatePD(deg - calculateAngle(inert->angle(vex::rotationUnits::deg)));
    if (fabs(deg) < 10) {
      pID = pID > 10 ? 10 : pID;
      pID = pID < -10 ? -10 : pID;
    } else {
      pID = pID > speed ? speed : pID;
      pID = pID < -speed ? -speed : pID;
    }
    leftA().spin(vex::directionType::fwd, pID, vex::velocityUnits::pct);
    leftB().spin(vex::directionType::fwd, pID, vex::velocityUnits::pct);
    rightA().spin(vex::directionType::rev, pID, vex::velocityUnits::pct);
    rightB().spin(vex::directionType::rev, pID, vex::velocityUnits::pct);
    vex::task::sleep(10);

    if(fabs(pID) <=2) {
      break;
    }
  }
  stop();
}
#define maxLeft                                                                \
  std::max(leftA().rotation(vex::rotationUnits::rev),                          \
           leftB().rotation(vex::rotationUnits::rev))
#define maxRight                                                               \
  std::max(rightA().rotation(vex::rotationUnits::rev),                         \
           rightB().rotation(vex::rotationUnits::rev))

void vext::id::moveBy(double inches, double speed) {
  resetRotation();
  
  double revs = inches / (wh * M_PI);

  auto forwardPD = vext::pd(100,  2.0/21);
  auto sidePD = vext::pd(2.0/7, 8.0/21);
  const double initialAngle = calculateAngle(inert->angle(vex::rotationUnits::deg));
  while (true) {
    double angle = calculateAngle(inert->angle(vex::rotationUnits::deg));
                    
    double fPDV =forwardPD.calculatePD(revs-leftA().rotation(vex::rotationUnits::rev));

    if (fabs(revs-leftA().rotation(vex::rotationUnits::rev)) < revs*.1) {
      fPDV = fPDV > 20 ? 20 : fPDV;
      fPDV = fPDV < -20 ? -20 : fPDV;
    } else {
      fPDV = fPDV > speed ? speed : fPDV;
      fPDV = fPDV < -speed ? -speed : fPDV;
    }

    double sPDV =sidePD.calculatePD(initialAngle-angle);
    vex::controller Controller;

                   
    leftA().spin(vex::directionType::fwd, sPDV+fPDV, vex::velocityUnits::pct);
    leftB().spin(vex::directionType::fwd, sPDV+fPDV, vex::velocityUnits::pct);
    rightA().spin(vex::directionType::rev, sPDV-fPDV, vex::velocityUnits::pct);
    rightB().spin(vex::directionType::rev, sPDV-fPDV, vex::velocityUnits::pct);
  }
  stop();
}

// namespace vlib
