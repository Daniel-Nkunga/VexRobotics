#include "vex.h"

using namespace vex;

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Left                 motor_group   4, 5            
// Right                motor_group   7, 6            
// Arm                  motor         1               
// Controller1          controller                    
// Flywheel             motor         11              
// RWing                motor         3               
// LWing                motor         2               
// Pneumatic            digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

competition Competition;

//Threading
void R_TRThreadFunction90(){
  Right.spinFor(reverse, 680, degrees);
}
void R_TLThreadFunction90(){
  Right.spinFor(forward, 680, degrees);
}
void R_DFThreadFunction(){
  Right.spinFor(forward, 3100, degrees);
}
void R_DFSThreadFunction(){
  Right.spinFor(forward, 300, degrees);
}
void R_DRLThreadFunction(){
  Right.spinFor(reverse,1200, degrees);
}
void R_DRThreadFunction(){
  Right.spinFor(reverse, 300, degrees);
}
void RWingOpen() {
  RWing.spin(forward);
}
void RWingClose() {
  RWing.spin(reverse);
}
void LWingOpen() {
  LWing.spin(reverse);
}
void LWingClose() {
  LWing.spin(forward);
}
void speed(){
  Right.setVelocity(80, percent);
  Left.setVelocity(80, percent);
}
void slow(){
  Right.setVelocity(25, percent);
  Left.setVelocity(25, percent);
}
void LWingTaskFunction() {
  LWing.spin(forward);
}

void WingsOpen(){
  thread RWing(RWingOpen);
  thread LWing(LWingOpen);
}

void WingsClose(){
  thread RWing(RWingClose);
  thread LWing(LWingClose);
}

void ArmLift(){
  Arm.spin(forward);
}
void ArmLower(){
  Arm.spin(reverse);
}

void autonomous(){ //Aiming for win point
  Right.setVelocity(25, percent);
  Left.setVelocity(25, percent);
  Arm.setPosition(0, degrees);
  Pneumatic.set(false);
  thread Right(R_DFThreadFunction);
  Left.spinFor(forward, 1800, degrees);
  speed();
  thread Right2(R_DRThreadFunction);
  Left.spinFor(reverse, 400, degrees);
  thread Right3(R_DFSThreadFunction);
  Left.spinFor(forward, 400, degrees);
  thread Right4(R_DRLThreadFunction);
  slow();
  Left.spinFor(reverse, 1200, degrees);
  Arm.spinToPosition(560, degrees);
}

void userControl(){
  Left.setVelocity(100, percent);
  Right.setVelocity(100, percent);
  while (true) {
    // Tank drive control with Controller1
    Left.spin(forward, Controller1.Axis3.position(), percent);
    Right.spin(forward, Controller1.Axis2.position(), percent);
    if(Controller1.ButtonR1.pressing()){
      thread Wings(WingsOpen);
    } else if(Controller1.ButtonR2.pressing()){
      thread Wings(WingsClose);
    }
    if (Controller1.ButtonL1.pressing()) {
      thread Arm(ArmLift);
    } else if (Controller1.ButtonL2.pressing()) {
      thread Arm(ArmLower);
    } else if (Controller1.ButtonA.pressing()) {
      Flywheel.spin(forward);
    } else if (Controller1.ButtonB.pressing()) {
      Flywheel.stop();
    } else if(Controller1.ButtonDown.pressing()){
      Pneumatic.set(true);
    } else if(Controller1.ButtonUp.pressing()){
      Pneumatic.set(false);
    } else {
      Arm.stop();
      RWing.stop();
      LWing.stop();
    }
    this_thread::sleep_for(10);
  }
}

int main() {
  // Velocities and Set Up
  RWing.setVelocity(100, percent);
  LWing.setVelocity(100, percent);
  RWing.setPosition(0, degrees);
  LWing.setPosition(0, degrees);
  Arm.setStopping(hold);
  RWing.setStopping(hold);
  LWing.setStopping(hold);
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);  
}
