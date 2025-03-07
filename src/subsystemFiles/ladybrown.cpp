#include "main.h"

/*
    1: Position 1 - Starting
    2: Position 2 - Intake
    3: Position 3 - Mobile Goal
*/
short int ladybrownPosition = 1;

void LadybrownSwitch(bool increase) {
    // If the ladybrown position needs to increase...
    if (increase) {
        // then increase the ladybrown position by 1
        if (ladybrownPosition < 3) ladybrownPosition++;
        // and if the ladybrown position would increase to 4, then instead, wrap around back to 1
        else ladybrownPosition = 1;
    // If the ladybrown position needs to decrease...
    } else {
        // then decrease the ladybrown position by 1
        if (ladybrownPosition > 1) ladybrownPosition--;
        // and if the ladybrown position would decrease to 0, then instead, wrap around back to 3
        else ladybrownPosition = 3;
    }
}

void LadybrownTask(void * param) {
    // Variable representing the ladybrown task
    pros::Task task = pros::Task::current();

    // The angle (in degrees) for each position
    const float position1 = 350;
    const float position2 = 317.50;
    const float position3 = 198.52;

    // Constant variable that is multiplied by the ladybrown angle error to determine ladybrown motor voltage
    const float kP = 150;

    // Initializes the variables needed for the ladybrown proportional movement algorithm
    double ladybrownAngle;
    double error;
    double targetAngle;
    short int power;

    while(true) {
        // Waits to start moving the ladybrown until after the driver has pushed one of the ladybrown controller buttons
        while(task.notify_take(true, 10));

        // Variable to track how long the ladybrown movement is taking
        int timeout = 0;
        
        // Sets the ladybrown target angle based on the target position
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

        // Obtains the angle of the ladybrown in degrees
        ladybrownAngle = LadybrownRotation.get_angle() / 100.0;
        // Calculates the error (difference) between the target ladybrown angle and the current ladybrown angle
        error = targetAngle - ladybrownAngle;

        // The ladybrown will move toward the target point while the error is greater than 0.01 degrees or until the movement has lasted for 10,000 msec
        while((std::abs(error) > 0.01) && (timeout < 10000)) {
            // Sets the ladybrown target angle based on the target position
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

            // Obtains the angle of the ladybrown in degrees
            ladybrownAngle = LadybrownRotation.get_angle() / 100.0;
            // If the ladybrown passes the 360 degree mark, it will treat angles 1-50 degrees as 361-410 degrees
            if (ladybrownAngle < 50) ladybrownAngle = 360 + ladybrownAngle;
            // Calculates the error (difference) between the target ladybrown angle and the current ladybrown angle
            error = targetAngle - ladybrownAngle;
            // Calculate the appropriate voltage output for the ladybrown motors
            power = error * kP;
            // Set the ladybrown motors to move according to the calculated voltage
            LadybrownMotors.move_voltage(power);

            // Delays the continuation of the loop by 20 msec to free VEX brain resources
            timeout += 20;
            pros::Task::delay(20);
        }

        // Delays the continuation of the loop by 20 msec to free VEX brain resources
        pros::Task::delay(20);
    }
}