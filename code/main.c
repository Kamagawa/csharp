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
* 		Feilan Jiang
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

const int BATTERY_THRESHOLD = 9000;
const int TRAY_DIST_CM = 30;

// check that the pencil tray is not removed during sharpening
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
		}
	}
}

task sharpenAndSort() {
	bool quit = false;
	bool finishedSharpening = false;

	do {
		while (!finishedSharpening) {
			if (feedPencil()) // pencil found
			{

			}
			else // no pencil / jam
			{

			}
		}
		string histogram[7];
		int *p_histogram = &histogram;

		quit = displayEndScreen(p_histogram, 0);
	} while (!quit);

	stopAllTasks();
}

// display menu dialog to let user pick pencil sorting method before sharpening begins
//task pickSortingMethod() {

//}

task main() {
	promptStart();
	startTask(monitorTray);
	startTask(sharpenAndSort);
}
