#include "vext.h"

#include <iostream>
/*
 * Implementation of vlib::chaindrive methods
 */

#define FWD vex::directionType::fwd
#define REV vex::directionType::rev

#define spin(a, b, pow, dir)                                                   \
  {                                                                            \
    a.spin(dir, pow, vex::velocityUnits::pct);                                 \
    b.spin(dir, pow, vex::velocityUnits::pct);                                 \
  }

#define cap(a, num)                                                            \
  {                                                                            \
    a = a > num ? num : a;                                                     \
    a = a < -num ? -num : a;                                                   \
  }

double calculateAngle(double angle) {
  return (angle > 180) ? angle - 360 : angle;
}

void vext::id::stop() { vext::four::stop(); }

void vext::id::straight(int power) { vext::four::straight(power); }

void vext::id::turn(int x, int y) { vext::four::turn(x, y); }

void vext::id::spinBy(double degrees, double speed) {
  vex::timer time;

  inert->resetRotation();
  double deg = degrees;
  if (vext::id::allianceColor == vext::alliance::BLUE) {
    deg *= -1;
  }
  deg = calculateAngle(inert->angle(vex::rotationUnits::deg)) + deg;
  while (deg > 180) {
    deg = deg - 360;
  }
  while (deg < -180) {
    deg = deg + 360;
  }
  
  // domain of degrees [-180, 180]
  auto pd = vext::pd(3.0 / 7, 25.0 / 21);
  while (time < 6000 && (fabs(deg - calculateAngle(inert->angle(vex::rotationUnits::deg))) > 0.8)) {
    std::cout << deg << " | "
              << calculateAngle(inert->angle(vex::rotationUnits::deg))
              << std::endl;
    double pID = pd.calculatePD(
        deg - calculateAngle(inert->angle(vex::rotationUnits::deg)));
    if (fabs(deg) < 10) {
      cap(pID, 10);
    } else {
      cap(pID, speed);
    }
    spin(leftA(), leftB(), pID, FWD);
    spin(rightA(), rightB(), pID, REV);
    vex::task::sleep(10);
  }
  stop();
}

#define currentInches leftA().rotation(vex::rotationUnits::rev) * M_PI *wh

void vext::id::moveBy(double inches, double speed) {
  vex::timer time;
  resetRotation();


  auto forwardPD = vext::pd(100.0/5, 2/7);
  auto sidePD = vext::pd(5.0 / 7, 8.0 / 21);
  const double targetAngle = calculateAngle(
      inert->angle(vex::rotationUnits::deg)); // initial angle serves as target
  const double target =
      currentInches + inches; // establish a final target using initial position
  double lastTime = time;
  while (time < 6000 && (fabs(target - currentInches) > fabs(inches) * .01 || fabs(calculateAngle(inert->angle(vex::rotationUnits::deg))) > .05)) {
    const double angle = calculateAngle(inert->angle(vex::rotationUnits::deg));
    double fPDV = forwardPD.calculatePD(target - currentInches, lastTime);

    std::cout << target - currentInches << std::endl;

    if (fabs(target - currentInches) < inches * .15) {
      cap(fPDV, 20);
    } else {
      cap(fPDV, speed);
    }

    const double sPDV = sidePD.calculatePD(targetAngle - angle, lastTime);
    spin(leftA(), leftB(), sPDV + fPDV, FWD);
    spin(rightA(), rightB(), sPDV - fPDV, REV);
    lastTime = time - lastTime;
  }
  stop();
}

// namespace vext
