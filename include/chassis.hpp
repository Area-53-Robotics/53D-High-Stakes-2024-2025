#include "lemlib/chassis/chassis.hpp"

extern bool isBlue;

extern void moveToPoint(float x, float y, int timeout, lemlib::MoveToPointParams params, bool async);

extern void moveToPose(float x, float y, float theta, int timeout, lemlib::MoveToPoseParams params, bool async);

extern void swingToHeading(float theta, lemlib::DriveSide lockedSide, int timeout, lemlib::SwingToHeadingParams params, bool async);

extern void swingToPoint(float x, float y, lemlib::DriveSide lockedSide, int timeout, lemlib::SwingToPointParams params, bool async);

extern void turnToHeading(float theta, int timeout, lemlib::TurnToHeadingParams params, bool async);

extern void turnToPoint(float x, float y, int timeout, lemlib::TurnToPointParams params, bool async);