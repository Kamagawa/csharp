/**  actions.c
 * Contains the action commands of the Csharp program.
 * These functions represent the different tasks performed by the robot
 * such as moving, sharpening, and ejecting pencils as well as moving the tray.
 * It includes the following contents:
 *
 * Enumerated types:
 * Status
 *
 * Functions: 
 * void promptStart() 
 * bool displayEndScreen(int *histogram, int colorOrder) 
 * Status feedPencil(int timeout = 3000)
 * Status sharpenPencil(int sharpenDuration = 3000, int timeout = 5000)
 * Status alignSharpener(int timeout = 7000)
 * Status ejectPencil(int timeout = 5000)
 * Status moveTrayToColor(int color)
 * int getPencilColor(int samplingDuration = 1000) */

#ifndef ACTIONS_C
#define ACTIONS_C

#include "controls.c"
#include "ports.c"
#include "util.c"

typedef enum status_t {
	SUCCESS, JAMMED, TIMED_OUT
} Status;

/** promptStart - written by Feilan Jiang
 * 
 * Prompts user to press the start button, after which the sharpening of pencils will begin. */
void promptStart() {
	displayString(3, "Press centre btn");
	displayString(4, "to start");
	waitForBtnPress (CENTER_BTN);
}

/** displayEndScreen - written by Eugene Wang
 * Displays a inventory list of sharpened pencils which are categorized by colour.
 * Users are able to cycle through the following list sort orders:
 * - Ascending order with respect to pencil count
 * - Descending order with respect to pencil count
 * - Default colour order as defined by RobotC
 * 
 * @param histogram: int array containing the pencil count for each colour category
 * @param colorOrder: identifier for which of the above sort orders to use
 * @return bool: whether or not the program shall continue */
bool displayEndScreen(int *histogram, int colorOrder) {
	// array of colour labels that is parallel to |histogram|
	string penColors[N_BINS] = { "invalid:%8d", "black:  %8d", "blue:   %8d",
			"green:  %8d", "yellow: %8d", "red:    %8d", "white:  %8d" };

	displayString(0, "LQt,CShrp,RSrt");
	if (colorOrder == 0) {
		for (int i = 0; i < N_BINS; i++) {
			displayString(i + 1, penColors[i], histogram[i]);
		}
	} else {
		int tbSorted[N_BINS];
		string colors[N_BINS];
		bool notTaken[N_BINS];

		for (int u = 0; u < N_BINS; u++) {
			tbSorted[u] = histogram[u];
			colors[u] = "";
			notTaken[u] = true;
		}

		if (colorOrder == 1) {
			sort(tbSorted, N_BINS, true);
		} else {
			sort(tbSorted, N_BINS, false);
		}

		// rearrange |penColors| to make it parallel with the newly sorted |histogram|
		for (int x = 0; x < N_BINS; x++) {
			for (int y = 0; y < N_BINS; y++) {
				if (tbSorted[x] == histogram[y] && notTaken[x]) {
					colors[x] = penColors[y];
					notTaken[x] = false;
				}
			}
		}

		// display sorted result
		for (int i = 0; i < N_BINS; i++) {
			displayString(i + 1, colors[i], tbSorted[i]);
		}
	}

	// prompt user for input
	int a = waitForBtnPress();

	// determine the next task based on user input
	if (a == LEFT_BTN) {
		eraseDisplay();
		return true;
	} else if (a == CENTER_BTN) {
		eraseDisplay();
		return false;
	} else if (a == RIGHT_BTN) {
		return displayEndScreen(histogram, (colorOrder + 1) % 3);
	} else {
		return displayEndScreen(histogram, (colorOrder + 1) % 3);
	}
}

/** feedPencil - written by Feilan Jiang
 * This function uses the wheels to feed the pencil into the cartridge exit hole.
 * The function exits when |timeout| is exceeded or when the exit hole touch sensor
 * is pressed, whichever happens first.
 * A |Status| value is returned to indicate the occurrence of errors.
 *
 * @param timeout: duration (in ms) for which the program will attempt to retract the pencil;
 a status of TIMED_OUT will be returned if |timeOut| is exceeded
 * @return Status:
 *     SUCCESS: action completed successfully
 *     JAMMED: pencil jam in cartridge
 *     TIMED_OUT: pencil fell off conveyor belt */
Status feedPencil(int timeout = 3000) {
	// |moveBelt()|: move pencil to wheels
	// |spinWheels()|: move pencil to sharpening-ready position (i.e. right past touch sensor)
	if (moveBelt(50, 500) && spinWheels(50)) {
		// A time variable is used instead of calling |ClearTimer()| because
		// doing so would interfere with other functions also using
		// |T1|. Assigning a different timer to each function was unforunately no
		// an option because it's unknown how many timers are needed at a single 
		// point in time.
		long t = time1[T1];
		while (!SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout) {
		}

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

/** sharpenPencil - written by Feilan Jiang
 * Feed the pencil into the sharpener hole and retract it after |sharpenDuration| is exceeded. 
 * A |Status| value is returned to indicate the occurrence of errors.
 * 
 * @param sharpenDuration: duration (in ms) for which the pencil will be sharpened
 * @param timeout: duration (in ms) for which the program will attempt to retract the pencil;
 a status of |TIMED_OUT| will be returned if |timeOut| is exceeded
 * @return Status:
 *     SUCCESS: action completed successfully
 *     JAMMED: pencil jam at cartridge exit hole
 *     TIMED_OUT: pencil is stuck in sharpener hole */
Status sharpenPencil(int sharpenDuration = 3000, int timeout = 5000) {
	if (spinWheels(50, 1000)) { // push pencil into sharpener hole
		// A time variable is used instead of calling |ClearTimer()| because
		// doing so would interfere with other functions also using
		// |T1|. Assigning a different timer to each function was unforunately no
		// an option because it's unknown how many timers are needed at a single 
		// point in time.
		long t;
		spinWheels(25, sharpenDuration); // wait for pencil to be sharpened

		spinWheels(-50); // retract pencil from sharpener
		t = time1[T1];
		while (SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout) {
		}
		spinWheels(0);

		return (time1[T1] - t < timeout) ? SUCCESS : TIMED_OUT;
	} else {
		return JAMMED;
	}
}

/** alignSharpener - written by Feilan Jiang
 * This function aligns the sharpener with the cartridge exit hole.
 * It is used by the program as a way of "zeroing" the sliding tray mechamism.
 * A |Status| value is returned to indicate the occurrence of errors.
 * 
 * @param travel: indicates the direction in which the tray must travel
 * @param timeout: duration (in ms) for which the program will attempt to retract the pencil;
 a status of |TIMED_OUT| will be returned if |timeOut| is exceeded
 * @return Status:
 *     SUCCESS: action completed successfully
 *     JAMMED: tray motor is jammed
 *     TIMED_OUT: tray derailment */
Status alignSharpener(bool travel = true, int timeout = 3000) { 
	//variable named changed from “dir” to “travel” to improve naming conventions
	if (moveTray(travel ? -25 : 25)) {
		// A time variable is used instead of calling |ClearTimer()| because
		// doing so would interfere with other functions also using
		// |T1|. Assigning a different timer to each function was unforunately no
		// an option because it's unknown how many timers are needed at a single 
		// point in time.
		long t = time1[T1];
		if (travel) {
			while (SensorValue[TRAY_TOUCH] && time1[T1] - t < timeout) {
			}
		} else {
			while (!(SensorValue[TRAY_TOUCH] && time1[T1] - t < timeout)) {
			}
		}

		moveTray(0);
		return (time1[T1] - t < timeout) ? SUCCESS : TIMED_OUT;
	} else {
		return JAMMED;
	}
}

/** ejectPencil - written by Feilan Jiang
 * Ejects the pencil from the cartridge.
 * A |Status| value is returned to indicate the occurrence of errors.
 * 
 * @param timeout: duration (in ms) for which the program will attempt to eject the pencil;
 a status of TIMED_OUT will be returned if |timeOut| is exceeded
 * @return Status:
 *     SUCCESS: action completed successfully
 *     JAMMED: pencil is stuck in cartridge exit hole
 *     TIMED_OUT: pencil is dangling in the exit hole */
Status ejectPencil(int timeout = 5000) {
	if (spinWheels(50)) {
		// A time variable is used instead of calling |ClearTimer()| because
		// doing so would interfere with other functions also using
		// |T1|. Assigning a different timer to each function was unforunately no
		// an option because it's unknown how many timers are needed at a single 
		// point in time.
		long t = time1[T1];
		// pencil begins behind touch sensor
		while (!SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout) {
		}
		// keep pushing until pencil past touch sensor
		while (SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout) {
		}

		// spin wheels for a full revolution to ensure pencil is properly ejected
		nMotorEncoder[WHEEL] = 0;
		while (abs(nMotorEncoder[WHEEL]) < 360 && time1[T1] - t < timeout) {
		}

		spinWheels(0);

		return (time1[T1] - t < timeout) ? SUCCESS : TIMED_OUT;
	} else {
		return JAMMED;
	}
}

/** moveTrayToColor - written by Kenta Morris
 * This function moves the tray to the bin that corresponds to the parameter |color|.
 * This is to ensure that the pencil is dropped in the correct bin.
 * A |Status| value is returned to indicate the occurrence of errors.
 * 
 * @param timeout: duration (in ms) for which the program will attempt to move the tray;
 a status of |TIMED_OUT| will be returned if |timeOut| is exceeded
 * @return Status:
 *     SUCCESS: action completed successfully
 *     JAMMED: tray motor is jammed
 *     TIMED_OUT: tray derailment */
Status moveTrayToColor(int color) {
	Status status = alignSharpener(false);

	if (status == SUCCESS) {
		if (moveTray(25, (color + 1) * BIN_DIST_CM)) {
			return SUCCESS;
		} else {
			return JAMMED;
		}
	}

	return status;
}

/** getPencilColor - written by Kenta Morris 
 * This function determines the pencil's colour by obtaining a large sample of readings
 * and returning the mode colour value.
 *
 * @param samplingDuration: the duration (in ms) for which to obtain colour samples
 * @return int: the mode colour value obtained from the samples */
int getPencilColor(int samplingDuration = 1000) {
	// A time variable is used instead of calling |ClearTimer()| because
	// doing so would interfere with other functions also using
	// |T1|. Assigning a different timer to each function was unforunately no
	// an option because it's unknown how many timers are needed at a single 
	// point in time.
	long t;

	t = time1[T1];
	int colorType[N_BINS] = { 0, 0, 0, 0, 0, 0, 0 };
	while (time1[T1] - t < samplingDuration) { // get average colour seen
		colorType[SensorValue[COLOR]]++;
	}

	int modeColorFreq = 0, modeColor = 0;
	for (int i = 0; i < N_BINS; i++) { // finds colour sensed the most frequently
		if (colorType[i] > modeColorFreq) {
			modeColorFreq = colorType[i];
			modeColor = i;
		}
	}

	return modeColor;
}

#endif
