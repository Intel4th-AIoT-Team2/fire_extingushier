#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "itoa.h"
#include "pwm.h"

#define PERIOD 20000000

int controlMotorAngle(int pin, int angle){
	float duty = (angle / 180.0 + 1) * 1000000;

	setPwm(pin, PERIOD, duty);

	enablePwm(pin);

	return 0;
}

int enPwm() {
	exportPwm(0);
	exportPwm(2);
	
	return 0;
}

int disPwm(){
	disablePwm(0);
	disablePwm(2);
	unexportPwm(0);
	unexportPwm(2);

	return 0;
}
