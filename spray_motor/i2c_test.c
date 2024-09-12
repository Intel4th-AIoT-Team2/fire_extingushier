#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    int file;
    int adapter_nr = 1; // I2C 버스 번호 (젯슨 나노에서는 보통 1번)
    char filename[20];
    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    
    // I2C 장치 열기
    file = open(filename, O_RDWR);
    if (file < 0) {
        perror("I2C 장치를 열 수 없습니다");
        return -1;
    }

    int addr = 0x40; // I2C 슬레이브 주소 (통신할 장치의 주소로 변경해야 함)
    char buffer[2];

    // I2C 장치 설정
    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        perror("I2C 슬레이브 설정 실패");
        close(file);
        return -1;
    }

    // 레지스터에서 데이터를 읽어오기
    buffer[0] = 0x01; // 읽을 레지스터 주소
    if (write(file, buffer, 1) != 1) {
        perror("레지스터 주소 전송 실패");
        close(file);
        return -1;
    }

    // 데이터 읽기
    if (read(file, buffer, 1) != 1) {
        perror("I2C 읽기 실패");
        close(file);
        return -1;
    }

    printf("레지스터 0x01의 값: 0x%02x\n", buffer[0]);

    close(file);
    return 0;
}

