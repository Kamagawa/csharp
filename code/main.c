/**
* <h1>Main.C</h1>
* <p>The main.c file is the component of the Csharp program.
* It contains the task main, which is where the programme
* will be called by LEGO NXT robot. </p>
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
* 			Feilan Jiang
*			Kenta Morris
*			Felix Cheng
*
* @version 1.0
* @since   2016-11-23
*/

#include "actions.c"
#include "controls.c"
#include "util.c"
#include "ports.c"

const int BATTERY_THRESHOLD = 9000;	 //battery level for runtime operation
const int TRAY_DIST_CM = 30;  //threshold hole level for normal tray to sensorSonar dist


/**
 * monitorTray
 * {code  task monitorTray(); }
 *
 * Description:
 * Check that the pencil tray is not removed during sharpening.
 *
 * Note:
 * This is a higer-levl modular function, that facilitate the
 * system operation, thus it requires little var from outside
 * environment as it has been handled in lower-level functions
 *
 * @return a void ‘task’ do not return anything.
*/
task monitorTray() {
	while (nAvgBatteryLevel > BATTERY_THRESHOLD) {
		if (SensorValue[ULTRA] > TRAY_DIST_CM) {
			playSound(soundException);
			displayString(3, "Tray removed!");
			displayString(4, "Put back to resume");
			displayString(5, "sharpening.");

			// pause all program execution until tray replaced
			hogCPU();
			while (SensorValue[ULTRA] > TRAY_DIST_CM) { }
			releaseCPU();

			eraseDisplay();
		}
	}
}


/**
 * sharpenAndSort
 * {code  task sharpenAndSort(); }
 *
 * Description:
 * the program is the core of the sharpenning and sorting feature
 * it will handle the operation loop that ultimately handles whether
 * the program will transport the pencil, sort, or stops
 *
 * Note:
 * This is a higer-levl modular function, that facilitate the
 * system operation, thus it requires little var from outside
 * environment as it has been handled in lower-level functions
 *
 * @return a void task do not return anything.
*/

task sharpenAndSort() {
	bool quit = false;
	bool finishedSharpening = false;
	int color = 0;
	int count[N_BINS] = { 0, 0, 0, 0, 0, 0, 0 };
	Status stat;

	do {
		while (!finishedSharpening) {
			stat = feedPencil();

			if (stat != TIMED_OUT) {
				color = getPencilColor();
				count[color]++;
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
				} while (stat != SUCCESS);

				do {
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
				} while (stat == JAMMED);

				do {
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
				} while (stat != SUCCESS);

				do {
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
				} while (stat == JAMMED);
			} else {
				finishedSharpening = true;
			}
		}

		quit = displayEndScreen(count, 0);
	} while (!quit);

	stopAllTasks();
}

/**
 * main
 * {code  task main(); }
 *
 * Description:
 * the main task of the program, where all the higher lever functions
 * were called
 *
 * Note:
 * This is a higer-levl modular function, that facilitate the
 * system operation, thus it requires little var from outside
 * environment as it has been handled in lower-level functions
 *
 * @return a void task do not return anything.
*/
task main() {
	init();
	promptStart();
	startTask(monitorTray);
	startTask(sharpenAndSort);
}
