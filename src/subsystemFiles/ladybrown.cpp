#include "main.h"

/*
    1: Position 1 - Starting
    2: Position 2 - Intake
    3: Position 3 - Mobile Goal
*/

short int ladybrownPosition = 1;

void LadybrownSwitch(bool increase) {
    if (increase) {
        if (ladybrownPosition < 3) ladybrownPosition++;
        else ladybrownPosition = 1;
    } else {
        if (ladybrownPosition > 1) ladybrownPosition--;
        else ladybrownPosition = 3;
    }
}

void LadybrownTask(void * param) {
    pros::Task task = pros::Task::current();

    double ladybrownAngle;
    double error;
    double targetAngle;
    short int power;

    const float position1 = 0;
    const float position2 = 338.2;
    const float position3 = 216.47;

    const float kP = 100;

    while(true) {
        while(task.notify_take(true, 10));

        switch(ladybrownPosition) {
            case 1:
                targetAngle = position1;
                break;
            case 2:
                targetAngle = position2;
                break;
            case 3:
                targetAngle = position3;
                break;
        }

        error = targetAngle - ladybrownAngle;

        while(std::abs(error) > 10) {
            ladybrownAngle = Rotation.get_angle();
            if (ladybrownAngle < 50) ladybrownAngle = 360 + ladybrownAngle;
            error = targetAngle - ladybrownAngle;
            power = error * kP;
            LadyBrownMotors.move_voltage(power);
            pros::Task::delay(20);
        }

        pros::Task::delay(20);
    }
}