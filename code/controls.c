#ifndef CONTROLS_C
#define CONTROLS_C

#include "ports.c"
#include "util.c"

const float DIAM_CM = 3.7;
const float CIRCUM_CM = DIAM_CM * PI;
const int ENC_TOL = 1
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
	bool jammed;

	motor[BELT] = power;
	jammed = getSpeed(BELT, 10) < JAM_THRESHOLD && power != 0;

	if (tMs > -1 && !jammed) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) { }
		motor[BELT] = 0;
	} else if (jammed) {
		motor[BELT] = 0;
	}

	return jammed;
}

bool spinWheels (int power, int tMs = -1)
{
	bool jammed;

	motor[WHEEL] = power;
	jammed = getSpeed(BELT, 10) < JAM_THRESHOLD && power != 0;

	if (tMs > -1 && !jammed) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) { }
		motor[WHEEL] = 0;
	} else if (jammed) {
		motor[WHEEL] = 0;
	}

	return jammed;
}

bool moveTray (int power, float distCm = 0)
{
	bool jammed;

	motor[TRAY] = power;
	jammed = getSpeed(BELT, 10) < JAM_THRESHOLD && power != 0;

	if (distCm > 0 && !jammed) {
		int encVal = distCm / CIRCUM_CM * 360;
		nMotorEncoder[TRAY] = 0;
		nMotorEncoderTarget[TRAY] = encVal;
		while(nMotorRunState[TRAY] != runStateIdle) { }
		motor[TRAY] = 0;
	} else if (jammed) {
		motor[TRAY] = 0;
	}

	return jammed;
}

#endif
