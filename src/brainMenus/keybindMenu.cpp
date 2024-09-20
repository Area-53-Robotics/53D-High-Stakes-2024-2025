#include "main.h"

// Creates the empty keybind display screen
lv_obj_t * keybindScr = lv_obj_create(NULL);

void OpenKeybindMenu() {
    // Loads the keybind display screen
    lv_scr_load_anim(keybindScr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
    
    // Loads the rectangle that will display the keyboard descriptions
    CreateMenuRectangle();
    
    // Stores the pointer to the label object on the rectangle
    lv_obj_t * label = lv_obj_get_child(menuRectangle, 0);

    // Prints the keybind descriptions onto the rectangle
    lv_label_set_text(label,
                    "Last Updated: N/A\n"
                    "-----------------------------------------------------\n"
                    "A: Toggle Drivetrain Direction\n"
                    "B: N/A\n"
                    "X: N/A\n"
                    "Y: N/A\n"
                    "Up: N/A\n"
                    "Down: N/A\n"
                    "Left: N/A\n"
                    "Right: N/A\n"
                    "L1: N/A\n" 
                    "L2: N/A\n"
                    "R1: N/A\n"
                    "R2: N/A"
    );
}