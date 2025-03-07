#include "main.h"

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
	chassis.calibrate();
	// pros::lcd::set_text(1, "Hello PROS User!");

	// pros::lcd::register_btn1_cb(on_center_button);
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
	InitMotorArraySizes();
    // CreateMenuDropdown();
    // OpenAutonSelectMenu();
}

float GetCurveOutput(int input) {
    return (std::exp(-20/12.7)+std::exp((std::abs(input)-127)/12.7)*(1-std::exp(-20/12.7))) * input;
}

void PositionTrack(void * param) {
	while(true) {
		lemlib::Pose pose = chassis.getPose();
		printf("X: %f, Y: %f, Theta: %f\n", pose.x, pose.y, pose.theta);
		pros::lcd::print(0, "X (inches): %f", pose.x);
		pros::lcd::print(1, "Y (inches): %f", pose.y);
		pros::lcd::print(2, "Theta (degrees): %f", pose.theta);
		pros::delay(100);
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

	pros::Task position_track_task(PositionTrack, (void*)"PROS");

	// if(!pros::competition::is_connected()) autonomous();

	// Initializes the ladybrown task
	pros::Task ladybrown_task(LadybrownTask, (void*)"PROS");

	while (true) {
		// Tank control scheme
		int LYAxis = Controller.get_analog(ANALOG_LEFT_Y); // Gets amount forward/backward from left joystick
		int RYAxis = Controller.get_analog(ANALOG_RIGHT_Y); // Gets the turn left/right from right joystick

		left_mg.move(LYAxis); // Sets left motor voltage
		right_mg.move(RYAxis); // Sets right motor voltage

		// When the L1 controller button is pressed...
		if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			// increase the ladybrown position by 1
			LadybrownSwitch(true);
			// notify the ladybrown mechanism to move to the new target position
			ladybrown_task.notify();
		// When the L2 controller button is pressed...
		}
		// else if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
		// 	// decrease the ladybrown position by 1
		// 	LadybrownSwitch(false);
		// 	// notify the ladybrown mechanism to move to the new target position
		// 	ladybrown_task.notify();
		// }

		// The intake motor spins forward when R2 is held and spins reverse when R1 is held.
		if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) IntakeMotor.move_velocity(500);
		else if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) IntakeMotor.move_velocity(-500);
		else IntakeMotor.brake();

		if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) RingRush();

		// Sets the clamp to operate in driver control after pressing the A button
		if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) PneumaticClamp();

		if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			if (!goalRushActivated) {
				GoalRushPiston.set_value(1);
				goalRushActivated = true;
			}
		} else {
			if (goalRushActivated) {
				GoalRushPiston.set_value(0);
				goalRushActivated = false;
			}
		}

		
		if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
			driveReversed = !driveReversed;
			ControllerDisplay();
		}

		pros::delay(20); // Run for 20 ms then update
	}
}