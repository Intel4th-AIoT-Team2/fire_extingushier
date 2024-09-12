#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 중간중간에 일부러 문자열로 다 넣고 하드코딩 한 부분 있어요 
// 어차피 젯슨 나노로 장비는 고정되어 있으니까요!
/*
echo 0 > /sys/class/pwm/pwmchip0/export 
echo 20000000 > /sys/class/pwm/pwmchip0/pwm0/period 
echo 1000000 > /sys/class/pwm/pwmchip0/pwm0/duty_cycle 
echo 1 > /sys/class/pwm/pwmchip0/pwm0/enable 
*/

void reverse(char str[], int length) {
	int start = 0;
	int end = length - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

char* itoa(int num, char* str, int base) {
	int i = 0;
	bool isNegative = false;

	// 0인 경우 바로 문자열 "0"으로 반환
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// 음수 처리 (10진수일 경우에만)
	if (num < 0 && base == 10) {
		isNegative = true;
		num = -num;
	}

	// 숫자를 문자열로 변환
	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	// 음수일 경우 '-' 추가
	if (isNegative) {
		str[i++] = '-';
	}

	// 문자열 끝에 NULL 추가
	str[i] = '\0';

	// 문자열을 뒤집어서 올바른 순서로 정렬
	reverse(str, i);

	return str;
}

// pwm 번호를 입력 해주면 export 설정
int exportPwm(int num){
	int export_fd;
	if (num == 0) {
		export_fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY | O_TRUNC);
	} 
	else if(num == 4){
		export_fd = open("/sys/class/pwm/pwmchip4/export", O_WRONLY | O_TRUNC);
	} 
	else {
		puts("PWM number error");
		return -1;
	}
	
	if (export_fd == -1) {
		perror("Open export_fd");
		return -1;
	}
	
	if (write(export_fd, "0", 1) != 1){
		perror("export_fd - write error");
		return -1;
	}
	close(export_fd);
	
	return 0;
}

// pwm 번호와 설정하고 싶은 주기와 듀티(1일 시간)을 nsec 단위로 입력하면 설정
int setPwm(int num, int period, int duty){
	int period_fd, duty_fd;
	int tmp;
	char period_str[10], duty_str[10];

	if (num == 0){
		period_fd = open("/sys/class/pwm/pwmchip0/pwm0/period", O_WRONLY | O_TRUNC);
		duty_fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY | O_TRUNC);
	} 
	else if(num == 4){
		period_fd = open("/sys/class/pwm/pwmchip4/pwm4/period", O_WRONLY | O_TRUNC);
		duty_fd = open("/sys/class/pwm/pwmchip4/pwm4/duty_cycle", O_WRONLY | O_TRUNC);
	} 
	else {
		perror("PWM number error");
		return -1;
	}
	
	if (period_fd == -1 | duty_fd == -1) {
		perror("Open period_fd | duty_fd error");
		return -1;
	}

	itoa(period, period_str, 10);
	itoa(duty, duty_str, 10);

	tmp = strlen(period_str);
	if (write(period_fd , period_str, tmp) != tmp) {
		perror("period_fd - write error");
		return -1;
	}

	tmp = strlen(duty_str);
	if (write(duty_fd , duty_str, tmp ) != tmp) {
		perror("duty_fd - write error");
		return -1;
	}
	close(period_fd);
	close(duty_fd);
	
	return 0;
}

// pwm 번호를 입력 해주면 enable 설정
int enablePwm(int num){
	int enable_fd;
	if (num == 0){
		enable_fd = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY | O_TRUNC);
	} 
	else if(num == 4){
		enable_fd = open("/sys/class/pwm/pwmchip4/pwm4/enable", O_WRONLY | O_TRUNC);
	} 
	else {
		perror("PWM number error");
		return -1;
	}
	
	if (enable_fd == -1) {
		perror("Open enable_fd ");
		return -1;
	}
	
	if (write(enable_fd, "1", 1) != 1){
		perror("enable_fd - write error");
		return -1;
	}
	close(enable_fd);
	
	return 0;
}

int main(){
	exportPwm(0);
	setPwm(0, 20000000, 1000000);
	enablePwm(0);

	return 0;
}
