/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       haojixu                                                   */
/*    Created:      Tue Nov 26 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// MotorBaseNW          motor         1               
// MotorBaseNE          motor         2               
// MotorBaseSE          motor         3               
// MotorBaseSW          motor         4               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "math.h"

using namespace vex;

namespace myUtils {
  // Returns the clipped value of a number. Clip 'number' if 'number' is less than 'min' or greater than 'max'
  float clip (float n, float lBound, float rBound) {
    if (n < lBound) n = lBound;
    if (n > rBound) n = rBound;
    return n;
  }
}

namespace MotorBase {
  directionType getDirection (float number) {
    if (number > 0.0) return directionType(fwd);
    else return directionType(rev);
  }

  void TranslateAndMove (float gamepad1LeftY, float gamepad1LeftX, float gamepad1RightX) {
        // float gamepad1LeftY = -gamepad1.left_stick_y;
        // float gamepad1LeftX = gamepad1.left_stick_x;
        // float gamepad1RightX = gamepad1.right_stick_x;

        // holonomic formulas

        float FrontLeft = (-gamepad1LeftY - gamepad1LeftX - gamepad1RightX);
        float FrontRight = (gamepad1LeftY - gamepad1LeftX - gamepad1RightX);
        float BackRight = (gamepad1LeftY + gamepad1LeftX - gamepad1RightX);
        float BackLeft = (-gamepad1LeftY + gamepad1LeftX - gamepad1RightX);

        // clip the right/left values so that the values never exceed +/- 1
        FrontRight = myUtils::clip(FrontRight, -100, 100);
        FrontLeft = myUtils::clip(FrontLeft, -100, 100);
        BackLeft = myUtils::clip(BackLeft, -100, 100);
        BackRight = myUtils::clip(BackRight, -100, 100);

        // write the values to the motors
        MotorBaseNE.spin(getDirection(FrontRight), fabs(FrontRight), percent);
        MotorBaseNW.spin(getDirection(FrontLeft), fabs(FrontLeft), percent);
        MotorBaseSW.spin(getDirection(BackLeft), fabs(BackLeft), percent);
        MotorBaseSE.spin(getDirection(BackRight), fabs(BackRight), percent);
  }

  void Move () {
    MotorBaseNE.power();
    MotorBaseNW.power();
    MotorBaseSE.power();
    MotorBaseSW.power();
  }
}

namespace Events {
  
}

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    MotorBase::TranslateAndMove(Controller1.Axis3.position(percent), Controller1.Axis4.position(percent), Controller1.Axis1.position(percent));

    MotorBase::Move();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  //Controller1.Screen.print()
  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

