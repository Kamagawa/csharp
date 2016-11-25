#ifndef CONTROLS_C
#define CONTROLS_C

#include "ports.c"
#include "util.c"

const float DIAM_CM = 3.7;
const float CIRCUM_CM = DIAM_CM * PI;
const int ENC_TOL = 1;
const int N_BINS = 7;
const int BIN_DIST = 0;
const int JAM_THRESHOLD = 10;

void init() {
	SensorType[WHEEL_TOUCH] = sensorTouch;
	SensorType[COLOR] = sensorColorNxtFULL;
	SensorType[ULTRA] = sensorSONAR;
	SensorType[TRAY_TOUCH] = sensorTouch;
}

bool moveBelt(int power, int tMs = -1) {
	bool success;

	motor[BELT] = power;
	success = getSpeed(BELT, 10) > JAM_THRESHOLD || power != 0;

	if (tMs > -1 && success) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) { }
		motor[BELT] = 0;
	} else if (!success) {
		motor[BELT] = 0;
	}

	return success;
}

bool spinWheels (int power, int tMs = -1)
{
	bool success;

	motor[WHEEL] = power;
	success = getSpeed(BELT, 10) > JAM_THRESHOLD || power != 0;

	if (tMs > -1 && success) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) { }
		motor[WHEEL] = 0;
	} else if (!success) {
		motor[WHEEL] = 0;
	}

	return success;
}

bool moveTray (int power, float distCm = 0)
{
	bool success;

	motor[TRAY] = power;
	success = getSpeed(BELT, 10) > JAM_THRESHOLD || power != 0;

	if (distCm > 0 && success) {
		int encVal = distCm / CIRCUM_CM * 360;
		nMotorEncoder[TRAY] = 0;
		nMotorEncoderTarget[TRAY] = encVal;
		while(nMotorRunState[TRAY] != runStateIdle) { }
		motor[TRAY] = 0;
	} else if (!success) {
		motor[TRAY] = 0;
	}

	return success;
}

#endif
