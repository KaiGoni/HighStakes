/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Anthony Wong                                              */
/*    Created:      12/30/2024                                                */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;

// define your global instances of motors and other devices here

motor leftMotorA = motor(PORT1, ratio6_1, false);
motor leftMotorB = motor(PORT2, ratio6_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT3, ratio6_1, true);
motor rightMotorB = motor(PORT4, ratio6_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 31, 200, mm, 0.6);

motor leftIntakeMotorA = motor(PORT17, ratio6_1, false);
motor leftIntakeMotorB = motor(PORT18, ratio6_1, true);
motor_group leftIntake = motor_group(leftIntakeMotorA, leftIntakeMotorB);
motor rightIntakeMotorA = motor(PORT19, ratio6_1, false);
motor rightIntakeMotorB = motor(PORT20, ratio6_1, false);
motor_group rightIntake = motor_group(rightIntakeMotorA, rightIntakeMotorB);

digital_out pnematicPort = digital_out(Brain.ThreeWirePort.A);
controller Controller1 = controller(primary);

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
double fabs(double x) {
    return (x < 0) ? -x : x;
}

double sqrt(double x) {
    double guess = x / 2.0;
    double epsilon = 0.0001;  // This controls the precision of the result
    
    while (fabs(guess * guess - x) > epsilon) {
        guess = (guess + x / guess) / 2.0;
    }
    
    return guess;
}

double atan(double x) {
    double result = x;
    double term = x;  // First term in the series
    double x_squared = x * x;
    int n = 1;  // Start with the first term

    // Iterate to calculate a better approximation
    while (term > 0.00001 || term < -0.00001) {
        n += 2;
        term = (-1) * term * x_squared * (n - 1) / n;
        result += term;
    }

    return result;
}

double atan2(double y, double x) {
    if (x > 0) {
        return atan(y / x);  // First quadrant
    } else if (x < 0 && y >= 0) {
        return atan(y / x) + M_PI;  // Second quadrant
    } else if (x < 0 && y < 0) {
        return atan(y / x) - M_PI;  // Third quadrant
    } else if (x == 0 && y != 0) {
        return (y > 0) ? M_PI / 2 :  -M_PI / 2;  // Handle vertical line case
    } else {
        return 0;  // Undefined or zero case
    }
}

void driveTo(int posX, int posY) {
  // Get current values
  int currentPosX = 0; // Current Pos to be determined
  int currentPosY = 0;
  int currentHeading = 0; // Current heading to be determined
  double deltaX = posX - currentPosX;
  double deltaY = posY - currentPosY;
  
  // Calculate distance and angle
  double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
  double angle = atan2(deltaY, deltaX) * 180 / M_PI;
  
  // Drivetrain.turnToHeading(angle, degrees);
  // Drivetrain.driveFor(forward, distance, mm);
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  Drivetrain.driveFor(forward, 300, mm);
  wait(1000, msec);
  driveTo(300, 300);
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

// "when started" hat block
int whenStarted1() {
  pnematicPort.set(false);
  return 0;
}

// "when ButtonL1 pressed
void pnematics_push() {
  pnematicPort.set(true);
}

// "when ButtonL2 pressed
void pnematics_pull() {
  pnematicPort.set(false);
}

void usercontrol(void) {
  // User control code here, inside the loop
  whenStarted1();
  while (1) {
    
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // calculate the drivetrain motor velocities from the controller joystick axies
    int drivetrainLeftSideSpeed = (Controller1.Axis3.position() * 0.8) + (Controller1.Axis1.position() * 0.6);
    int drivetrainRightSideSpeed = (Controller1.Axis3.position() * 0.8) - (Controller1.Axis1.position() * 0.6);

    // If values in deadband range, stop the drive motors and skip the motor control
    if (Controller1.Axis1.position() < 5 && Controller1.Axis1.position() > -5 && Controller1.Axis2.position() < 5 && Controller1.Axis2.position() > -5 && Controller1.Axis3.position() < 5 && Controller1.Axis3.position() > -5 && Controller1.Axis4.position() < 5 && Controller1.Axis4.position() > -5) {
      // Stop the drive motors
      LeftDriveSmart.stop();
      RightDriveSmart.stop();
    } else {
      // Motor Control
      LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
      LeftDriveSmart.spin(forward);
      RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
      RightDriveSmart.spin(forward);
    }

    // Intake Control
    if (Controller1.ButtonX.pressing()) {
      leftIntake.spin(forward);
      rightIntake.spin(forward);
    } else if (Controller1.ButtonB.pressing()) {
      leftIntake.spin(reverse);
      rightIntake.spin(reverse);
    } else {
      leftIntake.stop();
      rightIntake.stop();
    }

    // Pnematics Push/Pull
    Controller1.ButtonL1.pressed(pnematics_push);
    Controller1.ButtonL2.pressed(pnematics_pull);

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

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}