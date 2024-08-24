#include "api.h"
#include "pros/adi.hpp"

pros::Controller Controller(pros::E_CONTROLLER_MASTER);
pros::adi::DigitalOut ClampPistons(1);
