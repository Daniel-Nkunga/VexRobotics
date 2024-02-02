#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotorA = motor(PORT1, ratio18_1, true);
motor LeftMotorB = motor(PORT9, ratio18_1, true);
motor_group Left = motor_group(LeftMotorA, LeftMotorB);
motor RightMotorA = motor(PORT20, ratio18_1, false);
motor RightMotorB = motor(PORT10, ratio18_1, false);
motor_group Right = motor_group(RightMotorA, RightMotorB);
motor Arm = motor(PORT12, ratio36_1, true);
controller Controller1 = controller(primary);
motor Flywheel = motor(PORT11, ratio6_1, true);
motor RWing = motor(PORT3, ratio18_1, false);
motor LWing = motor(PORT5, ratio18_1, false);
digital_out Pneumatic = digital_out(Brain.ThreeWirePort.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}