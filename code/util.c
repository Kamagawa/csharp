/**  util.c
* contains sorting algorithm and basic human-mahcine interaction
*
* Defined BTN buttons: <
* LEFT_BTN 2
* RIGHT_BTN 1
* CENTER_BTN 3
*
* Funcions: 
* monitorTray()
* sharpenAndSort()
* task main()
* 
* @author: Eugene Wang, Feilan Jiang, Kenta Morris, Felix Cheng
* @version 1.0
* @since   2016-11-23 */

//start of preprocessor directives
#ifndef UTIL_C
#define UTIL_C

#define LEFT_BTN 2
#define RIGHT_BTN 1
#define CENTER_BTN 3


/**  swap
 * takes in the pointer of two integers and swtich their value.
 *
 * @param a: constant integer pointer a that will be swapped with b
 * @param a: constant integer pointer b that will be swapped with a  */
void swap(int * const a, int * const b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


/**  sort
 * the sort function takes in an integer array from defined size,
 * and sort it either in ascending or descending order depending
 * on user's specification.
 *
 * @param *ar: integer array pointer for the array to be sorted
 * @param len: integer length
 * @param ascending: boolean to determine the way of sorting
 *	  by defualt it is sorted to true (assending)
 * @return a void function
*/

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


/**
 * getSpeed
 * Returns the speed in counts per second for the motor specified by |motor|.
 * Time interval used in speed calculation specified by |tMs|.
 *
 * @param motor: parse motor for motorEncoder to detect counts
 * @param tMs: the interval of wait for speed measuring
 * @return (float) speed of vehicle in counts / specified interval
 *			in counts / second * specified interval */
float getSpeed(tMotor motor, int tMs = 50) {
	int d1 = nMotorEncoder[motor];
	wait1Msec(tMs);
	return (nMotorEncoder[motor] - d1) / (float) tMs * 1000;
}

#endif
//end the preprocessor directives



/**  waitForBtnPress
 * Waits for any NXT button to be pressed, then returns that button's number after the button is released.
 * If multiple buttons are pressed simultaneously, the function will return the number of the button which
 * pressed first.
 *
 * @return BTN the pressed button index */
int waitForBtnPress() {
	int btn;
	while (nNxtButtonPressed == -1){}
		btn = nNxtButtonPressed;
		while (nNxtButtonPressed == btn){}
	return btn;
}

/**  waitForBtnPress
 * Waits for a specific NXT button to be pressed, with an option for a timeout if the press never occurs.
 * By default, there is no timeout and the function will wait indefinitely for the button to be pressed.
 * If this timeout expires, or if there is no timeout, the function will return |true|.
 *
 * @return BTN the pressed button index */
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
