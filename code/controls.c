#ifndef CONTROLS_C
#define CONTROLS_C

#include "ports.c"

void init() {
	SensorType[WHEEL_TOUCH] = sensorTouch;
	SensorType[COLOR] = sensorColorNxtFULL;
	SensorType[ULTRA] = sensorSONAR;
	SensorType[TRAY_TOUCH] = sensorTouch;
}

void moveBelt(int power, int tMs = -1) {
	motor[BELT] = power;

	if (tMs > -1) {
		clearTimer(T1);
		while (time1[T1] < tMs) { }
		motor[BELT] = 0;
	}
}

#endif
