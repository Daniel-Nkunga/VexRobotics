#include "vex.h"

using namespace vex;

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Left                 motor_group   1, 9            
// Right                motor_group   20, 10          
// Arm                  motor         12              
// Controller1          controller                    
// Flywheel             motor         11              
// RWing                motor         3               
// LWing                motor         5               
// Pneumatic            digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

competition Competition;

//Threading
void L_TRThreadFunction90(){ //Naming Scheme [Motor Side]_[Turning Direction]
  Left.spinFor(reverse, 680, degrees);
}
void R_TRThreadFunction90(){
  Right.spinFor(forward, 680, degrees);
}
void R_TRThreadFunction70(){
  Right.spinFor(forward, 530, degrees);
}
void L_TLThreadFunction90(){
  Left.spinFor(forward, 680, degrees);
}
void R_TLThreadFunction90(){
  Right.spinFor(reverse, 700, degrees);
}
void R_DFThreadFunction(){
  Right.spinFor(forward, 700, degrees);
}
void R_DRLThreadFunction(){
  Right.spinFor(reverse,1200, degrees);
}

void RWingOpen() {
  RWing.spin(forward);
}
void RWingClose() {
  RWing.spin(reverse);
}
void LWingOpen() {
  LWing.spin(forward);
}
void LWingClose() {
  LWing.spin(reverse);
}

void LWingTaskFunction() {
  LWing.spin(forward);
}

void wings() {
  RWing.spinToPosition(0, degrees);
  LWing.spinToPosition(0, degrees);
}

void autonomous(){
  Pneumatic.set(false);
  Arm.setPosition(0, degrees);
  Arm.spinToPosition(600, degrees);
  thread Right(R_DFThreadFunction);
  Left.spinFor(forward, 700, degrees);
  thread Right2(R_TRThreadFunction70);
  Left.spinFor(reverse, 530, degrees);
  thread Right3(R_DRLThreadFunction);
  Left.spinFor(reverse, 800, degrees);

  // thread Right(R_TRThreadFunction90); //Because of the way threads work [how daniel THINKS they work], all left commands will not be threaded as to flatten the stack too much
  // Left.spinFor(reverse, 700, degrees);
  // vex::task::sleep(1000);
  // thread Right2(R_TLThreadFunction90);
  // Left.spinFor(forward, 700, degrees);
  // vex::task::sleep(1000);
  // thread Right3(R_DFThreadFunction);
  // Left.spinFor(forward, 700, degrees);
}

void userControl(){
  Left.setVelocity(100, percent);
  Right.setVelocity(100, percent);
  while (true) {
    // Tank drive control with Controller1
    Left.spin(forward, Controller1.Axis3.position(), percent);
    Right.spin(forward, Controller1.Axis2.position(), percent);
    
    // Handle various button presses
    if (Controller1.ButtonUp.pressing()) {
      Arm.spin(forward);
    } else if (Controller1.ButtonDown.pressing()) {
      Arm.spin(reverse);
    } else if (Controller1.ButtonR1.pressing()) {
      while(Controller1.ButtonR1.pressing()){
        thread RWing(RWingOpen);
      }
    } else if (Controller1.ButtonR2.pressing()) {
      while(Controller1.ButtonR2.pressing()){
        thread RWing(RWingClose);
      }
    } else if (Controller1.ButtonL1.pressing()) {
      while(Controller1.ButtonL1.pressing()){
        thread LWing(LWingOpen);
      }
    } else if (Controller1.ButtonL2.pressing()) {
      while(Controller1.ButtonL2.pressing()){
        thread LWing(LWingClose);
      }
    } else if (Controller1.ButtonA.pressing()) {
      Flywheel.spin(forward);
    } else if (Controller1.ButtonB.pressing()) {
      Flywheel.stop();
    } else if (Controller1.ButtonY.pressing()) {
      wings();
      Brain.Screen.print("Oops");
    } else if(Controller1.ButtonLeft.pressing()){
      Pneumatic.set(false);
    } else if(Controller1.ButtonRight.pressing()){
      Pneumatic.set(true);
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
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);  
}
