/**  main.c
* stucture csharp's program
* 
* constant variables: BATTERY_THRESHOLD, TRAY_DIST_CM *
* Funcions:  monitorTray(), sharpenAndSort(), task main()
*
* @author: Eugene Wang, Feilan Jiang, Kenta Morris, Felix Cheng
* @version 1.2
* @since   2016-11-23 */

#include "actions.c"
#include "controls.c"
#include "util.c"
#include "ports.c"

const int BATTERY_THRESHOLD = 0;	 //battery level for runtime operation
const int TRAY_DIST_CM = 20;  //threshold hole level for normal tray to sensorSonar dist
const int FAIL_TIMEOUT = 5000; // in a failed state, how long robot will wait for
							   // user input before continuing

/**  monitorTray
 * Check that the pencil tray is not removed during sharpening.
 * @return a void ?task? do not return anything.
*/
task monitorTray() {
	while (nAvgBatteryLevel > BATTERY_THRESHOLD) //have battery
	{
		if (SensorValue[ULTRA] > TRAY_DIST_CM) 	//tray out of bound
		{
			pauseMotors();
			playSound(soundException);
			displayString(3, "Tray removed!");
			displayString(4, "Put back to resume");
			displayString(5, "sharpening.");

			// pause all program execution until tray replaced
			hogCPU();
			while (SensorValue[ULTRA] > TRAY_DIST_CM) { } 	//continue action when tray out of bound
			
			//tray within bound: 
			
			releaseCPU();
			resumeMotors();
			eraseDisplay();
		}
	}
}
 
/**  sharpenAndSort 
 * the program is the core of the sharpenning and sorting feature
 * it will handle the operation loop that ultimately handles whether
 * the program will transport the pencil, sort, or stops
 *
 * @return a void task do not return anything. */

task sharpenAndSort() {
	bool quit = false; //user quits
	bool finishedSharpening = false; 
	int color = 0;	//current pencil color
	int count[N_BINS] = { 0, 0, 0, 0, 0, 0, 0 };// color array
	Status stat;	//status or operation

	do {
		while (!finishedSharpening) 	//inoperation
		{
			stat = feedPencil();	//feedpencil

			if (stat == SUCCESS) {
				//detect color, and record
				color = getPencilColor();
				count[color]++;			
				
				//if failed to detect
				if (color == 0) {
					displayString(0, "Color detection");
					displayString(1, "failed");
					displayString(3, "Placing in");
					displayString(4, "invalid bin");
					displayString(5, "after sharpening");
					wait1Msec(1000);
					eraseDisplay();
				}

				do {
					stat = alignSharpener();	//move sharpener in place

					if (stat == JAMMED) {		//if tray jamed
						displayString(0, "Possible jam in");
						displayString(1, "tray motor");
						displayString(3, "Press C to resume");
						displayString(4, "operation");
						waitForBtnPress(CENTER_BTN);
						eraseDisplay();
					} else if (stat == TIMED_OUT) {	//if time out before reach
						displayString(0, "Possible derailment");
						displayString(1, "of tray");
						displayString(3, "Press C to resume");
						displayString(4, "operation");
						waitForBtnPress(CENTER_BTN);
						eraseDisplay();
					}
				} while (stat != SUCCESS);	//continue util success status is reached

				do {
					stat = sharpenPencil();	//sharpen it
					if (stat == JAMMED) {
						displayString(0, "Possible jam in");
						displayString(1, "cartridge");
						displayString(3, "Press C to resume");
						displayString(4, "operation");
						waitForBtnPress(CENTER_BTN);
						eraseDisplay();
					} else if (stat == TIMED_OUT) {
						spinWheels(-100, 4000);

						if (SensorValue[WHEEL_TOUCH]) {
							displayString(0, "Pencil possibly");
							displayString(1, "stuck in");
							displayString(2, "sharpener");
							displayString(4, "Press C to resume");
							displayString(5, "operation");
							waitForBtnPress(CENTER_BTN);
							eraseDisplay();
						}
					}
				} while (stat == JAMMED);

				do {
					stat = moveTrayToColor(color);	//move tray to certain color
					if (stat == JAMMED) {
						displayString(0, "Possible jam in");
						displayString(1, "tray motor");
						displayString(3, "Press C to resume");
						displayString(4, "operation");
						waitForBtnPress(CENTER_BTN);
						eraseDisplay();
					} else if (stat == TIMED_OUT) {
						displayString(0, "Possible derailment");
						displayString(1, "of tray");
						displayString(3, "Press C to resume");
						displayString(4, "operation");
						waitForBtnPress(CENTER_BTN);
						eraseDisplay();
					}
				} while (stat != SUCCESS);

				do {
					stat = ejectPencil();		//eject pencil
					if (stat == JAMMED) {
						displayString(0, "Pencil possibly");
						displayString(1, "stuck in");
						displayString(2, "cartridge");
						displayString(4, "Press C to resume");
						displayString(5, "operation");
						waitForBtnPress(CENTER_BTN);
						eraseDisplay();
					} else if (stat == TIMED_OUT) {
						spinWheels(100, 4000);

						if (SensorValue[WHEEL_TOUCH]) {
							displayString(0, "Pencil possibly");
							displayString(1, "hanging on");
							displayString(2, "cartridge");
							displayString(4, "Press C to resume");
							displayString(5, "operation");
							waitForBtnPress(CENTER_BTN);
							eraseDisplay();
						}
					}
				} while (stat == JAMMED);
			} else {
				finishedSharpening = true;		//finish one round
			}
		}

		quit = displayEndScreen(count, 0); //display result and prompt for continuation or termination
	} while (!quit);

	stopAllTasks();
	powerOff();
}

/** main
 * the main task of the program, where all the higher lever functions
 * were called
 * @return a void task do not return anything. */
task main() {
	init();
	promptStart();
	startTask(monitorTray);
	startTask(sharpenAndSort);
}
