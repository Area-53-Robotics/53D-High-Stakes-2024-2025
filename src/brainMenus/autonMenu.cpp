#include "main.h"

// Creates the empty auton sleection screen
lv_obj_t * autonScr = lv_obj_create(NULL);

// Initializes the object that will hold the auton selection button list
lv_obj_t * autonList;

void AutonListCB(lv_event_t * e)
{
    // Stores the pointer to the button that triggered the callback event
    lv_obj_t * obj = lv_event_get_target(e);
    // Stores the pointer to the label object on the rectangle
    lv_obj_t * label = lv_obj_get_child(menuRectangle, 0);

    // We need to determine which auton corresponds with the button that was pressed, so we iterate through each available auton
    for(int i = 0; i < Auton::autonCount; i++) {
        // Then, we compare the name of the button to the auton name we are testing, and if they are the same...
        if(strcmp(lv_list_get_btn_text(autonList, obj), AutonObjectList[i].name) == 0) {
            // We set the id of the newly selected auton into the global autonSelect variable
            autonSelect = i;
            // Then we load the description of the auton onto the rectangle on the brain screen
            lv_label_set_text(label, AutonObjectList[i].description);
            // Only one auton button could have been pressed, so we can stop iterating through the available autons now
            break;
        }
    }
}

void CreateAutonList()
{
    // Creates an empty list object
    autonList = lv_list_create(autonScr);
    // Sets the size of the list to 160px wide by 185px tall
    lv_obj_set_size(autonList, 160, 185);
    // Aligns the list to the top right of the screen, offset by 5px to the right and 50px down
    lv_obj_align(autonList, LV_ALIGN_TOP_LEFT, 5, 50);

    // For each autonomous...
    for (int i = 0; i < Auton::autonCount; i++) {
        // Create a button for the autonomous in the button list
        AutonButtons[i] = lv_list_add_btn(autonList, NULL, AutonObjectList[i].name);
        // Assign a callback event that is triggered when the button is pressed
        lv_obj_add_event_cb(AutonButtons[i], AutonListCB, LV_EVENT_CLICKED, NULL);
    }
}

void OpenAutonSelectMenu() {
    // Loads the auton select screen
    lv_scr_load_anim(autonScr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);

    // Loads the auton button list
    CreateAutonList();
    // Loads the rectangle that will display auton descriptions
    CreateMenuRectangle();

    // Loads the description for the currently selected auton onto the screen
    for (int i = 0; i < Auton::autonCount; i++) {
        if(autonSelect == i) {
            lv_event_send(AutonButtons[i], LV_EVENT_CLICKED, NULL);
            break;
        }
    }
}