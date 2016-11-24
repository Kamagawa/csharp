#ifndef CONTROLS_C
#define CONTROLS_C

#include "ports.c"

void init() {
    SensorType[WHEEL_TOUCH] = sensorTouch;
    SensorType[COLOR] = sensorColorNxtFULL;
    SensorType[ULTRA] = sensorSONAR;
    SensorType[TRAY_TOUCH] = sensorTouch;
}

#endif
