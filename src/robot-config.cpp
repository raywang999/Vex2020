#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor LeftMotorBase = motor(PORT1, ratio18_1, false);
motor RightMotorBase = motor(PORT2, ratio18_1, false);
motor LeftMotorLift = motor(PORT3, ratio18_1, false);
motor RightMotorLift = motor(PORT4, ratio18_1, false);
motor temp1 = motor(PORT7, ratio18_1, false);
motor temp2 = motor(PORT8, ratio18_1, false);
//motor MotorBaseSE = motor(PORT3, ratio18_1, false);
//motor MotorBaseSW = motor(PORT4, ratio18_1, false);
controller Controller1 = controller(primary);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}