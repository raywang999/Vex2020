using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor MotorBaseNW;
extern motor MotorBaseNE;
extern motor MotorBaseSE;
extern motor MotorBaseSW;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );