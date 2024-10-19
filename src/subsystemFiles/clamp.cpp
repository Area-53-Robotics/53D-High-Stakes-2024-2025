#include "main.h"
// creates a boolean variable that sets the variable to false
bool clampPistonsActivated = false;

void PneumaticClamp() {
    //sets the variable defined above to true
    if (!clampPistonsActivated) {
        ClampPistons.set_value(1);
        clampPistonsActivated = true;
    } else {
     //keeps the variable defined above to false 
        ClampPistons.set_value(0);
        clampPistonsActivated = false;
    }
}