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
  motors().leftA().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors().leftB().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors().rightA().rotateFor(vex::directionType::rev, revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, false);
  motors().rightB().rotateFor(vex::directionType::rev, revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, true);
}
#define maxLeft std::max(motors().leftA().rotation(vex::rotationUnits::rev), motors().leftB().rotation(vex::rotationUnits::rev))
#define maxRight std::max(motors().rightA().rotation(vex::rotationUnits::rev), motors().rightB().rotation(vex::rotationUnits::rev))

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
      motors().leftA().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      motors().leftB().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      motors().rightA().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      motors().rightB().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
    } else if(leftRot > rightRot) {
      motors().leftA().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      motors().leftB().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      //time * speed = change in revs
      //left change in revs / left speed = right change in revs / right speed
      //(speed * right rev) / l rev = r speed
      if(dL != 0) {
        motors().rightA().spin(vex::directionType::fwd, (speed * dR) / dL,
                              vex::velocityUnits::pct);
        motors().rightB().spin(vex::directionType::fwd, (speed * dR) / dL,
                              vex::velocityUnits::pct);
      } else {
        motors().rightA().stop();
        motors().rightB().stop();
      }
    } else if(rightRot < leftRot) {
      //time * speed = change in revs
      //left change in revs / left speed = right change in revs / right speed
      //(speed * l rev) / r rev = L speed
      if(dR != 0) {
        motors().leftA().spin(vex::directionType::fwd, (speed * dL) / dR,
                              vex::velocityUnits::pct);
        motors().leftB().spin(vex::directionType::fwd, (speed * dL) / dR,
                              vex::velocityUnits::pct);
      } else {
        motors().leftA().stop();
        motors().leftB().stop();
      }
      motors().rightA().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
      motors().rightB().spin(vex::directionType::fwd, speed,
                            vex::velocityUnits::pct);
    }

    std::cout << revs << "|" << maxLeft << "|"  << maxRight << std::endl;
  }
  motors().stop();
  /*motors().leftA().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors().leftB().rotateFor(vex::directionType::fwd, revs, vex::rotationUnits::rev, speed,
                        vex::velocityUnits::pct, false);
  motors().rightA().rotateFor(vex::directionType::rev, revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, false);
  motors().rightB().rotateFor(vex::directionType::rev, revs, vex::rotationUnits::rev, speed,
                         vex::velocityUnits::pct, true);
   double leftRot = std::max(motors().leftA().rotation(vex::rotationUnits::deg), motors().leftB().rotation(vex::rotationUnits::deg));
   double rightRot = std::max(motors().rightA().rotation(vex::rotationUnits::deg), motors().rightB().rotation(vex::rotationUnits::deg));
   if(leftRot > rightRot) {
     motors().rightA().startRotateTo(leftRot, vex::rotationUnits::deg);
     motors().rightB().rotateTo(leftRot, vex::rotationUnits::deg);
   }
   else if(rightRot > leftRot) {
     motors().leftA().startRotateTo(rightRot, vex::rotationUnits::deg);
     motors().leftB().rotateTo(rightRot, vex::rotationUnits::deg);
   }*/

}

void vext::fwd::straight(int power) { motors().straight(power); }

void vext::fwd::turn(int x, int y) { motors().turn(x, y); }

void vext::fwd::stop() { motors().stop(); }

void vext::fwd::stopCoast() { motors().setStopping(vex::brakeType::coast); motors().stop(); }

void vext::fwd::setMaxTorque(double value, vex::percentUnits units) {
  motors().leftA().setMaxTorque(value, units);
  motors().leftB().setMaxTorque(value, units);
  motors().rightA().setMaxTorque(value, units);
  motors().rightB().setMaxTorque(value, units);
}

void vext::fwd::resetRotation() {
  motors().leftA().resetRotation();
  motors().leftB().resetRotation();
  motors().rightA().resetRotation();
  motors().rightB().resetRotation();
}

void vext::fwd::rotateTo( double rotation, vex::rotationUnits units, double velocity, vex::velocityUnits units_v ) {
  motors().leftA().startRotateTo(rotation,units,velocity,units_v);
  motors().leftB().startRotateTo(rotation,units,velocity,units_v);
  motors().rightA().rotateTo(rotation,units,velocity,units_v);
  motors().rightB().rotateTo(rotation,units,velocity,units_v);
}

void vext::fwd::bind(vex::controller::axis x, vex::controller::axis y) {
  static auto moveUpdate = [&] {
    if (direction(y) != 0 || direction(x) !=0) { // axis 1 and axis 3
      turn(x.position(), y.position());
    } else {
      stop();
    }
  };

  y.changed([] { moveUpdate(); });
  x.changed([] { moveUpdate(); });
}


// namespace vlib
