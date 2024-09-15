#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "itoa.h"
#include "gpioModule.h"
#include "motorCtl.h"

int onAI();
int offAI();
int workAI();

bool findPos(char *angle_x, char *angle_y);

void handler(int signo);
int takePic(char *filename);
int pid_ai = 0;


// 터틀봇 도착시 실행되는 함수 
int main(int argc, char *argv[]){
	bool fire_flag;
	char angle_x, angle_y;
///	
	// 입력 받은 값으로 테스트 
	fire_flag = atoi(argv[1]);
//*
	// motor init	
//	enPwm();
	// ai 스레드 초기화
	onAI();
	workAI();	

	// 카메라를 통해서 사진 촬영
	// 상하 각도를 정면을 바라보도록 변경 
	controlMotorAngle(0, 90);

	// 정면
	controlMotorAngle(2, 90);
	waitCtl(0.5);
	takePic("front.jpg");

	// 좌측 
	controlMotorAngle(2, 30);
	waitCtl(0.5);
	takePic("left.jpg");

	// 우측 
	controlMotorAngle(2, 150);
	waitCtl(0.5);
	takePic("right.jpg");

	// 사진 검사 
	workAI();
	fire_flag = findPos(&angle_x, &angle_y);

	// 촬영한 방향에 불이 없으면
	if(!fire_flag){
		// 터틀봇 회전
		

		// 다시 정면 좌우 촬영
		

		// 없으면 복귀

	}
	
	
	// 활영한 방향에 불이 있으면 
	if (fire_flag){
		// 사진의 세로 픽셀 값을 동해서 각도 추정

		// 방향 회전	
		controlMotorAngle(0, atoi(argv[2]));
		controlMotorAngle(2, atoi(argv[3]));

		controlMotorAngle(0, angle_x);
		controlMotorAngle(2, angle_y);
		waitCtl(0.5);

		// 스프레이 on
		toggleSpray(78);

		// 카메라에 붉은 픽셀이 일정 이상일 동안 
		while (fire_flag){
			// 대기
			// cam에서 불 확인 
			
			// 테스트 용으로 5초 대기 후 종료
			waitCtl(3);
			break;
		}

		// 스프레이 off
		toggleSpray(78);
	}

	// 정면 보도록 조정 	
	controlMotorAngle(0, 90);
	controlMotorAngle(2, 90);
	waitCtl(0.5);

	// motor disable
//	disPwm();

	// ai 프로세스 끄기 
	offAI();

	return 0;
}

// 사진을 찍어서 filename으로 저장하는 함수 
int takePic(char *filename){
	int status;
	char pyPath[100];
	char filePath[16] = "./";
	pid_t pid = fork();

	switch (pid) {
		case -1 : /* fork failed */
			perror("fork");
			return -1;

		case 0 : /* child process */
			getcwd(pyPath, 100);

			strcat(pyPath, "/takePic.py");
			strcat(filePath, filename);

			status = execl("/usr/bin/python3", "python3", pyPath, filePath, NULL);

			if(status < 0){
				perror("execl error");
				return -1;
			}

			return 0;
		default:
			while(wait(&status) != pid)
				continue;
			break;
	}
	return 0;
}

// 사진을 검사하는  ai의 스레드를 만드는 함수 
int onAI(){
        int status;
        char pyPath[100];
        pid_t pid = fork();
	sigset_t set;
	
	// SIGUSR1 handler 등록 
	signal(SIGUSR1, handler);
	sigfillset(&set);
	sigdelset(&set, SIGUSR1);

        switch (pid) {
                case -1 : /* fork failed */
                        perror("fork");
                        return -1;

                case 0 : /* child process */
                        getcwd(pyPath, 100);

                        strcat(pyPath, "/detectPic.py");	

                        status = execl("/usr/bin/python3", "python3", pyPath, NULL);

                        if(status < 0){
                                perror("execl error");
                                return -1;
                        }

                        return 0;
		default:
			pid_ai = pid;
			sigsuspend(&set);
			break;
	}

        return 0;
}

// 사진 검사 신호를 보내는 함수 
int workAI(){
	sigset_t set;

	// SIGUSR1 handler 등록 
	signal(SIGUSR1, handler);
	sigfillset(&set);
	sigdelset(&set, SIGUSR1);

	if (kill(pid_ai, SIGUSR1) == -1) {
		puts("kill -> SIGUSR1 error");
	}
	sigsuspend(&set);

        return 0;
	
}

// 사진을 검사하는 ai를 끄는 함수 
int offAI(){
	char *strPath[3] = {"img/front.jpg", "img/left.jgp", "img/right.jpg"};
	int result;

	kill(pid_ai, SIGKILL);	
	for (int i=0;i<3;i++){
		result = remove(strPath[i]);
		if(result)
			puts("remove error");
	}

	return 0;
}

// SIGUSR1 handler
void handler(int signo) {
	// do nothing 
	;
}

// 출력되어 있는 좌표값으로 화재의 유무와 위치를 판단하는 함수 
bool findPos(char *angle_x, char *angle_y){
	// 640 - 480
	

}

/*
int angleSpary(int vert, int horiz){
	enPwm();
	// 상하 각도 
	controlMotorAngle(0, vert);
	// 좌우 회전 
	controlMotorAngle(2, horiz);
	toggleSpray(78);
	disPwm();	
	
	return 0;
}
*/
