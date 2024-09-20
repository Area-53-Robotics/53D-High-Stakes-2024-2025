#include "main.h"
#include "pros/misc.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    CreateMenuDropdown();
    OpenAutonSelectMenu();
}

float GetCurveOutput(int input) {
    return (std::exp(-20/12.7)+std::exp((std::abs(input)-127)/12.7)*(1-std::exp(-20/12.7))) * input;
}

void MotorAccelerationTest() {
	std::cout << "Time, BLM, MLM, FLM, BRM, MRM, FRM" << std::endl;
	unsigned int loopCount = 0;

	while(true) {
		std::cout << (loopCount * 20) << ", ";
			
		pros::delay(20);
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    // CreateMenuDropdown();
    // OpenAutonSelectMenu();

	while (true) {
		// Tank control scheme
		int LYAxis = Controller.get_analog(ANALOG_LEFT_Y); // Gets amount forward/backward from left joystick
		int RYAxis = Controller.get_analog(ANALOG_RIGHT_Y);  // Gets the turn left/right from right joystick
		
		left_mg.move(GetCurveOutput(LYAxis)); // Sets left motor voltage
		right_mg.move(GetCurveOutput(RYAxis)); // Sets right motor voltage
		
		if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) IntakeMotor.move_velocity(450);
		else if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) IntakeMotor.move(-127);
		else IntakeMotor.brake();

		if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) PneumaticClamp();

		pros::delay(20); // Run for 20 ms then update
	}
}