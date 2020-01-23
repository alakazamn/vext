#include "vex.h"

/*-----------------------------------------------------------------------------*/
/** @file   v5_motor.h
 * @brief   This is just the vanilla VEX motor class, but with some methods that
 *          allow interchangeability for binding either one, two, or four motor
 *          groups.
 *//*---------------------------------------------------------------------------*/

#ifndef   VEXT_MOTOR_CLASS_H
#define   VEXT_MOTOR_CLASS_H

namespace vext {
  
  class motor : public vex::motor {
    public:
     /** 
     * @prog_lang{cpp|pro}
     * @drawer_cat{constructor}
     * @block_sig{vex::motor Motor = vex::motor(vex::PORT1);}     
     * @brief Creates a new motor object on the port specified.
     * @param index The port index for this motor. The index is zero-based.
     */
      motor( int32_t index ) : vex::motor(index) {};  
      ~motor() {

      }

     /** 
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::motor Motor = vex::motor(vex::PORT1, false);}
      * @brief Creates a new motor object on the port specified and sets the reversed flag.
      * @param index The port index for this motor. The index is zero-based.
      * @param reverse Sets the reverse flag for the new motor object.
      */
      motor( int32_t index, bool reverse ) : vex::motor(index, reverse) {};

     /** 
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::motor Motor = vex::motor(vex::PORT1, vex::gearSetting::ratio18_1);}
      * @brief Creates a new motor object on the port specified and sets the gear setting
      * @param index The port index for this motor. The index is zero-based.
      * @param gears Sets the gear's setting for the new motor object.
      */  
      motor( int32_t index, vex::gearSetting gears ) : vex::motor(index, gears) {};

      /** 
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::motor Motor = vex::motor(vex::PORT1, vex::gearSetting::ratio18_1, false);}
      * @brief Creates a new motor object on the port specified Sets the reversed flag and the gear setting for the new motor object.
      * @param index The port index for this motor. The index is zero-based.
      * @param gears Sets the gear's setting for the new motor object.
      * @param reverse Sets the reverse flag for the new motor object.
      */  
      motor( int32_t index, vex::gearSetting gears, bool reverse ) : vex::motor(index, gears, reverse) {};

      void straight(int power) {
        vex::directionType direction =
            power < 0 ? vex::directionType::fwd : vex::directionType::rev;
        spin(direction, abs(power), vex::percentUnits::pct);
      }

      void stop(vex::brakeType brake) {
        vex::motor::stop(brake);
      }
      void stop() {
        vex::motor::stop(vex::brakeType::hold);
      }
    };
  }

  #endif