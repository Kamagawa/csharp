/** controls.c 
* handles the control calls and responds within the program
*
* const:   DIAM_CM, CIRCUM_CM, ENC_TOL, N_BINS, BIN_DIST_CM
* Funcions: monitorTray(), sharpenAndSort(), task main()
*
* @author: Eugene Wang, Feilan Jiang, Kenta Morris, Felix Cheng
* @version 1.2
* @since   2016-11-23  */

#ifndef CONTROLS_C
#define CONTROLS_C

#include "ports.c"
#include "util.c"

const float DIAM_CM = 3.7;
const float CIRCUM_CM = DIAM_CM * PI;
const int ENC_TOL = 1;
const int N_BINS = 7;
const float BIN_DIST_CM = 1;
const int JAM_THRESHOLD = 100;

static int motorCache[3] = { 0, 0, 0 };

/**  init
 * the init function initiates the sensor values, and set
 * the correct ports to sensor, hence starting the function
 * of the program and will be called by taks main ();   */
void init() {
	SensorType[WHEEL_TOUCH] = sensorTouch;
	SensorType[COLOR] = sensorColorNxtFULL;
	SensorType[ULTRA] = sensorSONAR;
	SensorType[TRAY_TOUCH] = sensorTouch;
}

/**  moveBelt 
 * moves the belt with the givern power and time tMs, if not specified it will keep
 * moving at setted power. This is to send the pencils to the feeder.
 *
 * @param power thePower of motor moving the belt
 * @param tMs the time length in milisenconds that the belt will move
 * @return a bool that indicates if task has been done    */
bool moveBelt(int power, int tMs = -1) {
	bool success;

	motor[BELT] = power;
	success = power != 0 || getSpeed(BELT, 10) < JAM_THRESHOLD;

	if (tMs > -1 && success) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) { }
		motor[BELT] = 0;
	} else if (!success) {
		motor[BELT] = 0;
	}
	return success;
}


/**  spinWheels
 * The spinWheels function spins the wheel with MotorPower power
 * and the amout of time tMs, if not specified it will keep
 * moving at setted power. This is to feed the pencil to the pencil sharpener
 *
 * @param power thePower of motor moving the belt
 * @param tMs the time length in milisenconds that the belt will move
 * @return a bool to indicate if task has been done  */
bool spinWheels (int power, int tMs = -1){
	bool success;
	motor[WHEEL] = -power;
	success = power != 0 || getSpeed(BELT, 10) < JAM_THRESHOLD;

	if (tMs > -1 && success) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) { }
		motor[WHEEL] = 0;
	} else if (!success) {
		motor[WHEEL] = 0;
	}
	return success;
}

/**  moveTray
 * The moveTray function moves the tray with MotorPower power
 * and the distance in distCm which will be coverted into timing
 * for robot to calculate.
 * This is to feed the pencil to the pencil sharpener
 *
 * @param power thePower of motor moving the belt
 * @param distCm the time length in milisenconds that the belt will move
 * @return a bool that indicates if task has been done.  */
bool moveTray (int power, float distCm = 0)
{
	bool success;
	motor[TRAY] = -power;
//	success = power != 0 || getSpeed(BELT, 10) < JAM_THRESHOLD;
//	if (distCm > 0 && success) {
		int encVal = distCm / CIRCUM_CM * 360;
		nMotorEncoder[TRAY] = 0;
//		nMotorEncoderTarget[TRAY] = encVal;
		while(abs(nMotorEncoder[TRAY]) < encVal) { }
		motor[TRAY] = 0;
//	} else if (!success) {
//		motor[TRAY] = 0;
//	}
	return true;
}

//pause the motor
void pauseMotors() {
	motorCache[0] = motor[BELT];
	motorCache[1] = motor[WHEEL];
	motorCache[2] = motor[TRAY];
	motor[BELT] = motor[WHEEL] = motor[TRAY] = 0;
}

//resume the motor
void resumeMotors() {
	motor[BELT] = motorCache[0];
	motor[WHEEL] = motorCache[1];
	motor[TRAY] = motorCache[2];
}
#endif
