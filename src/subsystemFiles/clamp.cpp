#include "main.h"

bool clampPistonsActivated = false;

void PneumaticClamp() {
    if (!clampPistonsActivated) {
        ClampPistons.set_value(1);
        clampPistonsActivated = true;
    } else {
        ClampPistons.set_value(0);
        clampPistonsActivated = false;
    }
}