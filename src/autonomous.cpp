#include "main.h"

std::vector<lv_obj_t *> AutonButtons;
std::vector<Auton> AutonObjectList;

unsigned short int Auton::autonCount = 0;

/*
    The constructor to create a new auton

    Parameters:
    - autonName: String containing the name of the auton
    - autonDescription: String containing the description for the auton
    - autonRoutine: Function containing the actions to be performed in the auton
*/
Auton::Auton(const char * autonName, const char * autonDescription, std::function<void()> autonRoutine) {
    // Assigns the name of the auton to what the programmer enters
    name = autonName;
    // Assigns the description of the auton to what the programmer enters
    description = autonDescription;
    // Assigns the routine performed by the auton to the actions entered by the programmer
    routine = autonRoutine;
    // Assigns the auton's unique number id
    autonNum = autonCount;
    // Increments the count of current autons
    autonCount += 1;

    // Initializes a new button for the auton on the auton selector
    AutonButtons.push_back(new lv_obj_t);
    // Adds the new auton object to the list of created auton objects
    AutonObjectList.push_back(*this);
}

Auton leftQualsAuton(
	"Left Quals",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Left Auton\n",
	[]() -> void {
        Controller.print(0, 0, "Left Quals Start");
        pros::delay(20);
    }
);

Auton rightQualsAuton(
	"Right Quals",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Right Auton\n",
	[]() -> void {
        Controller.print(0, 0, "The right auton");
        pros::delay(20);
    }
);

Auton pSkillsAuton(
	"P-Skills",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Programming Skills Auton\n",
	[]() -> void {
        Controller.print(0, 0, "The P-Skills auton");
        pros::delay(20);
    }
);

unsigned short int autonSelect = rightQualsAuton.autonNum;

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    AutonObjectList[autonSelect].routine();
}