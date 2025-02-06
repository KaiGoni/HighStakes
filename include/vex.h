#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)



vex::motor leftMotorA = vex::motor(vex::PORT19, vex::ratio6_1, false);
vex::motor leftMotorB = vex::motor(vex::PORT20, vex::ratio6_1, false);
vex::motor_group LeftDriveSmart = vex::motor_group(leftMotorA, leftMotorB);
vex::motor rightMotorA = vex::motor(vex::PORT12, vex::ratio6_1, true);
vex::motor rightMotorB = vex::motor(vex::PORT11, vex::ratio6_1, true);
vex::motor_group RightDriveSmart = vex::motor_group(rightMotorA, rightMotorB);
vex::drivetrain Drivetrain = vex::drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 31, 200, vex::mm, 0.6);

vex::motor leftIntakeMotorA = vex::motor(vex::PORT17, vex::ratio6_1, false);
vex::motor leftIntakeMotorB = vex::motor(vex::PORT18, vex::ratio6_1, true);
vex::motor_group leftIntake = vex::motor_group(leftIntakeMotorA, leftIntakeMotorB);

vex::motor rightIntakeMotorA = vex::motor(vex::PORT1, vex::ratio6_1, true);
vex::motor rightIntakeMotorB = vex::motor(vex::PORT2, vex::ratio6_1, false);
vex::motor_group rightIntake = vex::motor_group(rightIntakeMotorA, rightIntakeMotorB);

vex::controller Controller1 = vex::controller(vex::primary);