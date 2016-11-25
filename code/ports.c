/**
* <h1>ports.c</h1>
* <p>The main.c file is a constant value storage file that is
* used to keep track of sensor indexes in the robot</p>
*
* <p> The function aims to stucture the overall organization of the
* robot. the main.c calls the following files and
* contains these variables, and functions: </p>
*
* <p><b>Defines: </b>PORTS_C</p>
*
* <p>
* <b>constant variables:</b>
* { code
* const tMotor WHEEL = motorA;
* const tMotor TRAY = motorB;
* const tMotor BELT = motorC;

* const tSensors WHEEL_TOUCH = S1;
* const tSensors TRAY_TOUCH = S2;
* const tSensors ULTRA = S3;
* const tSensors COLOR = S4;
* } </p>
*
*
* <b>Note:</b> The program will define the sensors in main
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


#ifndef PORTS_C
#define PORTS_C

const tMotor WHEEL = motorA;
const tMotor TRAY = motorB;
const tMotor BELT = motorC;

const tSensors WHEEL_TOUCH = S1;
const tSensors TRAY_TOUCH = S2;
const tSensors ULTRA = S3;
const tSensors COLOR = S4;

#endif
