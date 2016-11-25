#include "actions.c"
#include "controls.c"
#include "util.c"
#include "ports.c"

const int BATTERY_THRESHOLD = 9000;
const int TRAY_DIST_CM = 30;

// check that the pencil tray is not removed during sharpening
task monitorTray() {
	while (nAvgBatteryLevel < BATTERY_THRESHOLD) {
		if (SensorValue[ULTRA] > TRAY_DIST_CM) {
			// tray lifted during sharpening
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
