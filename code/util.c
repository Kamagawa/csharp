/**
* <h1>util.c</h1>
* <p>The util.c file contains the basic components of the program.
* This includes the sorting algorithm, basic human-mahcine interaction,
* and basic machine oeration components
* </p>
*
* <p> The function aims to stucture the overall organization of the
* robot. the main.c calls the following files and
* contains these variables, and functions: </p>
*
* <p><b>Includes: </b>"action.c", "controls.c", "util.c", "ports.c"</p>
*
* <p>
* <b>constant variables:</b>
* const int BATTERY_THRESHOLD = 9000;
* const int TRAY_DIST_CM = 30;
* </p>
*
* <p>
* <b>Funcions</b>
* monitorTray()
* sharpenAndSort()
* task main()
* </p>
*
* <b>Note:</b> The program will only work when all the specified files,
* function, and variable are present in the package
*
* @author
*		theCsharpGroup:
*			Eugene Wang
* 		Feilan Jiang
*			Kenta Morris
*			Felix Cheng
*
* @version 1.0
* @since   2016-11-23
*/

#ifndef UTIL_C

#define UTIL_C

#define LEFT_BTN 2
#define RIGHT_BTN 1
#define CENTER_BTN 3

void swap(int * const a, int * const b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// insertion sort, chosen for small input size
void sort(int *ar, int len, bool ascending = true) {
	int i, j, k;

	for (i = 1; i < len; i++) {
		k = i;
		for (j = i - 1; j > -1; j--) {
			if (ar[k] >= ar[j] ^ ascending) {
				swap(ar + k, ar + j);
				k--;
			}
		}
	}
}

// Returns the speed in counts per second for the motor specified by |motor|.
// Time interval used in speed calculation specified by |tMs|.
float getSpeed(tMotor motor, int tMs = 50) {
	int d1 = nMotorEncoder[motor];
	wait1Msec(tMs);
	return (nMotorEncoder[motor] - d1) / (float) tMs * 1000;
}

#endif

// Waits for any NXT button to be pressed, then returns that button's number after the button is released.
// If multiple buttons are pressed simultaneously, the function will return the number of the button which
// pressed first.
int waitForBtnPress() {
	int btn;
	while (nNxtButtonPressed == -1){}
		btn = nNxtButtonPressed;
		while (nNxtButtonPressed == btn){}
	return btn;
}

// Waits for a specific NXT button to be pressed, with an option for a timeout if the press never occurs.
// By default, there is no timeout and the function will wait indefinitely for the button to be pressed.
// If this timeout expires, or if there is no timeout, the function will return |true|.
bool waitForBtnPress(int btn, int timeoutMs = -1) {
	bool pressed;

	if (timeoutMs == -1) {
		while (nNxtButtonPressed != btn){}
		while (nNxtButtonPressed == btn){}
		pressed = true;
	} else {
		long t = time1[T1];
		while (nNxtButtonPressed != btn && time1[T1] - t < timeoutMs){}
		while (nNxtButtonPressed == btn && time1[T1] - t < timeoutMs){}
		pressed = time1[T1] - t < timeoutMs;
	}

	return pressed;
}
