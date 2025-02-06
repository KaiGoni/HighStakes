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
// Robot configuration code.
// motor leftMotorA = motor(PORT1, ratio6_1, false);
// motor leftMotorB = motor(PORT2, ratio6_1, false);
// motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
// motor rightMotorA = motor(PORT3, ratio6_1, true);
// motor rightMotorB = motor(PORT4, ratio6_1, true);
// motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
// drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 31, 200, mm, 0.6);

// motor leftIntakeMotorA = motor(PORT17, ratio6_1, false);
// motor leftIntakeMotorB = motor(PORT18, ratio6_1, true);
// motor_group leftIntake = motor_group(leftIntakeMotorA, leftIntakeMotorB);
// motor rightIntakeMotorA = motor(PORT19, ratio6_1, false);
// motor rightIntakeMotorB = motor(PORT20, ratio6_1, false);
// motor_group rightIntake = motor_group(rightIntakeMotorA, rightIntakeMotorB);

// controller Controller1 = controller(primary);

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while (true) {
    // calculate the drivetrain motor velocities from the controller joystick axies
    // int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis4.position();
    // int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis4.position();

    // // If values in deadband range, stop the drive motors and skip the motor control
    // if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5 && drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
    //   // Stop the drive motors
    //   LeftDriveSmart.stop();
    //   RightDriveSmart.stop();
    // } else {
    //   // Motor Control
    //   LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
    //   LeftDriveSmart.spin(forward);
    //   RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
    //   RightDriveSmart.spin(forward);
    // }

    // Intake Control
    // if (Controller1.ButtonX.pressing()) {
    //   leftIntake.spin(forward);
    //   rightIntake.spin(forward);
    // } else if (Controller1.ButtonB.pressing()) {
    //   leftIntake.spin(reverse);
    //   rightIntake.spin(reverse);
    // } else {
    //   leftIntake.stop();
    //   rightIntake.stop();
    // }

    // Goal Lift Control

    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void)
{

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is usedd to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void)
{
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  // Move forward 1000 mm
  // Drivetrain.driveFor(forward, 1000, vex::mm);
}

// print the current motor position

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void)
{
  // User control code here, inside the loop
  // while (1) {
  // This is the main execution loop for the user control program.
  // Each time through the loop your program should update motor + servo
  // values based on feedback from the joysticks.

  // ........................................................................
  // Insert user code here. This is where you use the joystick values to
  // update your motors, etc.
  // ........................................................................

  wait(20, msec); // Sleep the task for a short amount of time to
                  // prevent wasted resources.
  // }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}