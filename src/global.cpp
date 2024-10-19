#include "lemlib/chassis/trackingWheel.hpp"
#include "main.h"
#include "pros/imu.hpp"

pros::Controller Controller(pros::E_CONTROLLER_MASTER);

/*
    Dead Ports: 5, 16, 17 (last updated 12/1/23)
    Best Battery: 13
*/

pros::MotorGroup left_mg({-20, -18, -11});
pros::MotorGroup right_mg({14, 13, 10});

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);


lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              &right_mg, // right motor group
                              11, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                            450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

lemlib::ControllerSettings lateral_controller(8, // proportional gain (kP) 10
                                              0, // integral gain (kI)
                                              11, // derivative gain (kD) 3
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::ControllerSettings angular_controller(6, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              34, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew) 
);
pros::IMU imu(3);

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu   // inertial sensor
);

lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);

pros::Motor IntakeMotor(9, pros::v5::MotorGears::blue);
pros:: Motor RedirectMotor(15,pros::v5::MotorGears::red);

pros::adi::DigitalIn RedirectSwitch('C');

pros::adi::DigitalOut ClampPistons(1);
pros::adi::DigitalOut ArmPistons(2);

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
bool intakeRedirecting = false;

void ControllerDisplay() {
    if(!driveReversed) Controller.print(0, 0, "Reversed: false");
    else if(driveReversed) Controller.print(0, 0, "Reversed: true");
}