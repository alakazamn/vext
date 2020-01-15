#import "drive/v5_fwd.h"

#include "vex_units.h"
#include <iostream>
/*
 * Implementation of vlib::chaindrive methods
 */


/*
  Getters and Setters for specific motors in group (something missing from vex::motor_group)
*/
vex::motor_group vext::fwd::left() { return left_group; }
vex::motor_group vext::fwd::right() { return right_group; }


