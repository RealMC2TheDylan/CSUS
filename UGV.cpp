#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int constrain(int power, int low, int high) {
	if (power > high) {
		power = high;
	}
	else if (power < low) {
		power = low;
	}
	else
		return power;
}

void motordrive(int motor, int power)
{
	char command;
	char magnitude;
	power = constrain(power, -63, 63);
	if (motor == 1)
	{
		command = 64 + power;
	}
	else if (motor == 2)
	{
		command = 191 + power; // changed from 190 and 191
	}

	serialPuts(fd, &command);
	serialPuts(fd, &command);
}