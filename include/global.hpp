#include "api.h"
#include "lemlib/api.hpp"

extern pros::Controller Controller;

extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;

extern lemlib::ExpoDriveCurve throttle_curve;
extern lemlib::ExpoDriveCurve steer_curve;
extern lemlib::Drivetrain drivetrain;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::OdomSensors sensors;
extern lemlib::Chassis chassis;

extern pros::Motor IntakeMotor;

extern pros::Rotation Rotation;
extern pros::adi::DigitalOut ClampPistons;

extern std::array<std::string,7> MotorNameList;
extern std::array<pros::Motor*,1> MotorObjectList;
extern std::array<pros::MotorGroup*, 2> MotorGroupObjectList;
extern std::vector<int> MotorArraySizes;
extern int motorCount;

extern void InitMotorArraySizes();

extern unsigned short int autonSelect;

class Auton {
	public:
		// Increases everytime an auton is created, allowing us to assign a unique number identifier to each auton
	    static unsigned short int autonCount;

		// The name of the auton, assigned by the programmer via the constructor
		const char * name;
		// The description for the auton that will be seen on the auton selector, assigned by the programmer via the constructor
		const char * description;
		// The number identifier for the auton, automatically calculated in the constructor
		int autonNum;
		// The actions performed during the auton, assigned by the programmer via the constructor
		std::function<void()> routine;

		// The constructor to create a new auton
        Auton(const char * autonName, const char * autonDescription, std::function<void()> autonRoutine);
};

extern std::vector<lv_obj_t *> AutonButtons;
extern std::vector<Auton> AutonObjectList;

extern bool driveReversed;
extern void ControllerDisplay();