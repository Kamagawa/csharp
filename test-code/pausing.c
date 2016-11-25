task count() {
	int i = 0;
	while (true) {
		displayString(1, "%d", i++);
		wait1Msec(100);
	}
}

task main() {
	SensorType[S1] = sensorTouch;
	startTask(count);

	bool down;
	while (true) {
		down = SensorValue[S1] == 1;
		displayString(2, "%d", down);
		if (down){
			hogCPU();
			while (SensorValue[S1] == 1) { }
			releaseCPU();
		}
	}
}
