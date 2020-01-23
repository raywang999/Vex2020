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
//           
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "math.h"
#include "myUtils.h"

using namespace vex;

namespace MotorBase {
  void Lift(bool up, bool down){
    if (up){
      drive(LeftMotorLift, 40);
      drive(RightMotorLift, -40);
    } 
    else if (down){
      drive(LeftMotorLift, -40);
      drive(RightMotorLift, 40);
    }
    else{
      //drive(LeftMotorLift, 0);
      //drive(RightMotorLift, 0);
      LeftMotorLift.stop(brakeType::hold);
      RightMotorLift.stop(brakeType::hold);
    }
  }
  void TranslateAndMove (float gamepad1LeftY, float gamepad1LeftX) {
        float leftDrive = gamepad1LeftY + gamepad1LeftX;
        float rightDrive = gamepad1LeftY - gamepad1LeftX;
        drive(LeftMotorBase, leftDrive);
        drive(RightMotorBase, rightDrive*-1);
  }
  void grip(){
    double rot = 0.25;
    Grip.rotateTo(rot*-1, rotationUnits::rev, false);
  }
  void release(){
    double rot = 0.25;
    Grip.rotateTo(rot, rotationUnits::rev, false);
  }
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

    MotorBase::TranslateAndMove(Controller1.Axis3.position(percent), Controller1.Axis4.position(percent));
    MotorBase::Lift(Controller1.ButtonL1.pressing(), Controller1.ButtonL2.pressing());
    Controller1.ButtonR1.pressed(MotorBase::grip);
    Controller1.ButtonR2.pressed(MotorBase::release);
    //MotorBase::Move();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

