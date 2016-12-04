/**  actions.c
* contains the action command of the Csharp program.
* handle the moving pencils, sharpening pencil, 
* ejecting pencils, and moving trays. Essentially, the basic component of
* the machine, it includes these classes, variables, and functions: </p>
*
* defined Enum "status"
*
* Declared follow functions: 
* void promptStart() 
* bool displayEndScreen(int *histogram, int colorOrder) 
* Status feedPencil(int timeout = 5000)
* Status sharpenPencil(int sharpenDuration = 3000, int timeout = 5000)
* Status alignSharpener(int timeout = 7000)
* Status ejectPencil(int timeout = 7000)
* Status moveTrayToColor(int color)
* int getPencilColor(int tMs = 1000)
* 
* <b>Note:</b> The program will only work when all the specified files,
* function, and variable are present in the package
*
* @author: Euene Wang, Feilan Jiang, Kenta Morris, Felix Cheng
* @version 1.2
* @since   2016-11-23   */

#ifndef ACTIONS_C
#define ACTIONS_C

#include "controls.c"
#include "ports.c"
#include "util.c"

//enum status for functions to return starts datatype
typedef enum status_t { SUCCESS, JAMMED, TIMED_OUT } Status; 


/**  monitorTray
 * display strings, and wait for user button press to start
 * the program  */
void promptStart() {
	displayString(3, "Press centre btn");
	displayString(4, "to start");
	waitForBtnPress(CENTER_BTN);
}

/**  displayEndScreen
 * It handles the display of sorted contain in the program
 * first it display a list of sorted pencil depending on users' requirement, 
 * sort the pencils in different ways: assending, desecnding, and by color index
 * 
 * @param histogram int array pointer for the array to be sorted
 * @param colorOrder for the order of which the pencil will be sorted 
 * @return bool: whether or not the programme shall continue  */
bool displayEndScreen(int *histogram, int colorOrder) {
	//color array
	string penColors[N_BINS] = {"invalid:%8d" , "black:  %8d", "blue:   %8d",
	"green:  %8d", "yellow: %8d", "red:    %8d", "white:  %8d" };
	
	//display first sorted list
	displayString(0, "LQt,CShrp,RSrt");
	if (colorOrder == 0){
		for (int i = 0; i<N_BINS; i++){
			displayString(i + 1, penColors[i], histogram[i]);
		}
	}
	else		//switch to other options based on users' spec
	{
		int tbSorted [N_BINS];
		string colors[N_BINS];
		bool notTaken[N_BINS];

		for (int u = 0; u < N_BINS ; u ++){
			tbSorted[u] = histogram[u];
			colors[u] = "";
			notTaken[u] = true;
		}

		if (colorOrder == 1){
			sort (tbSorted, N_BINS, true);
		} else{
			sort (tbSorted, N_BINS, false);
		}

		for (int x = 0; x < N_BINS; x ++){
			for (int y = 0; y < N_BINS; y ++){
				if (tbSorted[x] == histogram[y] && notTaken[x]) {
					colors[x] = penColors[y];
					notTaken[x] = false;
				}
			}
		}
		
		//display sorted result
		for (int i = 0; i <N_BINS; i++){
			displayString (i + 1, colors[i], tbSorted[i]);
		}
	}

	//prompt user for input after each sort
	int a = waitForBtnPress();

	//decide the next task based on user input
	if (a == LEFT_BTN) {
		eraseDisplay();
		return true;
	} else if (a == CENTER_BTN) {
		eraseDisplay();
		return false;
	} else if (a == RIGHT_BTN) {
		return displayEndScreen(histogram, (colorOrder + 1 ) % 3);
	} else {
		return displayEndScreen (histogram, (colorOrder + 1) % 3);
	}
}

/**  feedPencil
 * this function handls spinning wheels to feed the pencil into the sharpener
 * it takes in a parameter times out to determine whether there are more pencils
 * left in the bin
 * 
 * @param timesout: no more pencils
 * @return jammed: pencils stuck in cartridge   */
Status feedPencil(int timeout = 3000) 
{
	// |moveBelt()|: get pencil to wheels
	// |spinWheels()|: get pencil into sharpening-ready position (i.e. right past touch sensor)
	if (moveBelt(50, 500) && spinWheels(50)) {
		long t = time1[T1];
		while (!SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout) { }

		if (time1[T1] - t < timeout) {
			// align pencil body with colour sensor
			return spinWheels(50, 150) ? SUCCESS : JAMMED;
		} else {
			spinWheels(0);
			return TIMED_OUT;
		}
	} else {
		return JAMMED;
	}
}


/**  sharpenPencil
 * spin the wheels to push the pencils into the sharpener and retract it after it is finished.
 * 
 * @param timesout: time until it returns a timeOut status
 * @param sharpenPencil: duration for shapening the pencil
 * @return status
 *		JAMMED: pencils stuck in cartridge
 *		TIMED_OUT: pencils stuck in sharpener
 *		SUCCESS: task completed                 */
Status sharpenPencil(int sharpenDuration = 3000, int timeout = 5000) {
	if (spinWheels(50, 1000)) { // push pencil into sharpener
		long t;
		spinWheels(25, sharpenDuration); // wait for pencil to be sharpened

		spinWheels(-50); // retract pencil from sharpener
		t = time1[T1];
		while (SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout) { }
		spinWheels(0);

		return (time1[T1] - t < timeout) ? SUCCESS : TIMED_OUT;
	} else {
		return JAMMED;
	}
}

/**  alignSharpener
 * This function aligns the sharpener to the slider and feeder port
 * essentially after the tray was moved to a set location for dropping
 * the pencil, this function resets the tray and sharpener to its 
 * initial position
 * 
 * @param timesout: time until it returns a timeOut status
 * @return status
 *		JAMMED: object in way
 *		TIMED_OUT: derailed tray 	*/
Status alignSharpener(bool dir = true, int timeout = 3000){
	if (moveTray(dir ? -25 : 25)) {
		long t = time1[T1];
		if (dir) 
			while(SensorValue[TRAY_TOUCH] && time1[T1] - t < timeout) { }
		else
			while(!(SensorValue[TRAY_TOUCH] && time1[T1] - t < timeout)) { }
		moveTray(0);
		return (time1[T1] - t < timeout) ? SUCCESS : TIMED_OUT;
	} else {
		return JAMMED;
	}
}

/**  ejectPencil
 * ejects the pencil from the feeder and check for environmental status
 * 
 * @param timesout: time until it returns a timeOut status
 * @return status
 *		JAMMED: pencil stuck in feeder
 *		TIMED_OUT: pencil hanging      */
Status ejectPencil(int timeout = 5000){
	if (spinWheels(50)){
		long t = time1[T1];
		// pencil begins behind touch sensor
		while(!SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout ){}
		// keep pushing till pencil past touch sensor
		while(SensorValue[WHEEL_TOUCH] && time1[T1] - t < timeout){}
		// push for an additional number of encoder counts in order to eject pencil
		nMotorEncoder[WHEEL] = 0;
		while(abs(nMotorEncoder[WHEEL]) < 360 && time1[T1] - t < timeout){}//change as needed

		spinWheels(0);

		return (time1[T1] - t < timeout)? SUCCESS : TIMED_OUT;
	} else {
		return JAMMED;
	}
}

/**  getPencilColor
 * This function detect pencils ambiant color, calculate pencils' 
 * average color and then returns it as the pencils' color
 * 
 * @param timesout: time until it returns a timeOut status
 * @return color index ( 0 == invalid color)  */
int getPencilColor(int tMs = 1000) {
	long t;

	t = time1[T1];
	int colorType[N_BINS] = { 0, 0, 0, 0, 0, 0, 0 };
	while(time1[T1] - t < tMs){//get average colour seen
		colorType[SensorValue[COLOR]]++;
	}

	int modeColorFreq = 0, modeColor = 0;
	for (int i = 0; i < N_BINS; i++){//finds colour sensed the most frequently
		if (colorType[i] > modeColorFreq){
			modeColorFreq = colorType[i];
			modeColor = i;
		}
	}

	return modeColor;
}

/**  moveTrayToColor
 * This function moves the tray to a certain color at int color.
 * it allows the pencil to be dropped to the correct location
 * and return runtime status for error handling on a higher level
 * 
 * @param timesout: time until it returns a timeOut status
 * @return status
 *		JAMMED: object in way
 *		TIMED_OUT: derailed tray
*/
Status moveTrayToColor(int color) {
       Status tempStatus = alignSharpener(false);
       if (tempStatus == SUCCESS){
               if (moveTray(25, (color + 1) * BIN_DIST_CM))
                  return SUCCESS;
               else
                 	return JAMMED;
       }
       return tempStatus;
 }
#endif
