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
	int pr,pl;
	float ul, ur;
	double L, r, v, x1, y, combine;
	double dx, dy, dtheta;
	
	L = .420;
	r = .1275;

	motordrive(1, 0);
	motordrive(2, 0);

	for (int x = 0; x < 6; x++) {
		printf("input dx between -6.742 and 6.742\n");
		scanf("%f", &dx);
		printf("input dy between -6.742 and 6.742\n");
		scanf("%f", &dy);
		printf("input dtheta between -90 and 90\n");
		scanf("%f", &dtheta);
		
		x1 = dx * dx;
		y = dy * dy;
		combine = x1 + y;
		v = sqrt(combine);

		ul = (-0.5*dtheta*L+v);
		ur= (0.5*dtheta*L+v);
		
		if (ur > 0) {
			pr = round((ur / .1937));
		}
		else if (ur < 0) {
			pr = round((ur / .1934));
		}
		else {
			pr = 0;
		}
		if (ul > 0) {
			pl = round((ul / .1937));
		}
		else if (ul < 0) {
			pl = round((ul / .1934));
		}
		else {
			pl = 0;
		}
		motordrive(1, pr);
		motordrive(2, pl);
	}
	motordrive(1, 0);

	motordrive(2, 0);
}