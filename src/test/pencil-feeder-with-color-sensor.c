#define TOUCH S1
#define COLOR S2

#define BELT motorA
#define WHEEL motorB

float getSpeed(tMotor motor, int tMs = 50) {
	int d1 = nMotorEncoder[motor];
	wait1Msec(tMs);
	return (nMotorEncoder[motor] - d1) / (float) tMs * 1000;
}

task main()
{
	bool btnDown[2] = {false, false};
	int motorPresets[4] = {25, 50, 75, 100};
	int i = 0;

	bool touch = false;
	string color = "";

	SensorType[TOUCH] = sensorTouch;
	SensorType[COLOR] = sensorColorNxtFULL;

	while (true) {
		btnDown[0] = btnDown[1];
		btnDown[1] = nNxtButtonPressed == 3;

		// toggle speed preset
		if (btnDown[0] && !btnDown[1]) {	// button released
			i = ++i % 4;
		}

		// motor forward, backward, or off
		if (nNxtButtonPressed == 1) {
			motor[WHEEL] = motorPresets[i];
			motor[BELT] = -motorPresets[i];
		} else if (nNxtButtonPressed == 2) {
			motor[WHEEL] = -motorPresets[i];
			motor[BELT] = motorPresets[i];
		} else {
			motor[WHEEL] = motor[BELT] = 0;
		}

		// check if touch down
		touch = SensorValue[TOUCH] == 1;

		// get color
		switch (SensorValue[COLOR]) {
			case 0:
				color = "invalid";
				break;
			case 1:
				color = "black";
				break;
			case 2:
				color = "blue";
				break;
			case 3:
				color = "green";
				break;
			case 4:
				color = "yellow";
				break;
			case 5:
				color = "red";
				break;
			case 6:
				color = "white";
				break;
			default:
				color = "";
				break;
		}

		// output to screen
		float speed = getSpeed(motorA);
		eraseDisplay();
		displayString(0, touch ? "down" : "up");
		displayString(1, "color %s", color);
		displayString(2, "motor %d", motorPresets[i]);
		displayString(3, "%f", speed);
	}
}
