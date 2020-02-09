#include "vex.h"

#ifndef VEXT_PD_H
#define VEXT_PD_H

/*-----------------------------------------------------------------------------*/
/* @file   v5_id.h
 * @brief   This class utilizes the vlib::four motorgroup to provide
 *          functionality for building a four-wheel drive.
 *          Controller binding is provided with a function,
 *          intended for two-stick control.
 *          Some of the methods are intended for use with autons.
 *          This class uses an inertial sensor to make more accurate
 *          movement
 *//*---------------------------------------------------------------------------*/

namespace vext {
    /*! \addtogroup drive
    *  @{
    */
    class pd {
    /*! @} */
    private:
        double kP = 12/7; 
        double kD = 8.0/21;
        double lastError = 0;
    public:
      pd() { };

      /*
      * Construct a chaindrive with left and right motors
      * @param left Left port
      * @param right Right port
      */
      pd(double p, double d) {
        kP = p;
        kD = d;
      };

      void setConstants(double p, double d) {
        kP = p;
        kD = d;
      }

      double calculatePD(double error) {
        double dPart = ((error - lastError) / 10) * kD;
        return (kP * error) + dPart;
      }
    };
} // namespace vext
#endif
