#include <unistd.h>
#include <stdlib.h>

#include "gpioModule.h"
#include "timerTest.h"


int main(){
	enPwm();
	controlMotorAngle(0, 4n5);
	controlMotorAngle(2, 135);
	toggleSpray(78);
	disPwm();	
	
	return 0;
}
