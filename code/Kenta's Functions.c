void zeroTray(){
	while(!SensorValue[TRAY_TOUCH]){
		motor[TRAY] = 75;//change as needed
	}
}

void ejectPencil(){
	motor[WHEEL] = 100;
	while(!sensorValue[WHEEL_TOUCH]){}
	while(sensorValue[WHEEL_TOUCH]){}

	nMotorEncoder[WHEEL] = 0;
	while(nMotorEncoder[WHEEL] < 500){}//change as needed
	motor[WHEEL] = 0;
}

int getPencilColour(){
	clearTimer(T1);
	int count = 0;
	int ColourType[7];
	while(time1[T1] < 1000 && count < 1000){//get average colour seen
		ColourType[SensorValue[COLOUR]]++;
	}

	int modeColourFreq = 0, modeColour = 0;
	for (int i = 0; i < 7; i++){//finds colour sensed the most frequently
		if (ColourType[i] > modeColourFreq){
			modeColourFreq = ColourType[i];
			modeColour = i;
		}
	}
	return modeColour;
}
