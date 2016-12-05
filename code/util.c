/** util.c
 * This file contains miscellaneous utility functions used elsewhere in the program. 
 *
 * Defined BTN buttons:
 * LEFT_BTN 2
 * RIGHT_BTN 1
 * CENTER_BTN 3
 *
 * Functions: 
 * void swap(int * const a, int * const b)
 * void sort(int *ar, int len, bool ascending = true)
 * float getSpeed(tMotor motor, int tMs = 50)
 * int waitForBtnPress()
 * bool waitForBtnPress(int btn, int timeoutMs = -1)
 * monitorTray()
 * sharpenAndSort()
 * task main() */

#ifndef UTIL_C
#define UTIL_C

const int LEFT_BTN = 2;
const int RIGHT_BTN = 1;
const int CENTER_BTN = 3;

/** swap
 * Switches the values of two integers. Used extensively by |sort()|.
 *
 * @param a: first integer 
 * @param b: second integer  */
void swap(int * const a, int * const b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

/** sort
 * Sorts an array of integers in ascending or desending order. Insertion sort was chosen
 * because of its simplicity and good performance for small input sizes.
 *
 * @param ar: integer array to be sorted
 * @param len: number of elements in the array
 * @param ascending: sorts in ascending order if |true| */
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

/** getSpeed
 * Returns the speed in counts per second for the motor specified by |motor|.
 * Time interval used in speed calculation specified by |tMs|.
 *
 * @param motor: the motor whose speed is to be calculated
 * @param tMs: the time interval used for speed calculation
 * @return float: motor speed in counts/second */
float getSpeed(tMotor motor, int tMs = 50) {
	int d1 = nMotorEncoder[motor];
	wait1Msec(tMs);
	return (nMotorEncoder[motor] - d1) / (float) tMs * 1000;
}

/** waitForBtnPress
 * Waits for any NXT button to be pressed, then returns that button's number after the button is released.
 * If multiple buttons are pressed simultaneously, the function will return the number of
 * the button which was pressed first.
 *
 * @return int: the pressed button's index */
int waitForBtnPress() {
	int btn;

	while (nNxtButtonPressed == -1) {
	}
	btn = nNxtButtonPressed;
	while (nNxtButtonPressed == btn) {
	}

	return btn;
}

/** waitForBtnPress
 * Waits for a specific NXT button to be pressed, with an option for a timeout if the press never occurs.
 * By default, there is no timeout and the function will wait indefinitely for the button to be pressed.
 * If this timeout expires, or if there is no timeout, the function will return |true|.
 *
 * @return bool: |true| if the button wasn't pressed before the timeout */
bool waitForBtnPress(int btn, int timeoutMs = -1) {
	bool pressed;

	if (timeoutMs == -1) {
		while (nNxtButtonPressed != btn) {
		}
		while (nNxtButtonPressed == btn) {
		}
		pressed = true;
	} else {
		long t = time1[T1];
		while (nNxtButtonPressed != btn && time1[T1] - t < timeoutMs) {
		}
		while (nNxtButtonPressed == btn && time1[T1] - t < timeoutMs) {
		}
		pressed = time1[T1] - t < timeoutMs;
	}

	return pressed;
}

#endif
