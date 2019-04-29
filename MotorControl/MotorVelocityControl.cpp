#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

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
	double ul, ur;
	double L, vx, vz, r;
		
	L = .420;
    r=.1275

	motordrive(1, 0);
	motordrive(2, 0);

    while(1){	     
    	ul = (-0.5*vz*L+vx)/r;
		ur = (0.5*vz*L+vx)/r;
        
		
		if (vx > 0) {
			pr = round((ur / .1937));
            pl = round((ul / .1937));
		}
		else if (vx < 0) {
			pr = round((ur / .1934));
            pl = round((ul / .1934));
		}
		else {
			pr = 0;
            pl = 0;
	    }
		motordrive(1, pr);
		motordrive(2, pl);

	}
	motordrive(1, 0);

	motordrive(2, 0);
}