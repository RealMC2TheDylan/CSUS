// ToDo 
    // globalCounter available to ROS nodes for read and reset
    // ROSify it so that it can be run as a node
// does not include interrupts or connectivity to other terminals

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define RotateAPin_L 0 //Define as CLK
#define RotateBPin_L 1 // Define as DT

static volatile int globalCounter_R = 0; // will need to be modifiable from other nodes

unsigned char flag;
unsigned char Last_RoB_Status;
unsigned char Current_RoB_Status;

int main(void)
{
	pinMode(RotateAPin_R, INPUT);
	pinMode(RotateBPin_R, INPUT);
	while (1)
	{
		rotaryDeal();
	}
}

void rotaryDeal(void)
{
	Last_RoB_Status = digitalRead(RotateBPin_R);

	while (!digitalRead(RotateAPin_R)) // continue checking until leading edge of pin A
        {
		Current_RoB_Status = digitalRead(RotateBPin_R); // read pin B
		flag = 1;
	}

	if (flag == 1) {
		flag = 0;
		if ((Last_RoB_Status == 0) && (Current_RoB_Status == 1)) // cw
                {
			globalCounter_R++;
		}
		if ((Last_RoB_Status == 1) && (Current_RoB_Status == 0)) // ccw
                {
			globalCounter_R--;
		}
	}
}