// TO DO: Controllers testing, Autonomous

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Anthony Wong & Zara Alom                                  */
/*    Created:      12/30/2024                                                */
/*    Description:  VEX High Stakes Competition Code                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;

// define your global instances of motors and other devices here

motor leftMotorA = motor(PORT18, ratio6_1, true);
motor leftMotorB = motor(PORT17, ratio6_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT10, ratio6_1, false);
motor rightMotorB = motor(PORT9, ratio6_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 31, 200, mm, 0.6);

motor intake = motor(PORT20, ratio6_1, true);
motor hook = motor(PORT16, ratio6_1, false);

digital_out pnematicPort = digital_out(Brain.ThreeWirePort.A);
controller Controller1 = controller(primary);

float driveTrainSpeed = 100;

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
  
  intake.setVelocity(100, percent);
}

// "when ButtonL1 pressed
void pnematics_push() {
  pnematicPort.set(true);
}

// "when ButtonL2 pressed
void pnematics_pull() {
  pnematicPort.set(false);
}

void driveTo(int posX, int posY, bool reverse) {
  // Get current values
  int currentPosX = 0; // Current Pos to be determined
  int currentPosY = 0;
  int currentHeading = 0; // Current heading to be determined
  float deltaX = posX - currentPosX;
  float deltaY = posY - currentPosY;
  
  // Calculate distance and angle
  float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
  float angle = atan2(deltaY, deltaX) * 180 / M_PI;
  if(reverse == true) {
    currentHeading -= 180;
  }
  if(currentHeading - angle > 180) {
    currentHeading -= 360;
  } else if(currentHeading - angle < -180) {
    currentHeading += 360;
  }
  
  Drivetrain.turnFor(right, angle - currentHeading, degrees);
  Drivetrain.driveFor(forward, distance, mm);
  currentPosX = posX;
  currentPosY = posY;
  currentHeading = angle;
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
  // ..........................................................................d
  intake.setVelocity(100, percent);
  intake.spin(forward);
  wait(2, sec);
  intake.stop();
  wait(2, sec);
  intake.spin(forward);
  wait(2, sec);
  intake.stop();
  wait(2, sec);
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
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // calculate the drivetrain motor velocities from the controller joystick axies
    float drivetrainLeftSideSpeed = ((Controller1.Axis3.position() * 0.8) + (Controller1.Axis1.position() * 0.6)) * (driveTrainSpeed / 100);
    float drivetrainRightSideSpeed = ((Controller1.Axis3.position() * 0.8) - (Controller1.Axis1.position() * 0.6)) * (driveTrainSpeed / 100);

    // If values in deadband range, stop the drive motors and skip the motor control
    if (fabs(Controller1.Axis1.position()) < 5 &&
     fabs(Controller1.Axis2.position()) < 5 &&
     fabs(Controller1.Axis3.position()) < 5 &&
     fabs(Controller1.Axis4.position()) < 5) {

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

    // Intake/Hook Control
    if(Controller1.ButtonR1.pressing()) {
      hook.spin(forward);
    } 
    if(Controller1.ButtonR2.pressing()) {
      intake.spin(forward);
    }
    if(Controller1.ButtonB.pressing() && !Controller1.ButtonR1.pressing() && !Controller1.ButtonR2.pressing()) {
      hook.spin(reverse);
      intake.spin(reverse);
    }

    // Pnematics Control
    Controller1.ButtonL1.pressed(pnematics_push);
    Controller1.ButtonL2.pressed(pnematics_pull);

    // Control drivetrain speed
    if(Controller1.ButtonRight.pressing()) {
      driveTrainSpeed = 100;
    } else if (Controller1.ButtonUp.pressing()) {
      driveTrainSpeed = 75;
    } else if (Controller1.ButtonLeft.pressing()) {
      driveTrainSpeed = 50;
    }

    // Sleep the task for a short amount of time to prevent wasted resources.
    wait(20, msec);
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