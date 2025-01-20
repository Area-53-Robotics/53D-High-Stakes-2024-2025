#include "lemlib/chassis/chassis.hpp"
#include "global.hpp"

bool isBlue = true;

void moveToPoint(float x, float y, int timeout, lemlib::MoveToPointParams params, bool async = true) {
    if(isBlue) chassis.moveToPoint(x, y, timeout, params, async);
    else chassis.moveToPoint(x * -1, y, timeout, params, async);
}

void moveToPose(float x, float y, float theta, int timeout, lemlib::MoveToPoseParams params, bool async = true) {
    if(isBlue) chassis.moveToPose(x, y, theta, timeout, params, async);
    else chassis.moveToPose(x * -1, y, theta * -1, timeout, params, async);
}

void swingToHeading(float theta, lemlib::DriveSide lockedSide, int timeout, lemlib::SwingToHeadingParams params, bool async = true) {
    if(isBlue) chassis.swingToHeading(theta, lockedSide, timeout);
    else chassis.swingToHeading( theta * -1, lockedSide, timeout);
}

void swingToPoint(float x, float y, lemlib::DriveSide lockedSide, int timeout, lemlib::SwingToPointParams params, bool async = true) {
    if(isBlue) chassis.swingToPoint(x, y, lockedSide, timeout);
    else chassis.swingToPoint(x * -1, y, lockedSide, timeout);
}

void turnToHeading(float theta, int timeout, lemlib::TurnToHeadingParams params, bool async) {
    if(isBlue) chassis.turnToHeading(theta, timeout, params, async);
    else chassis.turnToHeading( theta * -1, timeout, params, async);
}

void turnToPoint(float x, float y, int timeout, lemlib::TurnToPointParams params, bool async) {
    if(isBlue) chassis.turnToPoint(x, y, timeout, params, async);
    else chassis.turnToPoint(x * -1, y, timeout, params, async);
}