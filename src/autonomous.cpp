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

void moveDrivetrain(int power, int timeout){
    left_mg.move(power);
    right_mg.move(power);
    pros::delay(timeout);
    left_mg.brake();
    right_mg.brake();
}

void turnDrivetrain(int power, int timeout){
    left_mg.move(-power);
    right_mg.move(power);
    pros::delay(timeout);
    left_mg.brake();
    right_mg.brake(); 
}

short int IntakeSpeed = 0;

void IntakeTask(void * param){
    while(true){
        if(abs(IntakeSpeed) > 0) IntakeMotor.move(IntakeSpeed);
        else IntakeMotor.brake();
        pros::delay(20);
    }
}

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

// Auton leftQualsAuton(
// 	"Left Quals",
// 	"Last Updated: N/A\n"
// 	"-----------------------------------------------------\n"
// 	"The Left Auton\n",
// 	[]() -> void {
//         Controller.print(0, 0, "Left Quals Start");
//         pros::delay(20);
//     }
// );
Auton leftQualsAuton(
	"Left Quals",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Left Auton\n",
	[]() -> void {   
        chassis.setPose(0, 0, 0);
        chassis.moveToPoint(0, 48, 10000);
        /*
        moveDrivetrain(-100,225);
        pros::delay(1000);
        ClampPistons.set_value(1);
        pros::delay(1000);
        IntakeMotor.move(-500);
        pros::delay(1500);
        turnDrivetrain(700, 487);
        pros::delay(1000);
        moveDrivetrain(300,220);
        pros::delay(1000);
        IntakeMotor.move(-500);
        pros::delay(1500);
        IntakeMotor.brake();
        */
    }
);

Auton rightQualsAuton(
	"Right Quals",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Right Auton\n",
	[]() -> void {
       moveDrivetrain(-100,225);
       pros::delay(1000);
       ClampPistons.set_value(1);
       pros::delay(1000);
       IntakeMotor.move(-500);
       pros::delay(1500);
       turnDrivetrain(-100, 300);
       pros::delay(1000);
       moveDrivetrain(300,210);
       pros::delay(1000);
       IntakeMotor.move(-500);
       
       IntakeMotor.brake();
        //ClampPistons.set_value(0); */
        // chassis.calibrate();
        // chassis.setPose(0, 0, 0);
        // chassis.moveToPoint(0, 48, 10000);
        // chassis.turnToHeading(90, 2000);
        Controller.print(0, 0, "The right auton");
        pros::delay(20);
    }
);

Auton blueQualsAuton(
	"Blue Auton",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Right Side Auton 2: Electric Boogaloo\n",
	[]() -> void {
        // Pre-Auton Stuff
        pros::Task my_task(LadybrownTask, (void*)"PROS");
        Controller.print(0, 0, "The Right Side Auton 2");
        chassis.setPose(12, -54, 231.99);

        // Alliance Stake Scoring
        chassis.moveToPoint(5, -59.5, 1000, {.forwards = true}, false);
        ladybrownPosition = 3;
        my_task.notify();
        pros::delay(800);
        ladybrownPosition = 1;
        my_task.notify();

        // Pick up 1st mobile goal
        chassis.moveToPoint(22, -26, 1250, {.forwards = false, .maxSpeed = 90}, false);
        pros::delay(250);
        ClampPistons.set_value(1);
        pros::delay(200);

        // Pick up lone ring stack
        chassis.moveToPose(48, -24, 40, 2250, {.forwards = true, .maxSpeed = 110});
        IntakeMotor.move(-127);
        pros::delay(3250);

        // Pick up left ring stack
        chassis.moveToPose(45, -11, 325, 2500, {.forwards = true, .maxSpeed = 110});
        IntakeMotor.move(-127);
        pros::delay(250);

        // ! AWP Alt: Go for bar
        ladybrownPosition = 3;
        my_task.notify();
        chassis.moveToPose(-24, -12, 45, 2000);

        /*
        // Start moving towards start position ring stack
        chassis.moveToPose(4, -46, 270, 3500, {.forwards = true, .maxSpeed = 127});
        IntakeMotor.move(-127);
        pros::delay(700);
        IntakeMotor.brake();
        pros::delay(800);
        IntakeMotor.move(-127);

        // Drop 1st mobile goal
        ClampPistons.set_value(0);
        IntakeMotor.move(-127);
        pros::delay(200);
        IntakeMotor.move(-127);
        pros::delay(3000);

        // Pick up blue ring from start position ring stack
        chassis.moveToPose(-8, -46, 270, 5000, {.forwards = true, .maxSpeed = 110});
        IntakeMotor.move(-127);
        pros::delay(200);

        chassis.moveToPoint(-24, -24, 2000, {.forwards = false, .maxSpeed = 90});
        ClampPistons.set_value(1);
        IntakeMotor.move(-127);
        ladybrownPosition = 3;
        my_task.notify();
        chassis.moveToPoint(-18, -18, 2000, {.forwards = false, .maxSpeed = 110});
        */

        my_task.remove();
    }
);

Auton redQualsAuton(
	"Red Side Auton",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Right Side Auton 2: Electric Boogaloo\n",
	[]() -> void {
        // Pre-Auton Stuff
        pros::Task my_task(LadybrownTask, (void*)"PROS");
        Controller.print(0, 0, "The Right Side Auton 2");
        chassis.setPose(-12, -54, 128.01);

        // Alliance Stake Scoring
        chassis.moveToPoint(-5, -59.5, 1000, {.forwards = true}, false);
        ladybrownPosition = 3;
        my_task.notify();
        pros::delay(800);
        ladybrownPosition = 1;
        my_task.notify();

        // Pick up 1st mobile goal
        chassis.moveToPoint(-22, -26, 1250, {.forwards = false, .maxSpeed = 90}, false);
        pros::delay(250);
        ClampPistons.set_value(1);
        pros::delay(200);

        // Pick up lone ring stack
        chassis.moveToPose(-48, -24, 320, 2250, {.forwards = true, .maxSpeed = 110});
        IntakeMotor.move(-127);
        pros::delay(3250);

        // Pick up left ring stack
        chassis.moveToPose(-45, -11, 35, 2500, {.forwards = true, .maxSpeed = 110});
        IntakeMotor.move(-127);
        pros::delay(250);

        // ! AWP Alt: Go for bar
        ladybrownPosition = 3;
        my_task.notify();
        chassis.moveToPose(24, -12, 315, 2000);

        /*
        // Start moving towards start position ring stack
        chassis.moveToPose(-4, -46, 90, 3500, {.forwards = true, .maxSpeed = 127});
        IntakeMotor.move(-127);
        pros::delay(700);
        IntakeMotor.brake();
        pros::delay(800);
        IntakeMotor.move(-127);

        // Drop 1st mobile goal
        ClampPistons.set_value(0);
        IntakeMotor.move(-127);
        pros::delay(200);
        IntakeMotor.move(-127);
        pros::delay(3000);

        // Pick up blue ring from start position ring stack
        chassis.moveToPose(8, -46, 90, 5000, {.forwards = true, .maxSpeed = 110});
        IntakeMotor.move(-127);
        pros::delay(200);

        chassis.moveToPoint(24, -24, 2000, {.forwards = false, .maxSpeed = 90});
        ClampPistons.set_value(1);
        IntakeMotor.move(-127);
        ladybrownPosition = 3;
        my_task.notify();
        chassis.moveToPoint(18, -18, 2000, {.forwards = false, .maxSpeed = 110});
        */

        my_task.remove();
    }
);

Auton pSkillsAuton(
	"P-Skills",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Programming Skills Auton\n",
	[]() -> void {
        Controller.print(0, 0, "The P-Skills auton");

        pros::Task my_task(LadybrownTask, (void*)"PROS");
        pros::Task my_task2(IntakeTask, (void*)"PROS");

        chassis.setPose(-4, -54, 180);

        ladybrownPosition = 3;
        my_task.notify();
        pros::delay(800);
        ladybrownPosition = 1;
        my_task.notify();

        // Pick up mobile goal
        chassis.moveToPoint(24, -48, 2000, {.forwards = false, .maxSpeed = 90}, false);
        ClampPistons.set_value(1);
        IntakeSpeed = -127;

        chassis.moveToPoint(24, -24, 2000, {.forwards = true, .maxSpeed = 90}, false);

        chassis.moveToPoint(50, -26, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPose(60, -48, 180, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPoint(48, -48, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPoint(48, -60, 2000, {.forwards = true, .maxSpeed = 90}, false);

        IntakeSpeed = 0;
        chassis.moveToPose(60, -60, 315, 2000, {.forwards = false, .maxSpeed = 90}, false);
        ClampPistons.set_value(0);
        
        // ! PART 2 BEGINS HERE

        // Pick up mobile goal
        chassis.moveToPoint(-24, -48, 2000, {.forwards = false, .maxSpeed = 90}, false);
        ClampPistons.set_value(1);
        IntakeSpeed = -127;

        chassis.moveToPoint(-24, -24, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPoint(-48, -24, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPose(-60, -48, 180, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPoint(-48, -48, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPoint(-48, -60, 2000, {.forwards = true, .maxSpeed = 90}, false);

        IntakeSpeed = 0;
        chassis.moveToPose(-60, -60, 315, 2000, {.forwards = true, .maxSpeed = 90}, false);
        ClampPistons.set_value(0);

        pros::delay(20);
        /*
        */
    }
);



Auton lemLibAuton(
	"P-Skills",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Programming Skills Auton\n",
	[]() -> void {
        Controller.print(0, 0, "The P-Skills auton");
        chassis.setPose(0, 0, 0);
        chassis.moveToPoint(0, 36, 10000);
        // chassis.turnToHeading(180, 100000);
        pros::delay(20);
    }
);



unsigned short int autonSelect = redQualsAuton.autonNum;



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