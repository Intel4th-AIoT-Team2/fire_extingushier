#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "modules/ai.h"
#include "modules/itoa.h"
#include "modules/motorCtl.h"
#include "modules/gpioModule.h"


int pid_ai = 0;

// 터틀봇 도착시 실행되는 함수 
int main(int argc, char* argv[]) {
	bool fire_flag;
	char angle_x, angle_y;

	// ai 스레드 초기화
	onAI(&pid_ai);
	workAI(&pid_ai);

	// 카메라를 통해서 사진 촬영
	// 상하 각도를 정면을 바라보도록 변경 
	controlMotorAngle(0, 90);

	// 정면
	controlMotorAngle(2, 90);
	waitCtl(0.5);
	takePic("front.jpg");

	// 좌측 
	controlMotorAngle(2, 20);
	waitCtl(0.5);
	takePic("right.jpg");

	// 우측 
	controlMotorAngle(2, 160);
	waitCtl(0.5);
	takePic("left.jpg");

	// 사진 검사 
	workAI(&pid_ai);

	fire_flag = findPos(&angle_x, &angle_y);

	// 촬영한 방향에 불이 없으면
	if (!fire_flag) {
		// 터틀봇 회전


		// 다시 정면 좌우 촬영


		// 없으면 복귀

	}


	// 활영한 방향에 불이 있으면 
	if (fire_flag) {
		puts("여긴가");
		// 사진의 세로 픽셀 값을 동해서 각도 추정

		// 방향 회전	
		controlMotorAngle(0, angle_x);
		controlMotorAngle(2, angle_y);
		waitCtl(0.5);

		// 스프레이 on
		toggleSpray(78);

		// 카메라에 붉은 픽셀이 일정 이상일 동안 
		while (fire_flag) {
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

	// ai 프로세스 끄기 
	offAI(&pid_ai);

	return 0;
}
