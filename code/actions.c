#ifndef ACTIONS_C
#define ACTIONS_C

#include "controls.c"
#include "ports.c"
#include "util.c"

void promptStart() {
	displayString(3, "Press centre btn");
	displayString(4, "to start");
	waitForBtnPress(3);
}

bool displayEndScreen(int *histogram, int colorOrder) {

	string penColors[7] = {"invalid", "black: %d", "blue: %d",
	"green: %d", "yellow: %d", "red: %d", "white: %d", };


	displayString(0, "You pencils lol:");
	if (colorOrder == 0){
		for (int i = 0; i<7; i++){

			displayString(i, penColors[i], histogram[i]);
		}
	}
	else
	{
		int tbSorted [7];
		int *P_tbSorted = &tbSorted;

		for (int u = 0; u < 7 ; u ++){
			tbSorted[u] = histogram[u];
		}

		if (colorOrder == 1){
			sort (P_tbSorted, 7, colorOrder);
		} else{
			sort (P_tbSorted, 7, false);
		}

		int afterOrder[7];

		for (int x = 0; x < 7; x ++){
			for (int y = 0; y < 7; y ++){
				if (histogram [x] == tbSorted[y])
					afterOrder[x] = y;
			}
		}

		for (int i = 0; i <7; i++){
			long line = i;
			displayString (line, penColors[afterOrder[i]], tbSorted[i]);
		}

	}

	TButtons a = waitForBtnPress();

	if (a == LEFT_BTN)
		return true;
	else if (a == CENTER_BTN)
		return false;
	else if (a == RIGHT_BTN)
		return displayEndScreen(histogram, colorOrder%3);
	else
		return displayEndScreen (histogram, colorOrder%3);




}

bool feedPencil(int timeout = 5000) {
	clearTimer(T1);
	moveBelt(50);
	// spinWheels(50);
	while (!SensorValue[WHEEL_TOUCH] && time1[T1] < timeout){}
	moveBelt(0);
	// spinWheels(0);
	return time1[T1] < timeout;
}

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
			modeColorFreq = colorType[i];
			modeColor = i;
		}
	}
	return modeColor;
}

#endif
