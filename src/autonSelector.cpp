#include "main.h"

// Initializes the object that will hold the rectangle section on the auton selector
lv_obj_t * menuRectangle;

void CreateMenuRectangle() {
    // Creates the rectangle object on the active screen
    menuRectangle = lv_obj_create(lv_scr_act());
    // Sets the size of the rectangle to 305px wide by 230px tall
    lv_obj_set_size(menuRectangle, 305, 230);
    // Aligns the rectangle to the top right of the active screen, offset to the left by 5px and down by 5px
    lv_obj_align(menuRectangle, LV_ALIGN_TOP_RIGHT, -5, 5);

    // Creates a label object on the rectangle, onto which text can be printed
    lv_obj_t * label1 = lv_label_create(menuRectangle);
    // Aligns the label object to the top left of the rectangle
    lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 0, 0);
    // Sets the label object to slightly less than the width of the rectangle, allowing the lines to wrap
    lv_obj_set_width(label1, 269);
    // Sets the text to wrap (create a new line) when it reaches the boundary of the label
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);
    // Sets the label to have a default empty text, which can be changed later by other functions
    lv_label_set_text(label1, "");
}

void MenuDropdownCB(lv_event_t * e)
{
    // Assigns the dropdown that triggered the event to an object accessible by this function
    lv_obj_t * dropdown = lv_event_get_target(e);
    // Creates a 64-character length empty string variable
    char selected[64];
    // Stores the name of the dropdown menu's selected option into the string variable
    lv_dropdown_get_selected_str(dropdown, selected, sizeof(selected));

    // Opens the screen associated with the selected option
    if(strcmp(selected, "Autons") == 0) OpenAutonSelectMenu();
    else if (strcmp(selected, "Motors") == 0) OpenMotorMenu();
    else if (strcmp(selected, "Sensors") == 0) OpenSensorMenu();
    else if (strcmp(selected, "Keybinds") == 0) OpenKeybindMenu();
    else if (strcmp(selected, "Notes") == 0) OpenNotesMenu();
}

/**
 * Create a menu from a drop-down list and show some drop-down list features and styling
 */
void CreateMenuDropdown()
{
    // Creates an empty dropdown list on the top layer of the screen
    lv_obj_t * menuDropdown = lv_dropdown_create(lv_layer_top());
    // Sets the dropdown list to be 160px wide by 40px long
    lv_obj_set_size(menuDropdown, 160, 40);
    // Aligns the dropdown to the top left of the screen, offset by 5px to the left and 5px down
    lv_obj_align(menuDropdown, LV_ALIGN_TOP_LEFT, 5, 5);
    // Adds options to the dropdown menu
    lv_dropdown_set_options(menuDropdown, "Autons\n"
                            "Motors\n"
                            "Sensors\n"
                            "Keybinds\n"
                            "Notes");

    // In a menu we don't need to show the last clicked item
    lv_dropdown_set_selected_highlight(menuDropdown, false);

    // When the selected option on the dropdown menu changes, activate the callback function that switches the screen
    lv_obj_add_event_cb(menuDropdown, MenuDropdownCB, LV_EVENT_VALUE_CHANGED, NULL);
}