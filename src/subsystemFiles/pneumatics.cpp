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

bool goalRushActivated = false;

void GoalRush() {
    //sets the variable defined above to true
    if (!goalRushActivated) {
        GoalRushPiston.set_value(1);
        goalRushActivated = true;
    } else {
     //keeps the variable defined above to false 
        GoalRushPiston.set_value(0);
        goalRushActivated = false;
    }
}

bool ringRushActivated = false;

void RingRush() {
    if (!ringRushActivated) {
        RingRushPiston.set_value(1);
        ringRushActivated = true;
    } else {
        RingRushPiston.set_value(0);
        ringRushActivated = false;
    }
}