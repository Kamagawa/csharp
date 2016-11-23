bool movePiston(int power, int distanceCM, int gearRadiusCM, int cm = 0, ){

	 	int distPcts = gearRadiusCM * 2 * PI /360;

	 	m1.setMotorPower (power);
	 	m1.setMotorPower (power);
	 	nMotorEncoder[motorB] = 0;

	 	while ( distPcts * nMotorEncoder[motorB] < distance)
	  {
	  	//Emergency Stop right here.
	  }


   m1.setMotorPower (0);
	 m1.setMotorPower (0);

   nMotorEncoder[motorB] = 0;
	 return true;
}
