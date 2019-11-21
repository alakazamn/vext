/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Michael                                                   */
/*    Created:      Fri May 24 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <iostream>

#include <future>
#include "vlib.cpp"

 
using namespace vex;

vex::brain       Brain;
vex::controller Controller;
vlib::motor RightMotor(vex::PORT2);
vlib::motor LeftMotor(vex::PORT1, true);
vlib::motor RightArm(vex::PORT16);
vlib::motor LeftArm(vex::PORT6);
vlib::motor RightFlapper(vex::PORT15);
vlib::motor LeftFlapper(vex::PORT5);

int main() { 
   vlib::controls::bindTwo(Controller.Axis1, Controller.Axis3, Controller.ButtonB, LeftMotor, RightMotor);
}