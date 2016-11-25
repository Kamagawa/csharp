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
	int color = 0;
	int count[N_BINS] = { 0, 0, 0, 0, 0, 0, 0 };

	do {
		while (feedPencil()) {
			alignSharpener();
			color = getPencilColor();
			count[color]++;
			sharpenPencil();
			// moveTrayToColor(color);
			ejectPencil();
		}

		quit = displayEndScreen(count, 0);
	} while (!quit);

	stopAllTasks();
}

// display menu dialog to let user pick pencil sorting method before sharpening begins
//task pickSortingMethod() {

//}

task main() {
	init();
	promptStart();
	startTask(monitorTray);
	startTask(sharpenAndSort);
}
