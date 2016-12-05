/** main.c
 * This is the primary file of the Csharp program. Here, the overall control flow of the
 * program is defined. Each "step" performed by the robot is represented by functions 
 * defined in the file actions.c.
 * 
 * Constants:
 * const int BATTERY_THRESHOLD = 4000;
 * const int TRAY_DIST_CM = 20;
 * const int FAIL_TIMEOUT = 5000;
 * 
 * Tasks:
 * task monitorTray()
 * task sharpenAndSort()
 * task main()
 *
 * @author: Eugene Wang, Feilan Jiang, Kenta Morris, Felix Cheng */

#include "actions.c"
#include "controls.c"
#include "util.c"
#include "ports.c"

const int BATTERY_THRESHOLD = 4000; // mininum battery level (in mV) for runtime operation
const int TRAY_DIST_CM = 20; // distance between each colour bin
const int FAIL_TIMEOUT = 5000; // in a failed state, how long the robot will wait for
			       // user input before continuing

/** monitorTray
 * Check that the pencil tray is not removed during sharpening. If the tray is removed,
 * all other tasks will be stopped until it is restored. */
task monitorTray() {
	while (nAvgBatteryLevel > BATTERY_THRESHOLD)
	{
                // ultrasonic sensor reading will be greater than |TRAY_DIST_CM| when the
                // tray is gone
		if (SensorValue[ULTRA] > TRAY_DIST_CM)
		{
			pauseMotors();
			playSound(soundException);
			displayString(3, "Tray removed!");
			displayString(4, "Put back to resume");
			displayString(5, "sharpening.");

			// stop all other tasks
			hogCPU();
			while (SensorValue[ULTRA] > TRAY_DIST_CM) { }

                        // resume other tasks when the tray is restored
			releaseCPU();
			resumeMotors();
			eraseDisplay();
		}
	}
}
 
/** sharpenAndSort 
 * This task represents the main purpose of the robot. It contains the operation
 * loop that ultimately handles whether the program will sharpen pencils, sort them, 
 * or stop altogether. After all pencils are sorted, the program displays
 * an inventory count of sharpened pencils. From here, the user can choose to quit the
 * program or sharpen more pencils. */
task sharpenAndSort() {
	bool quit = false;
	bool finishedSharpening = false; 
	int color = 0;
	int count[N_BINS] = { 0, 0, 0, 0, 0, 0, 0 }; // histogram of pencil colours
	Status stat; // whether each action function completed successfully

	do {
		while (!finishedSharpening)
		{
			stat = feedPencil();

			if (stat == SUCCESS) {
				color = getPencilColor();
				count[color]++;	

				// a value of 0 represents an invalid colour
				if (color == 0) {
					displayString(0, "Color detection");
					displayString(1, "failed");
					displayString(3, "Placing in");
					displayString(4, "invalid bin");
					displayString(5, "after sharpening");
					wait1Msec(1000);
					eraseDisplay();
				}

                                stat = alignSharpener();
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

                                stat = sharpenPencil();
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

                                stat = moveTrayToColor(color);
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

                                stat = ejectPencil();
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
			} else {
                                // sharpening is complete for the current _batch_ of pencils
				finishedSharpening = true;
			}
		}

		quit = displayEndScreen(count, 0); // display pencil inventory and prompt user to continue or quit the program
	} while (!quit);

	stopAllTasks();
	powerOff();
}

/** main
 * The main task of the program. Sensor initialization and task spawning occur here. */
task main() {
	init();
	promptStart();
	startTask(monitorTray);
	startTask(sharpenAndSort);
	while (nAvgBatteryLevel > BATTERY_THRESHOLD) { }
}
