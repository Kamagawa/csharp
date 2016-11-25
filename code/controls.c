/**
* <h1>controls.c</h1>
* <p>The controls.c file is the control component of the Csharp program.
* It contains the handles the control mechanism of the program </p>
*
* <p> The function aims handle the control calls and responds within
* the following files and contains these variables, and functions: </p>
*
* <p><b>Includes: </b>ports.c</p>
*
* <p>
* <b>constant variables:</b>
* {code
* const float DIAM_CM = 3.7;
* const float CIRCUM_CM = DIAM_CM * PI;
* const int ENC_TOL = 1
* const int N_BINS = 7;
* const int BIN_DIST = 0;
* }
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

//define CONTROLS_C
#ifndef CONTROLS_C
#define CONTROLS_C

//include ports.c file
#include "ports.c"

//define constants
const float DIAM_CM = 3.7;
const float CIRCUM_CM = DIAM_CM * PI;
const int ENC_TOL = 1
const int N_BINS = 7;
const int BIN_DIST = 0;


/**
 * init
 * {code  void init(); }
 *
 * Description:
 * the init function initiates the sensor values, and set
 * the correct ports to sensor, hence starting the function
 * of the program and will be called by taks main ();
 *
 * Note:
 * This is a mid-levl modular function, that facilitate the
 * system operation, thus it requires little var from outside
 * environment as it has been handled in lower-level functions
 *
 * @return a void task do not return anything.
*/
void init() {
	SensorType[WHEEL_TOUCH] = sensorTouch;
	SensorType[COLOR] = sensorColorNxtFULL;
	SensorType[ULTRA] = sensorSONAR;
	SensorType[TRAY_TOUCH] = sensorTouch;
}


/**
 * moveBelt
 * {code  moveBelt(100, 50); }
 *
 * Description:
 * The move belt function moves the belt with MotorPower power
 * and the amout of time tMs, if not specified it will keep
 * moving at setted power.
 * This is to send the pencils to the feeder.
 *
 * @param power thePower of motor moving the belt
 * @param tMs the time length in milisenconds that the belt will move
 *
 * Note:
 * This is a low-levl modular function, that facilitate the
 * system operation, thus it requires little var from outside
 * environment as it has been handled in lower-level functions
 *
 * @return a void task do not return anything.
*/
void moveBelt(int power, int tMs = -1) {
	motor[BELT] = power;

	if (tMs > -1) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) { }
		motor[BELT] = 0;
	}
}


/**
 * spinWheels
 * {code  spinWheels(100, 50); }
 *
 * Description:
 * The spinWheels function spins the wheel with MotorPower power
 * and the amout of time tMs, if not specified it will keep
 * moving at setted power.
 * This is to feed the pencil to the pencil sharpener
 *
 * @param power thePower of motor moving the belt
 * @param tMs the time length in milisenconds that the belt will move
 *
 * Note:
 * This is a low-levl modular function, that facilitate the
 * system operation, thus it requires little var from outside
 * environment as it has been handled in lower-level functions
 *
 * @return a void task do not return anything.
*/
void spinWheels (int power, int tMs = -1)
{
	motor[WHEEL] = power;

	if (tMs > -1) {
		long t = time1[T1];
		while (time1[T1] - t < tMs) { }
		motor[WHEEL] = 0;
	}
}


/**
 * moveTray
 * {code  moveTray(100, 500.21); }
 *
 * Description:
 * The moveTray function moves the tray with MotorPower power
 * and the distance in distCm which will be coverted into timing
 * for robot to calculate.
 * This is to feed the pencil to the pencil sharpener
 *
 * @param power thePower of motor moving the belt
 * @param distCm the time length in milisenconds that the belt will move
 *
 * Note:
 * This is a low-levl modular function, that facilitate the
 * system operation, thus it requires little var from outside
 * environment as it has been handled in lower-level functions
 *
 * @return a void task do not return anything.
*/
void moveTray (int power, float distCm)
{
	int encVal = distCm / CIRCUM_CM * 360;
	nMotorEncoder[TRAY] = 0;

	motor[TRAY] = power;
	nMotorEncoderTarget[TRAY] = encVal;
	while(nMotorRunState[TRAY] != runStateIdle) { }
	motor[TRAY] = 0;
}

#endif
