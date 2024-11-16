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

    const float position1 = 360;
    const float position2 = 324.00;
    const float position3 = 209.47;

    const float kP = 150;

    while(true) {

        while(task.notify_take(true, 10));

        int timeout = 0;
        bool PIDActive = false;
        
        pros::lcd::print(5, "PIDActive: %d", PIDActive);

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

        ladybrownAngle = Rotation.get_angle() / 100.0;
        error = targetAngle - ladybrownAngle;

        while((std::abs(error) > 0.00001) && (timeout < 10000)) {
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

            PIDActive = true;
            ladybrownAngle = Rotation.get_angle() / 100.0;
            if (ladybrownAngle < 50) ladybrownAngle = 360 + ladybrownAngle;
            error = targetAngle - ladybrownAngle;
            power = error * kP;
            LadyBrownMotors.move_voltage(power);

            pros::lcd::print(1, "Error: %f", error);
            pros::lcd::print(2, "Power: %d", power);
            pros::lcd::print(3, "ladybrownAngle: %f", ladybrownAngle);
            pros::lcd::print(4, "ladybrownPosition: %d", ladybrownPosition);
            pros::lcd::print(5, "PIDActive: %d", PIDActive);

            timeout += 20;
            pros::Task::delay(20);
        }

        pros::Task::delay(20);
    }
}