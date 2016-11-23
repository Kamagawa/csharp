bool movePiston(int power, int distanceCM, int gearRadiusCM, int cm = 0 ){

	 	int distPcts = gearRadiusCM * 2 * PI /360;
	 	int avgSpeed;
	 	int tempEncoder;

	 	m1.setMotorPower (power);
	 	m1.setMotorPower (power);
	 	nMotorEncoder[motorB] = 0;
	 	clearTimer(T1);

	 	while ( distPcts * nMotorEncoder[motorB] < distance)
	  {
	  	if (time (T1)>=100){
	  		avgSpeed = nMotorEncoder[motorB];
	  	}
	  		//Emergency Stop right here.
	  }

   m1.setMotorPower (0);
	 m1.setMotorPower (0);

	 return true;
}
