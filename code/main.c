#include "actions.c"
#include "controls.c"
#include "nxtToggleBtn.c"
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

}

// display menu dialog to let user pick pencil sorting method before sharpening begins
task pickSortingMethod() {

}

// display number of pencils of each category after sharpening
// also includes option to sharpen more pencils
task displayInventory() {

}

task main() {

}
