#ifndef ACTIONS_C
#define ACTIONS_C

#include "controls.c"
#include "ports.c"

bool sharpenPencil(int ms) {
	// push pencil into sensor
	// spinWheels(50);
	// wait while change in speed less than x
	//	 or while speed is greater than x
	// spinWheels(0);

	// pencil reaches sharpener; hold and wait
	// ClearTimer(T1);
	// while (time1[T1] < ms) { }

	// bring pencil back into cartridge
	// spinWheels(-50);
	// while (sensorValue[WHEEL_TOUCH] == 1) { }
	// 		or speed is not 0
	// spinWheels(0);

	return true;
}

void zeroTray(){
	while(!SensorValue[TRAY_TOUCH]){
		motor[TRAY] = 75;//change as needed
	}
}

void ejectPencil(){
	motor[WHEEL] = 100;
	while(!SensorValue[WHEEL_TOUCH]){}
	while(SensorValue[WHEEL_TOUCH]){}

	nMotorEncoder[WHEEL] = 0;
	while(nMotorEncoder[WHEEL] < 500){}//change as needed
	motor[WHEEL] = 0;
}

int getPencilColor(){
	clearTimer(T1);
	int count = 0;
	int colorType[7] = { 0, 0, 0, 0, 0, 0, 0 };
	while(time1[T1] < 1000 && count++ < 1000){//get average colour seen
		colorType[SensorValue[COLOR]]++;
	}

	int modeColorFreq = 0, modeColor = 0;
	for (int i = 0; i < 7; i++){//finds colour sensed the most frequently
		if (colorType[i] > modeColorFreq){
			modeColorFreq = ColorType[i];
			modeColor = i;
		}
	}
	return modeColor;
}

#endif
