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
	waitForBtnPress(CENTER_BTN);
}

bool displayEndScreen(int *histogram, int colorOrder) {
	string penColors[N_BINS] = {"invalid:%8d" , "black:  %8d", "blue:   %8d",
	"green:  %8d", "yellow: %8d", "red:    %8d", "white:  %8d" };

	displayString(0, "LQt,CShrp,RSrt");
	if (colorOrder == 0){
		for (int i = 0; i<N_BINS; i++){
			displayString(i + 1, penColors[i], histogram[i]);
		}
	}
	else
	{
		int tbSorted [N_BINS];
		string colors[N_BINS];
		bool notTaken[N_BINS];

		for (int u = 0; u < N_BINS ; u ++){
			tbSorted[u] = histogram[u];
			colors[u] = "";
			notTaken[u] = true;
		}

		if (colorOrder == 1){
			sort (tbSorted, N_BINS, true);
		} else{
			sort (tbSorted, N_BINS, false);
		}

		for (int x = 0; x < N_BINS; x ++){
			for (int y = 0; y < N_BINS; y ++){
				if (tbSorted[x] == histogram[y] && notTaken[x]) {
					colors[x] = penColors[y];
					notTaken[x] = false;
				}
			}
		}

		for (int i = 0; i <N_BINS; i++){
			displayString (i + 1, colors[i], tbSorted[i]);
		}

	}

	int a = waitForBtnPress();

	if (a == LEFT_BTN) {
		eraseDisplay();
		return true;
	} else if (a == CENTER_BTN) {
		eraseDisplay();
		return false;
	} else if (a == RIGHT_BTN) {
		return displayEndScreen(histogram, (colorOrder + 1 ) % 3);
	} else {
		return displayEndScreen (histogram, (colorOrder + 1) % 3);
	}
}

// jammed: pencils stuck in cartridge
// times out: no more pencils
Status feedPencil(int timeout = 3000) {
	// |moveBelt()|: get pencil to wheels
	// |spinWheels()|: get pencil into sharpening-ready position (i.e. right past touch sensor)
	if (moveBelt(50, 500) && spinWheels(50)) {
		long t = time1[T1];
		while (!SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout) { }

		if (time1[T1] - t < timeout) {
			// align pencil body with colour sensor
			return spinWheels(50, 150) ? SUCCESS : JAMMED;
		} else {
			spinWheels(0);
			return TIMED_OUT;
		}
	} else {
		return JAMMED;
	}
}

// jammed: jam in cartridge
// time out: pencil stuck in sharpener
Status sharpenPencil(int sharpenDuration = 3000, int timeout = 5000) {
	if (spinWheels(50, 1000)) { // push pencil into sharpener
		long t;
		spinWheels(25, sharpenDuration); // wait for pencil to be sharpened

		spinWheels(-50); // retract pencil from sharpener
		t = time1[T1];
		while (SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout) { }
		spinWheels(0);

		return (time1[T1] - t < timeout) ? SUCCESS : TIMED_OUT;
	} else {
		return JAMMED;
	}
}

// jammed: object in way
// time out: derailed tray
Status alignSharpener(bool dir = true, int timeout = 3000){
	if (moveTray(dir ? -25 : 25)) {
		long t = time1[T1];
		if (dir) 
			while(SensorValue[TRAY_TOUCH] && time1[T1] - t < timeout) { }
		else
			while(!(SensorValue[TRAY_TOUCH] && time1[T1] - t < timeout)) { }
		moveTray(0);
		return (time1[T1] - t < timeout) ? SUCCESS : TIMED_OUT;
	} else {
		return JAMMED;
	}
}

// jammed: pencil stuck
// time out: pencil hanging
Status ejectPencil(int timeout = 5000){
	if (spinWheels(100)){
		long t = time1[T1];
		// pencil begins behind touch sensor
		while(!SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout ){}
		// keep pushing till pencil past touch sensor
		while(SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout){}
		// push for an additional number of encoder counts in order to eject pencil
		nMotorEncoder[WHEEL] = 0;
		while(abs(nMotorEncoder[WHEEL]) < 360 && time1[T1] - t < timeout){}//change as needed

		spinWheels(0);

		return (time1[T1] - t < timeout)? SUCCESS : TIMED_OUT;
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
       Status tempStatus = alignSharpener(false);
       if (tempStatus == SUCCESS){
               if (moveTray(25, (color + 1) * BIN_DIST_CM))
                  return SUCCESS;
               else
                 	return JAMMED;
       }
       return tempStatus;
 }

#endif
