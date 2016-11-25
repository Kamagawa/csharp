#ifndef CONTROLS_C
#define CONTROLS_C

#include "ports.c"

const float DIAM_CM = 3.7;
const float CIRCUM_CM = DIAM_CM * PI;
const int ENC_TOL = 1
const int N_BINS = 7;
const int BIN_DIST = 0;

void init() {
	SensorType[WHEEL_TOUCH] = sensorTouch;
	SensorType[COLOR] = sensorColorNxtFULL;
	SensorType[ULTRA] = sensorSONAR;
	SensorType[TRAY_TOUCH] = sensorTouch;
}

void moveBelt(int power, int tMs = -1) {
	motor[BELT] = power;

	if (tMs > -1) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) { }
		motor[BELT] = 0;
	}
}

void spinWheels (int power, int tMs = -1)
{
	motor[WHEEL] = power;

	if (tMs > -1) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) { }
		motor[WHEEL] = 0;
	}
}

void moveTray (int power, float distCm = 0)
{
	motor[TRAY] = power;

	if (distCm > 0) {
		int encVal = distCm / CIRCUM_CM * 360;
		nMotorEncoder[TRAY] = 0;
		nMotorEncoderTarget[TRAY] = encVal;
		while(nMotorRunState[TRAY] != runStateIdle) { }
		motor[TRAY] = 0;
	}
}

#endif
