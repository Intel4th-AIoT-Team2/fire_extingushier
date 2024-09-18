#include <Wire.h>
#include <TimerOne.h>
#include <SoftwareSerial.h>

SoftwareSerial RPI(2, 3);

#define DEV_ADDR 0x33
#define IMG_W 24
#define IMG_H 32

bool timerIsrFlag = false;    // 1초가 지났는지 확인하기 위한 변수


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  RPI.begin(115200);

  Timer1.initialize(2000000);   // 단위는 마이크로 세크 / 1초 단위로 인터럽트를 발생시키는 설정
  Timer1.attachInterrupt(timerIsr);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 0;
  uint8_t img[IMG_W * IMG_H * 3];
  uint16_t i2c_received = 0;

  Wire.beginTransmission(DEV_ADDR);
  Wire.write(0);  // MSB 주소
  i2c_received = Wire.endTransmission(false);

  if (timerIsrFlag){
    while (i < IMG_W * IMG_H * 3) {
      while (i2c_received != 1) {
        i2c_received = Wire.requestFrom(DEV_ADDR, 1);
      }

      i2c_received = Wire.requestFrom(DEV_ADDR, 1);

      if (i2c_received == 1)
        Wire.readBytes(img, 1);
      else {
        Serial.println(i2c_received);
        Serial.println("requestFrom");
      }

      i++;
    }

    // 시리얼을 통한 출력 확인 
    for (int i = 0; i < IMG_W*IMG_H*3; i++) {
      Serial.print(img[i]);
      RPI.print(img[i]);

      if ((i != 0) && (i % (IMG_W*IMG_H) == 0)){
        Serial.println("\n-------------------------");
        RPI.print("-");
      }
      else if ((i != 0) && (i % IMG_W == 0)){
        Serial.println(" ");
        RPI.print("/");
      }
      else {
        Serial.print(" ");
        RPI.print(" ");
      }
    }
    Serial.println("\n===================");
    RPI.print("=");
  }
}


void timerIsr()
{
  timerIsrFlag = true;
}
