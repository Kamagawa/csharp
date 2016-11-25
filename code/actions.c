/**
*
*/
#ifndef ACTIONS_C
#define ACTIONS_C

#include "controls.c"
#include "ports.c"
#include "util.c"

typedef enum status_t { SUCCESS, JAMMED, TIMED_OUT } Status;

void promptStart() {
	displayString(3, "Press centre btn");
	displayString(4, "to start");
	waitForBtnPress(3);
}

bool displayEndScreen(int *histogram, int colorOrder) {
	string penColors[N_BINS] = {"invalid", "black: %d", "blue: %d",
	"green: %d", "yellow: %d", "red: %d", "white: %d", };

	displayString(0, "Pencil inventory:");
	if (colorOrder == 0){
		for (int i = 0; i<N_BINS; i++){
			displayString(i, penColors[i], histogram[i]);
		}
	}
	else
	{
		int tbSorted [N_BINS];
		int *P_tbSorted = &tbSorted;

		for (int u = 0; u < N_BINS ; u ++){
			tbSorted[u] = histogram[u];
		}

		if (colorOrder == 1){
			sort (P_tbSorted, N_BINS, colorOrder);
		} else{
			sort (P_tbSorted, N_BINS, false);
		}

		int afterOrder[N_BINS];

		for (int x = 0; x < N_BINS; x ++){
			for (int y = 0; y < N_BINS; y ++){
				if (histogram [x] == tbSorted[y])
					afterOrder[x] = y;
			}
		}

		for (int i = 0; i <N_BINS; i++){
			long line = i;
			displayString (line, penColors[afterOrder[i]], tbSorted[i]);
		}

	}

	int a = waitForBtnPress();

	if (a == LEFT_BTN)
		return true;
	else if (a == CENTER_BTN)
		return false;
	else if (a == RIGHT_BTN)
		return displayEndScreen(histogram, colorOrder%3);
	else
		return displayEndScreen (histogram, colorOrder%3);
}

// jammed: pencils stuck in cartridge
// times out: pencil fallen off belt
bool feedPencil(int timeout = 5000) {
	long t;

	// get pencil to wheels
	moveBelt(50, 2000);

	// get pencil into sharpening-ready position (i.e. right past touch sensor)
	spinWheels(50);
	t = time1[T1];
	while (!SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout) { }

	if (time1[T1] - t < timeout) {
		spinWheels(50, 500);
		return true;
	} else {
		return false;
	}
}

// jammed: jam in cartridge
// time out: pencil stuck in sharpener
bool sharpenPencil(int tMs = 3000) {
	long t;

	// push pencil into sharpener, then wait for |tMs| milliseconds
	spinWheels(50, 1000);
	spinWheels(0, tMs);

	// retract pencil from sharpener
	spinWheels(-50);
	t = time1[T1];
	while (SensorValue[WHEEL_TOUCH] && time1[T1] - t < tMs) { }
	spinWheels(0);

	return time1[T1] - t < tMs;
}

// jammed: object in way
// time out: derailed tray
bool alignSharpener(){
	if (moveTray(50)) {//change as needed
		while(!SensorValue[TRAY_TOUCH]) { }
		moveTray(0);
		return true;
	} else {
		return false;
	}
}

// jammed: pencil stuck
// time out: pencil hanging
Status ejectPencil(int timeout = 7000){
	if (spinWheels(50)){
		long t = time1[T1];
		// pencil begins behind touch sensor
		while(!SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout ){}
		// keep pushing till pencil past touch sensor
		while(SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout){}
		// push for an additional number of encoder counts in order to eject pencil
		nMotorEncoder[WHEEL] = 0;
		while(nMotorEncoder[WHEEL] < 500 && time1[T1] - t < timeout){}//change as needed

		spinWheels(0);

		return (time1[T1] - t > timeout)? SUCCESS : TIMED_OUT;
	} else {
		return JAMMED;
	}
}

// 0: invalid color
int getPencilColor(int tMs = 1000) {
	long t;

	t = time1[T1];
	int colorType[N_BINS] = { 0, 0, 0, 0, 0, 0, 0 };
	while(time1[T1] - t < tMs){//get average colour seen
		colorType[SensorValue[COLOR]]++;
	}

	int modeColorFreq = 0, modeColor = 0;
	for (int i = 0; i < N_BINS; i++){//finds colour sensed the most frequently
		if (colorType[i] > modeColorFreq){
			modeColorFreq = colorType[i];
			modeColor = i;
		}
	}

	return modeColor;
}

// jammed: object in way
// time out: derailed tray

Status moveTrayToColor(int color) {
       Status tempStatus = alignSharpener();
       if (tempStatus == SUCCESS){
               if ( moveTray(-50, (color + 1) * BIN_DIST))
                  return SUCCESS;
               else
                 	return JAMMED;
       }
       return tempStatus;
 }

#endif
