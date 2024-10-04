#include "main.h"

bool armPistonsActivated = false;

void PneumaticArm() {
    if (!armPistonsActivated) {
        ArmPistons.set_value(1);
        armPistonsActivated = true;
    } else {
        ArmPistons.set_value(0);
        armPistonsActivated = false;
    }
}