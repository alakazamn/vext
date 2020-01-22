#include "vex.h"
#include "vext.h"

using namespace vex;

#ifndef REDACTED_H
#define REDACTED_H

extern bool macroOn;

class redacted {
public:
  static void setRampMacroActivated(bool active) { macroOn = active; }
  static bool rampMacroActivated() { return macroOn; }

  /*
  *
  */
  static void rampDown(vex::motor ramp, vext::two intake);

  static void pre_auton(vex::controller Controller, vex::brain Brain);

  static void auton(vext::fwd bot, vext::two intake, vex::motor ramp,
                    vex::motor tower);

  static void updateSpeedMode(int speedMode, vext::fwd);
};

#endif