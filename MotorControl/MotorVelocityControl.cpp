#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const int fd = serialOpen("/dev/ttySAC0", 38400);

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

int main()
{
	int motor;
	int p,pr,py;
	int i;

	motordrive(1, 0);
	motordrive(2, 0);

	for (int x = 0; x == 6; x++) {
		printf("Select a velocity between -1.2 and 1.2 m/sec")
			scanf("%i", p);
		if (p >= 0) {
			pr = round((p / .0241));
			pl = pr
		}
		else if (p < 0) {
			pr = round((p / .0235));
			pl = round((p / .0239));
		}
		motordrive(1, pr);
		motordrive(2, pl);
	}
	motordrive(1, 0);

	motordrive(2, 0);
}