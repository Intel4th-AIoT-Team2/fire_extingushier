import serial
import time


IMG_W = 24
IMG_H = 32
port = '/dev/ttyTHS1'  # Jetson Nano의 시리얼 포트
baud = 115200  # Baud rate

ser = serial.Serial(port, baud, timeout=1)

# 데이터 읽기
time.sleep(2)
data = ser.read(ser.in_waiting or 1) 
print(data)  # 읽은 데이터 디코딩 후 출력

# 데이터 읽기
time.sleep(2)
data = ser.read(ser.in_waiting or 1) 
print(data)  # 읽은 데이터 디코딩 후 출력

# 데이터 읽기
time.sleep(2)
data = ser.read(ser.in_waiting or 1) 
print(data)  # 읽은 데이터 디코딩 후 출력

# 포트 닫기
ser.close()

