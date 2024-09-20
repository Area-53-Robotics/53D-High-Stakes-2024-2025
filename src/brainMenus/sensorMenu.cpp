#include "main.h"

// Creates the empty sensor display screen
lv_obj_t * sensorScr = lv_obj_create(NULL);

void OpenSensorMenu() {
    // Loads the sensor display screen
    lv_scr_load_anim(sensorScr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);

    // Loads the rectangle that will display the battery telemetry information
    CreateBatteryRect();
}

void CreateBatteryRect() {
    // Creates a rectangle on the screen
    lv_obj_t * batteryRect = lv_obj_create(sensorScr);
    // Sets the rectangle to 260px wide by 120px tall
    lv_obj_set_size(batteryRect, 260, 120);
    // Aligns the rectangle to the top left, offset by 5px to the left and 50px down (under the main menu dropdown)
    lv_obj_align(batteryRect, LV_ALIGN_TOP_LEFT, 5, 50);

    // Creates a label object on the rectangle, onto which text can be printed
    lv_obj_t * label = lv_label_create(batteryRect);
    // Aligns the label object to the top left of the rectangle
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
    // Sets the label object to slightly less than the width of the rectangle, allowing the lines to wrap
    lv_obj_set_width(label, 269);
    // Sets the text to wrap (create a new line) when it reaches the boundary of the label
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    // Prints the battery telemetry information onto the rectangle
    lv_label_set_text_fmt(label, "Battery\nLevel: %.2f\nCurrent: %d mA\nTemperature: %.2f C\nVoltage: %d mV",
                        pros::battery::get_capacity(), pros::battery::get_current(),
                        pros::battery::get_temperature(), pros::battery::get_voltage());
}