import cv2
import sys


cam = cv2.VideoCapture(0) 

if cam.isOpened():  
    ret, frame = cam.read()  # 프레임 읽기

    if ret:
        # 프레임을 BGR에서 RGB로 변환
        cv2.imwrite("img/"+sys.argv[1], frame)

    cam.release()  # 카메라 해제
else:
    print("Error: Camera not opened")

