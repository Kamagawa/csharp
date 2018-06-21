#define TRAY motorA

/*void moveTray (int power, int distCm)
{
	if (distCm < 0)
		power*= -1;

	int encVal = distCM / CIRCUM_CM * 360;
	nMotorEncoder[TRAY] = 0;

	motor[TRAY] = power;
	nMotorEncoderTarget[TRAY] = encVal;
	while(nMotorRunState[TRAY] != runStateIdle) { }
	motor[TRAY] = 0;
}*/

task main() {
	nMotorEncoderTarget[TRAY] = 1000;
	motor[TRAY] = -50;
	while (nMotorRunState[TRAY] != runStateIdle) { }
	motor[TRAY] = 0;
}
