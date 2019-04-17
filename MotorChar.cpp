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
	power = constrain(power, -63, 63);
		if (motor == 1)
	{
		command = 64 + power;
	}
	else if (motor == 2)
	{
		command = power < 0 ? 191 - magnitude : 192 + magnitude;
	}

	serialPuts(fd, &command);

}

int main() {
	int x = 1;

	//for motor control
	int motor, p;

	//for encoder
	int tickCount = 0;
	int tmp = 0;
	clock_t t;
	double time_taken;
	bool new_t = true;

	pinMode(SwitchPin, INPUT);
	pinMode(RotateAPin, INPUT);
	pinMode(RotateBPin, INPUT);


	//Acceleration to top speed
	while(x==1){

		for (p = 0; p < 127; p++)
		{
			motordrive(1, p);
			motordrive(2, p);

			if (new_t == true) {
				t = clock();
				new_t = false;
			}
			rotaryDeal();
			//if (tmp != globalCounter){
			//	printf("%d\n", globalCounter);
			//	tmp = globalCounter;
			//}
			if (tmp != globalCounter) {
				tmp = globalCounter;
				tickCount++;
			}
			if (tickCount == 50) {
				t = clock() - t;
				time_taken = ((double)t) / CLOCKS_PER_SEC;
				printf("%f\n", time_taken);
				tickCount = 0;
				new_t = true;
			}
		}
		x = 2;
	}

	//decelerating from top speed
	while(x==2)
	{
		for (p = 127; p <= 0; p--)
		{
			motordrive(1, p);
			motordrive(2, p);

			if (new_t == true) {
				t = clock();
				new_t = false;
			}
			rotaryDeal();
			//if (tmp != globalCounter){
			//	printf("%d\n", globalCounter);
			//	tmp = globalCounter;
			//}
			if (tmp != globalCounter) {
				tmp = globalCounter;
				tickCount++;
			}
			if (tickCount == 50) {
				t = clock() - t;
				time_taken = ((double)t) / CLOCKS_PER_SEC;
				printf("%f\n", time_taken);
				tickCount = 0;
				new_t = true;
			}
		}
		x = 3;
	}

}