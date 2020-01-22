#include "vex.h"

enum mapType{
  LINEAR, //for normal like engine stuff if for claw
  EXPONENTIAL //for the motors and drivetrain
};

//returns the percent that 
float mapValuePercent(float n){
  return n * n * n / 10000;
}

//
float clip (float n, float lBound, float rBound) {
    if (n < lBound) n = lBound;
    if (n > rBound) n = rBound;
    return n;
}

directionType getDirection (float number) {
    if (number > 0.0) 
      return directionType(fwd);
    else 
      return directionType(rev);
}

void drive(motor Motor, float v){
  Motor.spin(getDirection(v), fabs(v), percent);
}
