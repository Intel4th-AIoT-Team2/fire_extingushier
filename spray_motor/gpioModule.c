#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "gpio.h"

int toggleSpray(int gpioNum){
	if(gpioNum == 0)
		return 0;

	exportGpio(gpioNum);
	setDirectionGpio(gpioNum, "high");

	setGpio(gpioNum, 1);
	sleep(1);
	setGpio(gpioNum, 0);

	disableGpio(gpioNum);
	return 0;
}

