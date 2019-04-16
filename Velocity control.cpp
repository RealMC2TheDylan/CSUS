#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define RotateAPin 0 //Define as CLK
#define RotateBPin 1// Define as DT
#define SwitchPin  2// Define as Push Button Switch

int fd = serialOpen("/dev/ttyS0", 38400);

static volatile int globalCounter = 0;

unsigned char flag;
unsigned char Last_RoB_Status;
unsigned char Current_RoB_Status;

void rotaryDeal(void)
{
	Last_RoB_Status = digitalRead(RotateBPin);

	while (!digitalRead(RotateAPin)) {
		Current_RoB_Status = digitalRead(RotateBPin);
		flag = 1;
	}

	if (flag == 1) {
		flag = 0;
		if ((Last_RoB_Status == 0) && (Current_RoB_Status == 1)) {
			globalCounter++;
		}
		if ((Last_RoB_Status == 1) && (Current_RoB_Status == 0)) {
			globalCounter--;
		}
	}
}


void motordrive(int motor, int power)
{
	byte command, magnitude;
	power = constrain(power, -127, 127);
	magnitude = abs(power) >> 1;
	if (motor == 1)
	{
		command = power < 0 ? 63 - magnitude : 64 + magnitude;
	}
	else if (motor == 2)
	{
		command = power < 0 ? 191 - magnitude : 192 + magnitude;
	}

	command = constrain(command, 1, 254);
	serialPuts(fd, command);

}

int main() {
	//for motor control
	int motor, p;

	//for encoder
	int tickCount = 0;
	int tmp = 0;
	clock_t t;
	double time_taken;
	bool new_t = true;

	//velocity variables
	double Diam = ;//in centimeters
	double Pi = 3.14159265359;
	double tickRev = ;
	double tickDist, distance;
	double l = ;//length of robot
	double w = ;//width of robot
	double Vx, Vy, Vz;
	double X, Y, Z;
	double circu;

	//Preliminary math
	circu = Pi * Diam * 100; // conversion to meter
	tickDist = circu / tickRev;
	
	pinMode(SwitchPin, INPUT);
	pinMode(RotateAPin, INPUT);
	pinMode(RotateBPin, INPUT);


	//velocity calculations
	while (1) {
		if (new_t == true) {
			t = clock();
			new_t = false;
		}
		//needs to happen for left and right encoder
		//assuming first example is for right side
		rotaryDeal();
		//if (tmp != globalCounter){
		//	printf("%d\n", globalCounter);
		//	tmp = globalCounter;
		//}
		if (tmp != globalCounter) {
			tmp = globalCounter;
			tickCount++;
		}
		if (tickCount == 20) {
			t = clock() - t;
			time_taken = ((double)t) / CLOCKS_PER_SEC;
			printf("%f\n", time_taken);
			tickCount = 0;
			new_t = true;
		}
		distance = tickCount * tickRev;
		Vx = distance * time_taken;


	}
