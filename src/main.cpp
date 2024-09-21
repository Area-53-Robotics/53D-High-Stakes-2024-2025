#include "main.h"
#include "liblvgl/extra/widgets/chart/lv_chart.h"
#include "liblvgl/misc/lv_color.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

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
	// pros::lcd::initialize();
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
    CreateMenuDropdown();
    OpenAutonSelectMenu();
}

float GetCurveOutput(int input) {
    return (std::exp(-20/12.7)+std::exp((std::abs(input)-127)/12.7)*(1-std::exp(-20/12.7))) * input;
}

void MotorAccelerationTest(void * param) {
	lv_obj_t * chart;
    chart = lv_chart_create(lv_scr_act());
	lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
	lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT);
	lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 200);
    lv_obj_set_size(chart, 300, 225);
    lv_obj_center(chart);

    // lv_obj_add_event_cb(chart, event_cb, LV_EVENT_ALL, NULL);
    lv_obj_refresh_ext_draw_size(chart);

    /*Zoom in a little in X*/
    // lv_chart_set_zoom_x(chart, 800);

    /*Add two data series*/
    lv_chart_series_t * BLMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * MLMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_ORANGE), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * FLMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_YELLOW), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * BRMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * MRMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * FRMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_PURPLE), LV_CHART_AXIS_PRIMARY_Y);

	// std::cout << "Time, BLM, MLM, FLM, BRM, MRM, FRM" << std::endl;

	int loopCount = 0;

	while(true){
		lv_chart_set_next_value2(chart, BLMser, loopCount * 20, left_mg.get_temperature(0));
		lv_chart_set_next_value2(chart, MLMser, loopCount * 20, left_mg.get_temperature(1));
		lv_chart_set_next_value2(chart, FLMser, loopCount * 20, left_mg.get_temperature(2));
		lv_chart_set_next_value2(chart, BRMser, loopCount * 20, right_mg.get_temperature(0));
		lv_chart_set_next_value2(chart, MRMser, loopCount * 20, right_mg.get_temperature(1));
		lv_chart_set_next_value2(chart, FRMser, loopCount * 20, right_mg.get_temperature(2));
		lv_chart_set_next_value2(chart, FRMser, loopCount * 20, 120);

		lv_chart_refresh(chart);
		loopCount++;
		pros::delay(20);
	}
}

void chartTest(void * param) {
	/*Create a chart*/
    lv_obj_t * chart;
    chart = lv_chart_create(lv_scr_act());
    lv_obj_set_size(chart, 400, 190);
    lv_obj_center(chart);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);   /*Show lines and points too*/
	// lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT);
	// lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_X, 0, 100);
	lv_chart_set_point_count(chart, 100);
	lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 6, 2, true, 50);
	lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 2, true, 50);
	lv_chart_set_zoom_x(chart, 125);

    /*Add two data series*/
    lv_chart_series_t * BLMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * MLMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_ORANGE), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * FLMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_YELLOW), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * BRMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * MRMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * FRMser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_PURPLE), LV_CHART_AXIS_PRIMARY_Y);

	int loopCount = 0;

    /*Set the next points on 'ser1'*/
	while(true) {
		lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, loopCount + 10);
		// lv_chart_set_point_count(chart, loopCount);

    	lv_chart_set_next_value(chart, BLMser, loopCount);
    	lv_chart_set_next_value(chart, MLMser, loopCount - 1);
    	lv_chart_set_next_value(chart, FLMser, loopCount - 2);
    	lv_chart_set_next_value(chart, BRMser, loopCount);
    	lv_chart_set_next_value(chart, MRMser, loopCount);
    	lv_chart_set_next_value(chart, FRMser, loopCount);

		loopCount++;
    	lv_chart_refresh(chart); /*Required after direct set*/
		lv_obj_refresh_ext_draw_size(chart);
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

	pros::Task my_task(chartTest, (void*)"PROS");

	while (true) {
		// Tank control scheme
		int LYAxis = Controller.get_analog(ANALOG_LEFT_Y); // Gets amount forward/backward from left joystick
		int RYAxis = Controller.get_analog(ANALOG_RIGHT_Y);  // Gets the turn left/right from right joystick
		
		left_mg.move(GetCurveOutput(LYAxis)); // Sets left motor voltage
		right_mg.move(GetCurveOutput(RYAxis)); // Sets right motor voltage
		
		if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) IntakeMotor.move_velocity(600);
		else if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) IntakeMotor.move(-127);
		else IntakeMotor.brake();

		if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) PneumaticClamp();

		pros::delay(20); // Run for 20 ms then update
	}
}