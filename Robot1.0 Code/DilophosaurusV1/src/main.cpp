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

int main() {
  // Your setup code here
  RWing.setVelocity(100, percent);
  LWing.setVelocity(100, percent);
  RWing.setPosition(0, degrees);
  LWing.setPosition(0, degrees);
  Arm.setStopping(hold);

  //Autonomous
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
      Pneumatic.set(true);
    } else if(Controller1.ButtonRight.pressing()){
      Pneumatic.set(false);
    } else {
      Arm.stop();
      RWing.stop();
      LWing.stop();
    }

    // Your other control logic here
    
    this_thread::sleep_for(10);
  }
}
