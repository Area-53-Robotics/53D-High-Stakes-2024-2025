#include "main.h"

pros::Controller Controller(pros::E_CONTROLLER_MASTER);

/*
    Dead Ports: 5, 16, 17 (last updated 12/1/23)
    Best Battery: 13
*/

pros::MotorGroup left_mg({-8, -9, -10});
pros::MotorGroup right_mg({1, 2, 3});

pros::Motor IntakeMotor(4);

pros::adi::DigitalOut ClampPistons(1);

std::array<std::string,7> MotorNameList = {"BL", "ML", "FL", "BR", "MR", "FR", "Intake"};
std::array<pros::Motor*,1> MotorObjectList = {&IntakeMotor};
std::array<pros::MotorGroup*,2> MotorGroupObjectList = {&left_mg, &right_mg};

std::vector<int> MotorArraySizes;
int motorCount = 0;

void InitMotorArraySizes() {
    for(pros::MotorGroup* motorGroup : MotorGroupObjectList) {
        MotorArraySizes.push_back(motorGroup->size());
    }
    MotorArraySizes.push_back(MotorObjectList.size());

    for(int size : MotorArraySizes) {
        motorCount += size;
    }
}

bool driveReversed = false;

void ControllerDisplay() {
    if(!driveReversed) Controller.print(0, 0, "Reversed: false");
    else if(driveReversed) Controller.print(0, 0, "Reversed: true");
}