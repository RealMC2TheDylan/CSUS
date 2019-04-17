#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;

int fd = serialOpen("/dev/ttyS0", 38400);

int constrain(int power, int low, int high)
{
	if (power < low)
	{
		power = low;
	}
	else if (power > high)
	{
		power = high;
	}
	else
		power = power;
	return power;
}

void motordrive(int motor, int power)
{
	char command, magnitude;
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
	serialPuts(fd, &command);

}

int main()
{
	int motor, p;
	
	for (p = 0; p < 127; p++)
	{
		motordrive(1, p);
		motordrive(2, p);
		sleep_for(nanoseconds(500));
	}
	for (p = 127; p > -127; p--)
	{
		motordrive(1, p);
		motordrive(2, p);
		sleep_for(nanoseconds(500));
	}
	for (p = -127; p < 0; p++)
	{
		motordrive(1, p);
		motordrive(2, p);
		sleep_for(nanoseconds(500));
	}
	sleep_for(nanoseconds(4000));
}