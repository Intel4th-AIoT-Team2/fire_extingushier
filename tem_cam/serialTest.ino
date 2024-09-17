#include <SoftwareSerial.h>

SoftwareSerial RPI(2, 3);
String income = "";

void setup() {
  Serial.begin(9600);
  RPI.begin(9600);
}

void loop() {
  while(RPI.available()) {
    income += (char)RPI.read();  // RPI에서 데이터 읽기
  }

  if (income.length() > 0) {  // 문자열이 빈 문자열이 아닐 때
    Serial.println(income);    // Arduino에서 읽은 데이터 출력
    RPI.print(income);         // 받은 데이터를 다시 RPI로 전송
    income = "";               // income 초기화
  }
}
