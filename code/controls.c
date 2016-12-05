/** controls.c 
 * The functions in this file are used to operate the robot's subsystems, of which
 * there are three:
 * - Wheels: located behind the cartridge exit hole; feeds, retracts, and ejects pencils
 * - Belt: located beneath the cartridge; feeds pencils to the wheel subsystem
 * - Tray: located in front of the cartridge; aligns the cartridge exit hole with
 *         the sharpener hole or appropriate colour bin
 *
 * Constants:
 * const float DIAM_CM = 3.7;
 * const float CIRCUM_CM = DIAM_CM * PI;
 * const int ENC_TOL = 1;
 * const int N_BINS = 7;
 * const float BIN_DIST_CM = 1;
 * const int JAM_THRESHOLD = 100;

 * Functions:
 * void init()
 * bool moveBelt(int power, int tMs = -1)
 * bool spinWheels (int power, int tMs = -1)
 * bool moveTray (int power, float distCm = 0)
 * void pauseMotors()
 * void resumeMotors() */

#ifndef CONTROLS_C
#define CONTROLS_C

#include "ports.c"
#include "util.c"

const float DIAM_CM = 3.7;
const float CIRCUM_CM = DIAM_CM * PI;
const int ENC_TOL = 1;
const int N_BINS = 7;
const float BIN_DIST_CM = 1;
const int JAM_THRESHOLD = 100;

static int motorCache[3] = { 0, 0, 0 };

/** init
 * Initializes all sensors to be used by setting the |SensorType| of each port. */
void init() {
	SensorType[WHEEL_TOUCH] = sensorTouch;
	SensorType[COLOR] = sensorColorNxtFULL;
	SensorType[ULTRA] = sensorSONAR;
	SensorType[TRAY_TOUCH] = sensorTouch;
}

/** moveBelt 
 * Moves the belt at the given power. Optionally, the motors can be set to run for a 
 * duration determined by the value of |tMs|. By default, the belt will continue to
 * move until stopped programmatically by a future call to |moveBelt()|. This function
 * is used in actions.c to move the pencil towards the cartridge exit hole.
 *
 * A return value of |false| indicates a motor jam.
 *
 * @param power: power level at which to operate the belt
 * @param tMs: optional duration (in ms) for which to operate the belt 
 * @return bool: a value of |false| indicates a motor jam */
bool moveBelt(int power, int tMs = -1) {
	bool success;

	motor[BELT] = power;

	// a jam occurs if the motor speed is too low
	success = power != 0 || getSpeed(BELT, 10) < JAM_THRESHOLD;

	// if |tMs|'s value is non-default, then stop the motor after |tMs| milliseconds 
	if (tMs > -1 && success) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) {
		}
		motor[BELT] = 0;
		// stop motor if there is a jam
	} else if (!success) {
		motor[BELT] = 0;
	}

	return success;
}

/** spinWheels 
 * Spins the wheels at the given power. Optionally, the motors can be set to run for a 
 * duration determined by the value of |tMs|. By default, the wheels will continue to
 * spin until stopped programmatically by a future call to |spinWheels()|. This function
 * is used in actions.c to feed pencils into the sharpener and eject them into the colour
 * bins.
 *
 * A return value of |false| indicates a motor jam.
 *
 * @param power: power level at which to operate the wheels
 * @param tMs: optional duration (in ms) for which to operate the wheels 
 * @return bool: a value of |false| indicates a motor jam */
bool spinWheels(int power, int tMs = -1) {
	bool success;

	motor[WHEEL] = -power;

	// a jam occurs if the motor speed is too low
	success = power != 0 || getSpeed(BELT, 10) < JAM_THRESHOLD;

	// if |tMs|'s value is non-default, then stop the motor after |tMs| milliseconds 
	if (tMs > -1 && success) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) {
		}
		motor[WHEEL] = 0;
		// stop motor if there is a jam
	} else if (!success) {
		motor[WHEEL] = 0;
	}
	return success;
}

/** spinWheels 
 * Moves the tray at the given power. Optionally, the tray can be set to move for a 
 * distance specified by the value of |distCm|. This function
 * is used in actions.c to align the correct part of the tray with the cartridge
 * exit hole.
 * 
 * A return value of |false| indicates a motor jam.
 *
 * @param power: power level at which to operate the tray
 * @param tMs: optional duration (in ms) for which to operate the tray 
 * @return bool: a value of |false| indicates a motor jam */
bool moveTray(int power, float distCm = 0) {
	bool success;

	motor[TRAY] = -power;

	// a jam occurs if the motor speed is too low
	success = power != 0 || getSpeed(BELT, 10) < JAM_THRESHOLD;

	if (distCm > 0 && success) {
		int encVal = distCm / CIRCUM_CM * 360;
		nMotorEncoder[TRAY] = 0;
		nMotorEncoderTarget[TRAY] = encVal;
		while (abs(nMotorEncoder[TRAY]) < encVal) {
		}
		motor[TRAY] = 0;
		// stop motor if there is a jam
	} else if (!success) {
		motor[TRAY] = 0;
	}

	return true;
}

/**
 * Stops all motors and records their power values. This function is used
 * to disable the robot if the task |monitorTray()| (in main.c) detects a tray
 * removal. */
void pauseMotors() {
	motorCache[0] = motor[BELT];
	motorCache[1] = motor[WHEEL];
	motorCache[2] = motor[TRAY];
	motor[BELT] = motor[WHEEL] = motor[TRAY] = 0;
}

/**
 * Sets the disabled motors to their power values prior to being disabled. This function 
 * is used to re-enable the robot in the task |monitorTray()| (in main.c) when the tray 
 * is restored. */
void resumeMotors() {
	motor[BELT] = motorCache[0];
	motor[WHEEL] = motorCache[1];
	motor[TRAY] = motorCache[2];
}

#endif
