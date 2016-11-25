/**
* <h1>actions.c</h1>
* <p>The actions.c file is the action component of the Csharp program.
* It contains the handles the action mechanism of the program </p>
*
* <p> The function aims handle the moving pencils, sharpening pencil, 
* ejecting pencils, and moving trays. Essentially, the basic component of
* the machine, it includes these classes, variables, and functions: </p>
*
* <p><b>Includes: 
* #ifndef ACTIONS_C
* #define ACTIONS_C
* 
* #include "controls.c"
* #include "ports.c"
* #include "util.c" 
* </p> 
*
* <p>
* <b>defined Enum:</b>
* {code
* typedef enum status_t { SUCCESS, JAMMED, TIMED_OUT } Status;
* }
* </p>
*
* <p>
* <b>Funcions</b>
* void promptStart() 
* bool displayEndScreen(int *histogram, int colorOrder) 
* Status feedPencil(int timeout = 5000)
* Status sharpenPencil(int sharpenDuration = 3000, int timeout = 5000)
* Status alignSharpener(int timeout = 7000)
* Status ejectPencil(int timeout = 7000)
* Status moveTrayToColor(int color)
* int getPencilColor(int tMs = 1000)
* 
* </p>
*
* <b>Note:</b> The program will only work when all the specified files,
* function, and variable are present in the package
*
* @author
*		theCsharpGroup:
*			Eugene Wang
* 			Feilan Jiang
*			Kenta Morris
*			Felix Cheng
*
* @version 1.0
* @since   2016-11-23
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

	displayString(0, "L Quit C Shrp R Sort");
	if (colorOrder == 0){
		for (int i = 0; i<N_BINS; i++){
			displayString(i + 1, penColors[i], histogram[i]);
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
			displayString (i + 1, penColors[afterOrder[i]], tbSorted[i]);
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
		return displayEndScreen(histogram, colorOrder%3);
	} else {
		return displayEndScreen (histogram, colorOrder%3);
	}
}

// jammed: pencils stuck in cartridge
// times out: no more pencils
Status feedPencil(int timeout = 5000) {
	// |moveBelt()|: get pencil to wheels
	// |spinWheels()|: get pencil into sharpening-ready position (i.e. right past touch sensor)
	if (moveBelt(50, 2000) && spinWheels(50)) {
		long t = time1[T1];
		while (!SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout) { }

		if (time1[T1] - t < timeout) {
			// align pencil body with colour sensor
			return spinWheels(50, 500) ? SUCCESS : JAMMED;
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
		wait1Msec(sharpenDuration);	// wait for pencil to be sharpened

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
Status alignSharpener(int timeout = 7000){
	if (moveTray(50)) {//change as needed
		long t = time1[T1];
		while(!SensorValue[TRAY_TOUCH] && time1[T1] - t < timeout) { }
		moveTray(0);
		return (time1[T1] - t < timeout) ? SUCCESS : TIMED_OUT;
	} else {
		return JAMMED;
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
               if (moveTray(50, (color + 1) * BIN_DIST))
                  return SUCCESS;
               else
                 	return JAMMED;
       }
       return tempStatus;
 }

#endif
