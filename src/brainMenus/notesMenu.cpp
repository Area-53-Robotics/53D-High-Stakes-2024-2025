#include "main.h"

// Creates the empty notes display screen
lv_obj_t * notesScr = lv_obj_create(NULL);

void OpenNotesMenu() {
    // Loads the notes display screen
    lv_scr_load_anim(notesScr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);

    // Loads the rectangle that will display the keyboard descriptions
    CreateMenuRectangle();
    
    // Stores the pointer to the label object on the rectangle
    lv_obj_t * label = lv_obj_get_child(menuRectangle, 0);

    // Prints the notes onto the rectangle
    lv_label_set_text(label,
                    "Last Updated: N/A\n"
                    "-----------------------------------------------------\n"
                    "- Don't sell Makhi\n\n"
                    "Makhi Rules:\n"
                    "1. No using the pneumatic wings with drinks on the table.\n"
                    "2. No acting crazy so that teams don't think you're high.\n"
                    "3. No exaggerating the truth to judges\n"
                    "4. Let others speak so we show teamwork\n"
                    "5. No breaking the bot, especially not by sitting on it"
    );
}