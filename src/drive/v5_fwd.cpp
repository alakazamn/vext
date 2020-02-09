#import "vext/drive/v5_drive.h"

#import "vext/drive/v5_fwd.h"

#include "vex_units.h"
#include <iostream>
/*
 * Implementation of vlib::chaindrive methods
 */

void vext::fwd::spinBy(double degrees, double speed) {
  resetRotation();
  double revs = ((degrees / 360.0) * diag) / 4;
  leftA().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  leftB().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  rightA().rotateFor(vex::directionType::rev, revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, false);
  rightB().rotateFor(vex::directionType::rev, revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, true);
}
#define maxLeft std::max(leftA().rotation(vex::rotationUnits::rev), leftB().rotation(vex::rotationUnits::rev))
#define maxRight std::max(rightA().rotation(vex::rotationUnits::rev), rightB().rotation(vex::rotationUnits::rev))

void vext::fwd::moveBy(double inches, double speed) {
  double revs = inches / (wh * M_PI);
  resetRotation();

  while(maxLeft < revs || maxRight < revs) {
     vex::controller Controller;


    double leftRot = maxLeft;
    double rightRot = maxRight;
    double dL = revs - leftRot;
    double dR = revs - leftRot;

    if(leftRot == rightRot) {
      leftA().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      leftB().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      rightA().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      rightB().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
    } else if(leftRot > rightRot) {
      leftA().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      leftB().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      //time * speed = change in revs
      //left change in revs / left speed = right change in revs / right speed
      //(speed * right rev) / l rev = r speed
      if(dL != 0) {
        rightA().spin(vex::directionType::fwd, (speed * dR) / dL,
                              vex::velocityUnits::pct);
        rightB().spin(vex::directionType::fwd, (speed * dR) / dL,
                              vex::velocityUnits::pct);
      } else {
        rightA().stop();
        rightB().stop();
      }
    } else if(rightRot < leftRot) {
      //time * speed = change in revs
      //left change in revs / left speed = right change in revs / right speed
      //(speed * l rev) / r rev = L speed
      if(dR != 0) {
        leftA().spin(vex::directionType::fwd, (speed * dL) / dR,
                              vex::velocityUnits::pct);
        leftB().spin(vex::directionType::fwd, (speed * dL) / dR,
                              vex::velocityUnits::pct);
      } else {
        leftA().stop();
        leftB().stop();
      }
      rightA().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      rightB().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
    }

    std::cout << revs << "|" << maxLeft << "|"  << maxRight << std::endl;
  }
  stop();
}

void vext::fwd::straight(int power) { vext::four::straight(power); }

void vext::fwd::turn(int x, int y) { vext::four::turn(x, y); }

void vext::fwd::stop() { vext::four::stop(); }

void vext::fwd::stopCoast() { setStopping(vex::brakeType::coast); stop(); }

void vext::fwd::setMaxTorque(double value, vex::percentUnits units) {
  leftA().setMaxTorque(value, units);
  leftB().setMaxTorque(value, units);
  rightA().setMaxTorque(value, units);
  rightB().setMaxTorque(value, units);
}

void vext::fwd::resetRotation() {
  leftA().resetRotation();
  leftB().resetRotation();
  rightA().resetRotation();
  rightB().resetRotation();
}

void vext::fwd::rotateTo( double rotation, vex::rotationUnits units, double velocity, vex::velocityUnits units_v ) {
  leftA().startRotateTo(rotation,units,velocity,units_v);
  leftB().startRotateTo(rotation,units,velocity,units_v);
  rightA().rotateTo(rotation,units,velocity,units_v);
  rightB().rotateTo(rotation,units,velocity,units_v);
}

void vext::fwd::bind(vex::controller::axis x, vex::controller::axis y) {
  static auto moveUpdate = [&] {
    if (axisDirection(y) != 0 || axisDirection(x) !=0) { // axis 1 and axis 3
      turn(x.position(), y.position());
    } else {
      stop();
    }
  };

  y.changed([] { moveUpdate(); });
  x.changed([] { moveUpdate(); });
}


// namespace vlib
