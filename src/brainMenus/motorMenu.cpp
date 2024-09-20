#include "main.h"

// Creates the empty motor display screen
lv_obj_t * motorScr = lv_obj_create(NULL);

void OpenMotorMenu() {
    // Loads the motor display screen
    lv_scr_load_anim(motorScr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);

    // Loads the table that will display the motor telemetry information
    CreateMotorTable();
    // Loads the rectangle that will hold the motor telemetry toggle buttons
    CreateTelemetryRectangle();
    // Loads the motor telemetry toggle buttons
    CreateTelemetryButtons();
}

void MotorTableCB(lv_event_t * e)
{
    // Stores the pointer to the motor telemetry table
    lv_obj_t * obj = lv_event_get_target(e);
    // Stores a pointer to the LVGL's drawing instance of a part/cell in the table
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);

    // If the cells are drawn...
    if(dsc->part == LV_PART_ITEMS) {
        // Calculates the row number of the cell being drawn
        uint32_t row = dsc->id / lv_table_get_col_cnt(obj);
        // Calculates the column number of the cell being drawn
        uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);

        // Align all cells to the left
        dsc->label_dsc->align = LV_TEXT_ALIGN_LEFT;

        // Make the second column (temperature and power data) red with full opacity
        if(col == 1) {
            dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_RED), dsc->rect_dsc->bg_color, LV_OPA_40);
            dsc->rect_dsc->bg_opa = LV_OPA_COVER;
        }

        // Make the third column (velocity and voltage data) blue with full opacity
        else if(col == 2) {
            dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_BLUE), dsc->rect_dsc->bg_color, LV_OPA_40);
            dsc->rect_dsc->bg_opa = LV_OPA_COVER;
        }

        // Make the fourth column (torque and current data) yellow with full opacity
        else if(col == 3) {
            dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_YELLOW), dsc->rect_dsc->bg_color, LV_OPA_40);
            dsc->rect_dsc->bg_opa = LV_OPA_COVER;
        }
    }
}

// Initializes the motor telemetry table
lv_obj_t * motorTable;

// By default, the table will display the temperature, velocity, and torque of the motors
bool showingTemp = true;
bool showingVelocity = true;
bool showingTorque = true;

void CreateMotorTable() {
    // Creates the motor telemetry table
    motorTable = lv_table_create(motorScr);

    // Sets the number of rows in the table to the number of motors
    lv_table_set_row_cnt(motorTable, motorCount);
    // Sets the number of columns in the table to 4 (motor name & 3 telemetry values)
    lv_table_set_col_cnt(motorTable, 4);

    // Sets the width of the first column to 74px and the width of the other 3 columns to 76px
    lv_table_set_col_width(motorTable, 0, 74);
    lv_table_set_col_width(motorTable, 1, 76);
    lv_table_set_col_width(motorTable, 2, 76);
    lv_table_set_col_width(motorTable, 3, 76);

    // Sets the size of the table to 305px wide by 230px tall 
    lv_obj_set_size(motorTable, 305, 230);
    // Adjusts the vertical padding of the text in the cells depending on the number of rows in the table
    lv_obj_set_style_pad_ver(motorTable, (111 / motorCount) - 5, LV_PART_ITEMS);
    // Sets the horizontal padding of the text in the cells to 2px
    lv_obj_set_style_pad_hor(motorTable, 2, LV_PART_ITEMS);
    // Sets the font in the table to Montserrat size 10
    lv_obj_set_style_text_font(motorTable, &lv_font_montserrat_10, LV_PART_ITEMS);
    // Aligns the table to the top right of the screen, offset by 5px to the left and 5px down
    lv_obj_align(motorTable, LV_ALIGN_TOP_RIGHT, -5, 5);

    // Adds an event callback to to apply the custom drawing (style) to the cells
    lv_obj_add_event_cb(motorTable, MotorTableCB, LV_EVENT_DRAW_PART_BEGIN, NULL);

    // Fills the cells in the first row of the table with motor names
    for(int i = 0; i < motorCount; i++) {
        lv_table_set_cell_value_fmt(motorTable, i, 0, "%s", MotorNameList[i].c_str());
    }

    // Calls the function that will display the temperature of the motors in the red column of the table
    UpdateRedColumn(true);
    // Calls the function that will display the velocity of the motors in the blue column of the table
    UpdateBlueColumn(true);
    // Calls the function that will display the torque of the motors in the yellow column of the table
    UpdateYellowColumn(true);
}

void UpdateRedColumn(bool showTemp) {
    int row = 0;

    // For each motor...
    for(int i = 0; i < MotorArraySizes.size(); i++) {
        if(i == MotorArraySizes.size() - 1) {
            for(int j = 0; j < MotorObjectList.size(); j++) {
                // If the user selected to display temperature values, then fill the red column of the table with the temperature values
                if(showTemp) lv_table_set_cell_value_fmt(motorTable, row, 1, "%lf C", MotorObjectList[j]->get_temperature());
                // Otherwise, the user selected to display power values, so fill the red column of the table with the power values
                else lv_table_set_cell_value_fmt(motorTable, row, 1, "%lf W", MotorObjectList[j]->get_power());

                row++;
            }
        } else {
            for(int j = 0; j < MotorGroupObjectList[i]->size(); j++) {
                // If the user selected to display temperature values, then fill the red column of the table with the temperature values
                if(showTemp) lv_table_set_cell_value_fmt(motorTable, row, 1, "%lf C", MotorGroupObjectList[i]->get_temperature(j));
                // Otherwise, the user selected to display power values, so fill the red column of the table with the power values
                else lv_table_set_cell_value_fmt(motorTable, row, 1, "%lf W", MotorGroupObjectList[i]->get_power(j));
                
                row++;
            }
        }
    }
}

void UpdateBlueColumn(bool showVelocity) {
    int row = 0;

    // For each motor...
    for(int i = 0; i < MotorArraySizes.size(); i++) {
        if(i == MotorArraySizes.size() - 1) {
            for(int j = 0; j < MotorObjectList.size(); j++) {
                // If the user selected to display velocity values, then fill the blue column of the table with the velocity values
                if(showVelocity) lv_table_set_cell_value_fmt(motorTable, row, 2, "%lf RPM", MotorObjectList[j]->get_actual_velocity());
                // Otherwise, the user selected to display voltage values, so fill the blue column of the table with the voltage values
                else lv_table_set_cell_value_fmt(motorTable, row, 2, "%lf mV", MotorObjectList[j]->get_power());
            
                row++;
            }
        } else {
            for(int j = 0; j < MotorGroupObjectList[i]->size(); j++) {
                // If the user selected to display velocity values, then fill the blue column of the table with the velocity values
                if(showVelocity) lv_table_set_cell_value_fmt(motorTable, row, 2, "%lf RPM", MotorGroupObjectList[i]->get_actual_velocity(j));
                // Otherwise, the user selected to display voltage values, so fill the blue column of the table with the voltage values
                else lv_table_set_cell_value_fmt(motorTable, row, 2, "%lf mV", MotorGroupObjectList[i]->get_power(j));
                
                row++;
            }
        }
    }
}

void UpdateYellowColumn(bool showTorque) {
    int row = 0;

    // For each motor...
    for(int i = 0; i < MotorArraySizes.size(); i++) {
        if(i == MotorArraySizes.size() - 1) {
            for(int j = 0; j < MotorObjectList.size(); j++) {
                // If the user selected to display torque values, then fill the blue column of the table with the torque values
                if(showTorque) lv_table_set_cell_value_fmt(motorTable, row, 3, "%lf Nm", MotorObjectList[j]->get_torque());
                // Otherwise, the user selected to display current draw values, so fill the blue column of the table with the current draw values
                else lv_table_set_cell_value_fmt(motorTable, row, 3, "%lf mA", MotorObjectList[j]->get_current_draw());
            
                row++;
            }
        } else {
            for(int j = 0; j < MotorGroupObjectList[i]->size(); j++) {
                // If the user selected to display torque values, then fill the blue column of the table with the torque values
                if(showTorque) lv_table_set_cell_value_fmt(motorTable, row, 3, "%lf Nm", MotorGroupObjectList[i]->get_torque(j));
                // Otherwise, the user selected to display current draw values, so fill the blue column of the table with the current draw values
                else lv_table_set_cell_value_fmt(motorTable, row, 3, "%lf mA", MotorGroupObjectList[i]->get_current_draw(j));
            
                row++;
            }
        }
    }
}

// Initializes the telemetry button rectangle
lv_obj_t * telemetryRect;

void CreateTelemetryRectangle() {
    // Creates an empty style, which will later be assigned to the telemetry button rectangle
    static lv_style_t telemetryRectStyle;
    // Initializes (sets a default state) for the style
    lv_style_init(&telemetryRectStyle);
    // Sets all padding in the rectangle to 0
    lv_style_set_pad_all(&telemetryRectStyle, 0);
    // Sets the gap between objects in the rectangle to 0
    lv_style_set_pad_gap(&telemetryRectStyle, 0);
    // Sets the padding between the top of the rectangle and the top object in the rectangle to 2px
    lv_style_set_pad_top(&telemetryRectStyle, 2.5);
    // Sets the padding between the bottom object in the rectangle and the bottom of the rectangle to 2px
    lv_style_set_pad_bottom(&telemetryRectStyle, 2.5);

    // Creates the telemetry button rectangle
    telemetryRect = lv_obj_create(motorScr);
    // Sets the size of the rectangle to 160px wide by 185px tall
    lv_obj_set_size(telemetryRect, 160, 185);
    // Aligns the rectangle to be directly below the main menu dropdown
    lv_obj_align(telemetryRect, LV_ALIGN_TOP_LEFT, 5, 50);
    // Assigns the style information defined earlier to the telemetry button rectangle
    lv_obj_add_style(telemetryRect, &telemetryRectStyle, 0);
}

void ButtonMatrixCB(lv_event_t * e)
{
    // Stores the pointer to the button matrix that triggered the callback event
    lv_obj_t * obj = lv_event_get_target(e);
    // Stores id number (0 or 1) of the selected button in the button matrix
    uint32_t id = lv_btnmatrix_get_selected_btn(obj);

    // Determines which button has been pressed, and sets its control mode to "pressed"
    short int i;
    for(i = 0; i < 2; i++) {
        if(lv_btnmatrix_has_btn_ctrl(obj, i, LV_BTNMATRIX_CTRL_CHECKED)) break;
    }
    lv_btnmatrix_set_btn_ctrl(obj, i, LV_BTNMATRIX_CTRL_CHECKED);

    // If the temperature button was pressed, update the red column to display temperature values
    if(strcmp(lv_btnmatrix_get_btn_text(obj, id), "Temp") == 0) {
        UpdateRedColumn(true);
        showingTemp = true;
    // If the power button was pressed, update the red column to display power values
    } else if(strcmp(lv_btnmatrix_get_btn_text(obj, id), "Power") == 0) {
        UpdateRedColumn(false);
        showingTemp = false;
    // If the velocity button was pressed, update the blue column to display velocity values
    } else if(strcmp(lv_btnmatrix_get_btn_text(obj, id), "Velocity") == 0) {
        UpdateBlueColumn(true);
        showingVelocity = true;
    // If the voltage button was pressed, update the blue column to display voltage values
    } else if(strcmp(lv_btnmatrix_get_btn_text(obj, id), "Voltage") == 0) {
        UpdateBlueColumn(false);
        showingVelocity = false;
    // If the torque button was pressed, update the yellow column to display torque values
    } else if(strcmp(lv_btnmatrix_get_btn_text(obj, id), "Torque") == 0) {
        UpdateYellowColumn(true);
        showingTorque = true;
    // If the current draw button was pressed, update the yellow column to display current draw values
    } else if(strcmp(lv_btnmatrix_get_btn_text(obj, id), "Current") == 0) {
        UpdateYellowColumn(false);
        showingTorque = false;
    }
}

void RedButtonMatrixStyleCB(lv_event_t * e)
{
    // Stores the pointer to the button that triggered the callback event
    lv_obj_t * obj = lv_event_get_target(e);
    // Stores a pointer to the LVGL's drawing instance of the button
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);

    // When the button matrix draws the buttons...
    if(dsc->class_p == &lv_btnmatrix_class && dsc->type == LV_BTNMATRIX_DRAW_PART_BTN) {
        // If the temperature button is being drawn by LVGL...
        if(dsc->id == 0) {
            // If temperature values are being shown, then make the temperature button red
            if(showingTemp) dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_RED);
            // Else, if the power values are being shown, then make the temperature button grey
            else dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_GREY);
        }
        // If the power button is being drawn by LVGL...
        else if(dsc->id == 1) {
            // If power values are being shown, then make the power button red
            if(!showingTemp) dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_RED);
            // Else, if the temperature values are being shown, then make the power button grey
            else dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_GREY);
        }
    }
}

void BlueButtonMatrixStyleCB(lv_event_t * e)
{
    // Stores the pointer to the button that triggered the callback event
    lv_obj_t * obj = lv_event_get_target(e);
    // Stores a pointer to the LVGL's drawing instance of the button
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);

    // When the button matrix draws the buttons...
    if(dsc->class_p == &lv_btnmatrix_class && dsc->type == LV_BTNMATRIX_DRAW_PART_BTN) {
        // If the velocity button is being drawn by LVGL...
        if(dsc->id == 0) {
            // If velocity values are being shown, then make the velocity button blue
            if(showingVelocity) dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_BLUE);
            // Else, if the voltage values are being shown, then make the velocity button grey
            else dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_GREY);
        }
        // If the voltage button is being drawn by LVGL...
        else if(dsc->id == 1) {
            // If voltage values are being shown, then make the voltage button blue
            if(!showingVelocity) dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_BLUE);
            // Else, if the velocity values are being shown, then make the voltage button grey
            else dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_GREY);
        }
    }
}

void YellowButtonMatrixStyleCB(lv_event_t * e)
{
    // Stores the pointer to the button that triggered the callback event
    lv_obj_t * obj = lv_event_get_target(e);
    // Stores a pointer to the LVGL's drawing instance of the button
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);

    // When the button matrix draws the buttons...
    if(dsc->class_p == &lv_btnmatrix_class && dsc->type == LV_BTNMATRIX_DRAW_PART_BTN) {
        // If the torque button is being drawn by LVGL...
        if(dsc->id == 0) {
            // If torque values are being shown, then make the torque button yellow
            if(showingTorque) dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_YELLOW);
            // Else, if the current draw values are being shown, then make the torque button grey
            else dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_GREY);
        }
        // If the current draw button is being drawn by LVGL...
        else if(dsc->id == 1) {
            // If current draw values are being shown, then make the current draw button yellow
            if(!showingTorque) dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_YELLOW);
            // Else, if the torque values are being shown, then make the current draw button grey
            else dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_GREY);
        }
    }
}

// Initializes the text that will be mapped onto the telemetry buttons
const char * RedButtonMap[] = {"Temp", "Power", NULL};
const char * BlueButtonMap[] = {"Velocity", "Voltage", NULL};
const char * YellowButtonMap[] = {"Torque", "Current", NULL};

void CreateTelemetryButtons() {
    // Sets the style properties of the telemetry button matrix
    static lv_style_t teleBtnBGStyle;
    lv_style_init(&teleBtnBGStyle);
    lv_style_set_pad_all(&teleBtnBGStyle, 0);
    lv_style_set_pad_gap(&teleBtnBGStyle, 0);
    lv_style_set_clip_corner(&teleBtnBGStyle, true);
    lv_style_set_radius(&teleBtnBGStyle, LV_RADIUS_CIRCLE);
    lv_style_set_border_width(&teleBtnBGStyle, 0);

    // Sets the style properties of the individual telemetry buttons
    static lv_style_t teleBtnStyle;
    lv_style_init(&teleBtnStyle);
    lv_style_set_radius(&teleBtnStyle, 0);
    lv_style_set_border_width(&teleBtnStyle, 1);
    lv_style_set_border_opa(&teleBtnStyle, LV_OPA_50);
    lv_style_set_border_color(&teleBtnStyle, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_border_side(&teleBtnStyle, LV_BORDER_SIDE_INTERNAL);
    lv_style_set_radius(&teleBtnStyle, 0);

    /* --- 1. Red buttons (temperature and power) --- */
    // Initializes an empty button matrix that will be used to toggle the values in the red column
    lv_obj_t * RedButtonMatrix = lv_btnmatrix_create(telemetryRect);
    // Assigns text to the buttons in the button matrix
    lv_btnmatrix_set_map(RedButtonMatrix, RedButtonMap);

    // Assigns the style properties declared earlier to the telemetry button matrix
    lv_obj_add_style(RedButtonMatrix, &teleBtnBGStyle, 0);
    // Assigns the style properties declared earlier to the individual telemetry buttons
    lv_obj_add_style(RedButtonMatrix, &teleBtnStyle, LV_PART_ITEMS);

    // Sets the size of the button matrix to 150px wide by 57px tall
    lv_obj_set_size(RedButtonMatrix, 150, 57);
    // Aligns the button matrix to the top-middle of the rectangle
    lv_obj_align(RedButtonMatrix, LV_ALIGN_TOP_MID, 0, 0);

    // Activates a callback function that updates the telemetry table when a telemetry button is pressed
    lv_obj_add_event_cb(RedButtonMatrix, ButtonMatrixCB, LV_EVENT_VALUE_CHANGED, NULL);
    // Activates a callback function that updates the look of the telemetry buttons when one of them is pressed
    lv_obj_add_event_cb(RedButtonMatrix, RedButtonMatrixStyleCB, LV_EVENT_DRAW_PART_BEGIN, NULL);

    // Allow the buttons to be selected
    lv_btnmatrix_set_btn_ctrl_all(RedButtonMatrix, LV_BTNMATRIX_CTRL_CHECKABLE);

    // Allow only one button to be pressed at a time
    lv_btnmatrix_set_one_checked(RedButtonMatrix, true);
    // Set the "temperature" button to be pressed by default
    lv_btnmatrix_set_btn_ctrl(RedButtonMatrix, 0, LV_BTNMATRIX_CTRL_CHECKED);

    /* --- 2. Blue buttons (velocity and voltage) --- */
    // Initializes an empty button matrix that will be used to toggle the values in the blue column
    lv_obj_t * BlueButtonMatrix = lv_btnmatrix_create(telemetryRect);
    // Assigns text to the buttons in the button matrix
    lv_btnmatrix_set_map(BlueButtonMatrix, BlueButtonMap);

    // Assigns the style properties declared earlier to the telemetry button matrix
    lv_obj_add_style(BlueButtonMatrix, &teleBtnBGStyle, 0);
    // Assigns the style properties declared earlier to the individual telemetry buttons
    lv_obj_add_style(BlueButtonMatrix, &teleBtnStyle, LV_PART_ITEMS);

    // Sets the size of the button matrix to 150px wide by 57px tall
    lv_obj_set_size(BlueButtonMatrix, 150, 57);
    // Aligns the button matrix to the center of the rectangle
    lv_obj_align(BlueButtonMatrix, LV_ALIGN_CENTER, 0, 0);

    // Activates a callback function that updates the telemetry table when a telemetry button is pressed
    lv_obj_add_event_cb(BlueButtonMatrix, ButtonMatrixCB, LV_EVENT_VALUE_CHANGED, NULL);
    // Activates a callback function that updates the look of the telemetry buttons when one of them is pressed
    lv_obj_add_event_cb(BlueButtonMatrix, BlueButtonMatrixStyleCB, LV_EVENT_DRAW_PART_BEGIN, NULL);

    // Allow the buttons to be selected
    lv_btnmatrix_set_btn_ctrl_all(BlueButtonMatrix, LV_BTNMATRIX_CTRL_CHECKABLE);

    // Allow only one button to be pressed at a time
    lv_btnmatrix_set_one_checked(BlueButtonMatrix, true);
    // Set the "velocity" button to be pressed by default
    lv_btnmatrix_set_btn_ctrl(BlueButtonMatrix, 0, LV_BTNMATRIX_CTRL_CHECKED);


    /* --- 3. Yellow buttons (torque and current) --- */
    // Initializes an empty button matrix that will be used to toggle the values in the yellow column
    lv_obj_t * YellowButtonMatrix = lv_btnmatrix_create(telemetryRect);
    // Assigns text to the buttons in the button matrix
    lv_btnmatrix_set_map(YellowButtonMatrix, YellowButtonMap);

    // Assigns the style properties declared earlier to the telemetry button matrix
    lv_obj_add_style(YellowButtonMatrix, &teleBtnBGStyle, 0);
    // Assigns the style properties declared earlier to the individual telemetry buttons
    lv_obj_add_style(YellowButtonMatrix, &teleBtnStyle, LV_PART_ITEMS);

    // Sets the size of the button matrix to 150px wide by 57px tall
    lv_obj_set_size(YellowButtonMatrix, 150, 57);
    // Aligns the button matrix to the bottom-middle of the rectangle
    lv_obj_align(YellowButtonMatrix, LV_ALIGN_BOTTOM_MID, 0, 0);

    // Activates a callback function that updates the telemetry table when a telemetry button is pressed
    lv_obj_add_event_cb(YellowButtonMatrix, ButtonMatrixCB, LV_EVENT_VALUE_CHANGED, NULL);
    // Activates a callback function that updates the look of the telemetry buttons when one of them is pressed
    lv_obj_add_event_cb(YellowButtonMatrix, YellowButtonMatrixStyleCB, LV_EVENT_DRAW_PART_BEGIN, NULL);

    // Allow the buttons to be selected
    lv_btnmatrix_set_btn_ctrl_all(YellowButtonMatrix, LV_BTNMATRIX_CTRL_CHECKABLE);

    // Allow only one button to be pressed at a time
    lv_btnmatrix_set_one_checked(YellowButtonMatrix, true);
    // Set the "torque" button to be pressed by default
    lv_btnmatrix_set_btn_ctrl(YellowButtonMatrix, 0, LV_BTNMATRIX_CTRL_CHECKED);
}