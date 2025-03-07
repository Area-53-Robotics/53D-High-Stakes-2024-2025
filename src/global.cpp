#include "main.h"
#include "pros/adi.hpp"

pros::Controller Controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup left_mg({-7, -9, -11}, pros::v5::MotorGears::blue);
pros::MotorGroup right_mg({15, 14, 17}, pros::v5::MotorGears::blue);

pros::MotorGroup LadybrownMotors({19, -20});

pros::IMU imu(4);
pros::Rotation LadybrownRotation(18);
pros::Rotation vertical_encoder(1);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, 0);


// Declares the intake motor and sets it to port 6
pros::Motor IntakeMotor(6, pros::v5::MotorGears::blue);

// Declares the clamp piston and sets it to adi port G
pros::adi::DigitalOut ClampPistons('E');
pros::adi::DigitalOut GoalRushPiston('B');
pros::adi::DigitalOut RingRushPiston('G');

lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              &right_mg, // right motor group
                              11, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);



lemlib::ControllerSettings lateral_controller(13, // proportional gain (kP) 10
                                              0, // integral gain (kI)
                                              90, // derivative gain (kD) 3
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::ControllerSettings angular_controller(2.52, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              14, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew) 
);

lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu   // inertial sensor
);

lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        nullptr, 
                        nullptr
);

// Array that stores strings representing the name of each motor
std::array<std::string,7> MotorNameList = {"BL", "ML", "FL", "BR", "MR", "FR", "Intake"};
// Array that stores pointers to all the independent motor objects
std::array<pros::Motor*,1> MotorObjectList = {&IntakeMotor};
// Array that stores pointers to all the motor groups
std::array<pros::MotorGroup*,2> MotorGroupObjectList = {&left_mg, &right_mg};

std::vector<int> MotorArraySizes;
int motorCount = 0;

void InitMotorArraySizes() {
    // Obtain the number of motors in each motor group
    for(pros::MotorGroup* motorGroup : MotorGroupObjectList) {
        MotorArraySizes.push_back(motorGroup->size());
    }

    // Obtain the number of independent motor objects
    MotorArraySizes.push_back(MotorObjectList.size());

    // Accumulate the motor counts into one variable, representing the total number of motors
    for(int size : MotorArraySizes) {
        motorCount += size;
    }
}

bool driveReversed = false;

void ControllerDisplay() {
    if(!driveReversed) Controller.print(0, 0, "Reversed: false");
    else if(driveReversed) Controller.print(0, 0, "Reversed: true");
}