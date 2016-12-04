/**  ports.c
* store constant value to keep track of sensor indice in the robot</p>
* @author: Eugene Wang, Feilan Jiang, Kenta Morris, Felix Cheng
* @version 1.0
* @since   2016-11-23 */
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
