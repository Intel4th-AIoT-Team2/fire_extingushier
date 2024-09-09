#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "pwm.h"

#define PERIOD 20000000
#define DUTY 1000000

int controlMotorAngle(int angle){
	if(angle == 0)
		return 0;

	pid_t pid;
	int status;
	int time = angle / 60.0 * 270000;

	pid = fork();
	switch (pid) {
		case -1 : /* fork failed */
			perror("fork");
			return -1;
			
		case 0 : /* child process */
			exportPwm(0);
			setPwm(0, PERIOD, DUTY);
			enablePwm(0);
			
			usleep(time);

			disablePwm(0);
			unexportPwm(0);

			return 0;
			break;
		default:
			while(wait(&status) != pid)
				continue;
			break;
	}
	return 0;
}
