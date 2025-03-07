#include "main.h"

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
        else if(IntakeSpeed == 0) IntakeMotor.brake();
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

    // Adds the new auton object to the list of created auton objects
    AutonObjectList.push_back(*this);
}

Auton blueGoalRushAuton(
	"Blue Goal Rush",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Blue Goal Rush Auton\n",
	[]() -> void {
        pros::Task my_task(LadybrownTask, (void*)"PROS");
        pros::Task my_task2(IntakeTask, (void*)"PROS");
        Controller.print(0, 0, "The Blue Side Auton");
        chassis.setPose(-12, -54, 128.01);

        // Alliance Stake Scoring
        chassis.moveToPoint(-5, -59.5, 1000, {.forwards = true}, false);
        ladybrownPosition = 3;
        my_task.notify();
        pros::delay(800);
        ladybrownPosition = 1;
        my_task.notify();

        // Pick up 1st ring
        chassis.moveToPose(-45, -23, 20, 3000, {.forwards = true, .maxSpeed = 110}, false);
        IntakeSpeed = -127;
        pros::delay(900);
        IntakeSpeed = 0;

        // Pick up auton line mobile goal
        chassis.moveToPoint(-48, -12, 1400, {.forwards = false, .maxSpeed = 90}, false);
        pros::delay(50);
        ClampPistons.set_value(1);
        pros::delay(50);

        // Drop auton line mobile goal
        chassis.moveToPoint(-48, -48, 2500, {.forwards = false, .maxSpeed = 90}, false);
        pros::delay(50);
        ClampPistons.set_value(0);
        pros::delay(50);

        // Grab 2nd mobile goal
        chassis.moveToPose(-26, -26, 225, 2000, {.forwards = false, .maxSpeed = 110}, false);
        pros::delay(50);
        ClampPistons.set_value(1);
        pros::delay(50);

        IntakeSpeed = -127;
        pros::delay(500);
        IntakeSpeed = 0;

        ladybrownPosition = 3;
        my_task.notify();
        moveToPose(-12, -12, 90, 2000, {.forwards = true, .maxSpeed = 110}, false);

        my_task2.remove();
    }
);

Auton redGoalRushAuton(
	"Red Goal Rush",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Red Goal Rush Auton\n",
	[]() -> void {
        pros::Task my_task(LadybrownTask, (void*)"PROS");
        pros::Task my_task2(IntakeTask, (void*)"PROS");

        Controller.print(0, 0, "The Red Side Auton");
        chassis.setPose(12, -54, 231.99);

        // Alliance Stake Scoring
        moveToPoint(5, -59.5, 1000, {.forwards = true}, false);
        ladybrownPosition = 3;
        my_task.notify();
        pros::delay(800);
        ladybrownPosition = 1;
        my_task.notify();

        // Pick up 1st mobile goal
        moveToPoint(22, -26, 1250, {.forwards = false, .maxSpeed = 90}, false);
        pros::delay(50);
        ClampPistons.set_value(1);
        pros::delay(50);

        // Pick up lone ring stack
        moveToPose(48, -24, 40, 2000, {.forwards = true, .maxSpeed = 110});
        IntakeSpeed = -127;
        pros::delay(3000);

        // Touch the bar
        ladybrownPosition = 3;
        my_task.notify();
        moveToPose(-20, -5, 45, 2000, {.forwards = true, .maxSpeed = 110});

        my_task2.remove();


         /*pros::Task my_task(LadybrownTask, (void*)"PROS");
       moveDrivetrain(-100,225);
       pros::delay(1000);
       ClampPistons.set_value(1);
       pros::delay(1000);
       IntakeMotor.move(-500);
       pros::delay(1500);
       turnDrivetrain(-100, 300);
       pros::delay(1000);
       moveDrivetrain(300,210);
       pros::delay(2000);
       ClampPistons.set_value(0);
       moveDrivetrain(-600, 230);
        ladybrownPosition = 3;

        */

       //IntakeMotor.move(-500);

       //IntakeMotor.brake();
        //ClampPistons.set_value(0); */
        // chassis.calibrate();
        // chassis.setPose(0, 0, 0);
        // chassis.moveToPoint(0, 48, 10000);
        // chassis.turnToHeading(90, 2000);
         my_task.notify();
        my_task.remove();
        Controller.print(0, 0, "The right auton");
        pros::delay(20);
    }
);

Auton blueRingSideAuton(
	"Blue Ring Side",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Blue Ring Side Auton\n",
	[]() -> void {
        // Pre-Auton Stuff
        pros::Task my_task(LadybrownTask, (void*)"PROS");
        pros::Task my_task2(IntakeTask, (void*)"PROS");
        Controller.print(0, 0, "The Blue Side Auton");
        chassis.setPose(12, -54, 231.99);

        // Alliance Stake Scoring
        moveToPoint(5, -59.5, 1000, {.forwards = true}, false);
        ladybrownPosition = 3;
        my_task.notify();
        pros::delay(800);
        ladybrownPosition = 1;
        my_task.notify();

        // Pick up 1st mobile goal
        moveToPoint(22, -26, 1250, {.forwards = false, .maxSpeed = 90}, false);
        pros::delay(50);
        ClampPistons.set_value(1);
        pros::delay(50);

       

        // Pick up lone ring stack
        //moveToPose(48, -24, 40, 2000, {.forwards = true, .maxSpeed = 110});
        moveToPoint(48, -24, 1250, {.forwards = true, .maxSpeed = 90}, false);
        IntakeSpeed = -127;
        pros::delay(3000);
        //IntakeSpeed = 0;

        // Pick up left ring stack
        chassis.turnToPoint(48, 0, 1250);
        pros::delay(200);
        RingRush();
        pros::delay(200);
        moveToPoint(48, -13, 1250, {.forwards = true, .maxSpeed = 90}, false);
        pros::delay(2000);
        moveToPoint(48, -24, 1250, {.forwards = false, .maxSpeed = 90}, false);
        RingRushPiston.set_value(0);
        /*moveToPoint(46, -7.5, 2000, {.forwards = true, .maxSpeed = 90}, false);
        moveToPoint(46, -7.5, 2000, {.forwards = true, .maxSpeed = 90}, false);
        pros::delay(1500);*/

         moveToPoint(48, -20, 1250, {.forwards = false, .maxSpeed = 90}, false);
        
        //moveToPoint(53, -24, 1250, {.forwards = false, .maxSpeed = 90}, false);

       



        // ! AWP Alt: Go for bar
        /*ladybrownPosition = 3;
        my_task.notify();
        moveToPose(-24, -12, 45, 2000, {.forwards = true, .maxSpeed = 110});
        IntakeSpeed = 0; */
        
        /*
        // Start moving towards start position ring stack
        moveToPose(4, -46, 270, 4000, {.forwards = true, .maxSpeed = 127});
        IntakeSpeed = -127;
        pros::delay(700);
        IntakeSpeed = 0;
        pros::delay(800);
        IntakeSpeed = -127;

        // Drop 1st mobile goal
        ClampPistons.set_value(0);
        IntakeSpeed = -127;
        pros::delay(2700);

        // Pick up blue ring from start position ring stack
        moveToPose(-8, -46, 270, 2500, {.forwards = true, .maxSpeed = 110});
        pros::delay(400);
        IntakeSpeed = 0;

        moveToPoint(-26, -22, 2000, {.forwards = false, .maxSpeed = 70}, false);
        ClampPistons.set_value(1);
        IntakeSpeed = -127;
        moveToPose(-20, -20, 45, 1000, {});
        // moveToPoint(-18, -18, 2000, {.forwards = false, .maxSpeed = 110});
            */
       // my_task.remove();
        my_task2.remove();
    }
);

Auton redRingSideAuton(
	"Red Ring Side",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Red Ring Side Auton\n",
	[]() -> void {
       pros::Task my_task(LadybrownTask, (void*)"PROS");
        pros::Task my_task2(IntakeTask, (void*)"PROS");
        Controller.print(0, 0, "The Blue S ide Auton");
        chassis.setPose(-12, -54, -231.99);

        // Alliance Stake Scoring
        moveToPoint(-5, -59.5, 1000, {.forwards = true}, false);
        ladybrownPosition = 3;
        my_task.notify();
        pros::delay(800);
        ladybrownPosition = 1;
        my_task.notify();

        // Clamp mobile goal
        moveToPoint(-22, -24, 1250, {.forwards = false, .maxSpeed = 90}, false);
        pros::delay(50);
        ClampPistons.set_value(1);
        pros::delay(50);

        moveToPose(-48, -24, 30, 1700, {.forwards = true, .maxSpeed = 110});
        IntakeSpeed = -127;
        pros::delay(2500);

        moveToPose(-42, -6, 10, 1200, {.forwards = true, .maxSpeed = 110}, false);
        pros::delay(1500);

        moveToPoint(-40, -22, 1750, {.forwards = true, .maxSpeed = 110}, false);

        moveToPose(-39, -12, 22, 2000, {.forwards = true, .maxSpeed = 90}, false);
        pros::delay(1500);

        IntakeSpeed = 0;
        ladybrownPosition = 3;
        my_task.notify();
        moveToPose(-12, -12, 90, 2000, {.forwards = true, .maxSpeed = 110}, false);

        // Intake & outtake (requested by Makhi) to prevent jamming
        IntakeSpeed = 127;
        pros::delay(500);
        IntakeSpeed = -127;
        pros::delay(500);
        IntakeSpeed = 0;

        my_task2.remove();


      /*  // Pre-Auton Stuff
        pros::Task my_task(LadybrownTask, (void*)"PROS");
        pros::Task my_task2(IntakeTask, (void*)"PROS");
        Controller.print(0, 0, "The Blue Side Auton");
        chassis.setPose(12, -54, 231.99);

        // Alliance Stake Scoring
        moveToPoint(5, -59.5, 1000, {.forwards = true}, false);
        ladybrownPosition = 3;
        my_task.notify();
        pros::delay(800);
        ladybrownPosition = 1;
        my_task.notify();

        // Pick up 1st mobile goal
        moveToPoint(22, -26, 1250, {.forwards = true, .maxSpeed = 90}, false);
        pros::delay(50);
        ClampPistons.set_value(1);
        pros::delay(50);

        // Pick up lone ring stack
        moveToPose(48, -24, 30, 2000, {.forwards = true, .maxSpeed = 110});
        IntakeSpeed = -127;
        pros::delay(3000);

        // Pick up left ring stack
        moveToPose(43, -7, 335, 1200, {.forwards = true, .maxSpeed = 110});
        pros::delay(1200);
        IntakeSpeed = 0;
        */
    }
);

Auton newGoalRushAuton(
	"Red Ring Side",
	"Last Updated: N/A\n"
	"-----------------------------------------------------\n"
	"The Red Ring Side Auton\n",
	[]() -> void {
       pros::Task my_task(LadybrownTask, (void*)"PROS");
        pros::Task my_task2(IntakeTask, (void*)"PROS");
        Controller.print(0, 0, "The Blue Side Auton");
        chassis.setPose(58, -54, 0);
        chassis.turnToPoint(47, -24, 900);
        GoalRush();
        pros::delay(200);
        IntakeSpeed = -68;
        chassis.moveToPoint(45, -20,1200,{.forwards = true, .maxSpeed = 110}, false);
        pros::delay(410);
        IntakeSpeed = 0;
        pros::delay(200);
        GoalRush();
        pros::delay(600);
        chassis.moveToPoint(48, -35, 1700, {.forwards = false, .maxSpeed = 127}, false);
        pros::delay(200);
        GoalRush();
        chassis.moveToPoint(48, -34, 1700, {.forwards = false, .maxSpeed = 127}, false);
        chassis.moveToPoint(48, -47, 1700, {.forwards = false, .maxSpeed = 127}, false);
        chassis.turnToHeading(170, 1000);
        chassis.moveToPoint(48, -20, 1700, {.forwards = false, .maxSpeed = 127}, false);
        pros::delay(200);
        ClampPistons.set_value(1);
        IntakeSpeed = -110;
        pros::delay(660);
        IntakeSpeed = 0;
        GoalRush();
        pros::delay(200);
        ClampPistons.set_value(0);
        chassis.moveToPoint(48, -47, 1700, {.forwards = true, .maxSpeed = 127}, false);
        chassis.moveToPose(24, -26, 90, 1700, {.forwards = false, .maxSpeed = 127}, false);
        chassis.moveToPoint(23, -50, 1700, {.forwards = false, .maxSpeed = 127}, false);
        ClampPistons.set_value(1);
        IntakeSpeed = -127;
        pros::delay(500);
        IntakeSpeed = 0;
        pros::delay(500);
        ClampPistons.set_value(0);
        pros::delay(200);
        chassis.moveToPoint(0, -48, 1700, {.forwards = true, .maxSpeed = 127}, false);
        IntakeSpeed = -127;
        chassis.moveToPoint(-1, -49, 1700, {.forwards = true, .maxSpeed = 127}, false);
        
        

        //GoalRush();
        //pros::delay(200);
       // GoalRushPiston.set_value(0);
       // chassis.moveToPoint(58, -43, 1700, {.forwards = false, .maxSpeed = 127}, false);
        /*chassis.moveToPose(-58, -33, 180, 1200, {.forwards = false, .maxSpeed = 110}, false); 
        chassis.moveToPoint(-53,-24, 1700, {.forwards = false, .maxSpeed = 127}, false);
        ClampPistons.set_value(1);
        pros::delay(200);
        IntakeSpeed = -127;
        pros::delay(2000);
        IntakeSpeed = 0;
        ClampPistons.set_value(0);
        pros::delay(200);
        chassis.moveToPose(-46,-25,-90,1700, {.forwards = false, .maxSpeed = 127}, false);
        chassis.moveToPoint(-24,-24, 1700, {.forwards = false, .maxSpeed = 127}, false); 
        ClampPistons.set_value(1); */   
        //chassis.moveToPoint(-58,-54, 1700, {.forwards = false, .maxSpeed = 127}, false);        
        //chassis.moveToPoint(-24,-24, 1700, {.forwards = false, .maxSpeed = 127}, false);        
        //chassis.moveToPoint(-46,-25,1700, {.forwards = true, .maxSpeed = 127}, false);
        //IntakeSpeed = 127;
        //pros::delay(1000);
        //IntakeSpeed = 0;
        
        //ClampPistons.set_value(1);
        //chassis.moveToPoint(-58, -43, 1500, {.forwards = false, .maxSpeed = 127}, false);
        //GoalRush();
        pros::delay(200);
        //chassis.moveToPoint(-50, -26, 1700, {.forwards = false, .maxSpeed = 127}, false);
        //ClampPistons.set_value(1);
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
        // pros::Task my_task2(IntakeTask, (void*)"PROS");

        chassis.setPose(-4, -54, 180);

        ladybrownPosition = 3;
        my_task.notify();
        pros::delay(800);
        ladybrownPosition = 1;
        my_task.notify();

        // Pick up mobile goal
        chassis.moveToPoint(24, -48, 2000, {.forwards = false, .maxSpeed = 90}, false);
        ClampPistons.set_value(1);
        IntakeMotor.move(-127);

        chassis.moveToPoint(24, -24, 2000, {.forwards = true, .maxSpeed = 90}, false);

        chassis.moveToPoint(50, -26, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPose(60, -48, 180, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPoint(48, -48, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPoint(48, -60, 2000, {.forwards = true, .maxSpeed = 90}, false);

        IntakeMotor.brake();
        chassis.moveToPose(60, -60, 315, 2000, {.forwards = false, .maxSpeed = 90}, false);
        ClampPistons.set_value(0);

        chassis.moveToPoint(48, -48, 2000, {.forwards = true, .maxSpeed = 90}, true);
        chassis.moveToPoint(58, -58, 2000, {.forwards = false, .maxSpeed = 90}, true);
        chassis.moveToPoint(48, -48, 2000, {.forwards = true, .maxSpeed = 90}, true);

        // ! PART 2 BEGINS HERE



        // Pick up mobile goal
        chassis.moveToPoint(-24, -48, 2000, {.forwards = false, .maxSpeed = 90}, false);
        pros::delay(1000);
        ClampPistons.set_value(1);
        IntakeMotor.move(-127);

        chassis.moveToPoint(-24, -24, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPoint(-48, -24, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPose(-60, -48, 180, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPoint(-48, -48, 2000, {.forwards = true, .maxSpeed = 90}, false);
        chassis.moveToPoint(-48, -60, 2000, {.forwards = true, .maxSpeed = 90}, false);

        IntakeMotor.brake();
        chassis.moveToPoint(-60, -60,  2000, {.forwards = true, .maxSpeed = 90}, false);
        ClampPistons.set_value(0);

        pros::delay(20);
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



unsigned short int autonSelect = blueRingSideAuton.autonNum;



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