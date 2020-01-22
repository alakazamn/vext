#include "vex.h"
#include "vext.h"

using namespace vex;

  #ifndef   REDACTED_H
  #define   REDACTED_H

  extern bool macroOn;

  class redacted {
    public:
      static void setRampMacroActivated(bool active) {
        macroOn = active;
      }
      static bool rampMacroActivated() {
        return macroOn;
      }
      static void rampDown(vex::motor ramp, vext::two intake); 
  };


#endif