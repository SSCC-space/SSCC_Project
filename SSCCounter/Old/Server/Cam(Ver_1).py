# -*- coding: utf-8 -*-
import cv2
from datetime import datetime

# 변수 지정
Measure_Time = "0"
x,y,w,h = 321, 85, 80, 47   # 블러 영역 선택
Blur_Size = 30              # 블러 처리에 사용할 커널 크기

# 사진 촬영 함수
def Cam():
    global x,y,w,h, Blur_Size
    cap = cv2.VideoCapture(0)
    if cap.isOpened():
        while True:
            ret, frame = cap.read()
            if ret:
                if cv2.waitKey(1) == -1:
                    roi = frame[y:y+h, x:x+w]                    # 관심영역 지정
                    roi = cv2.blur(roi, (Blur_Size, Blur_Size))  # 블러(모자이크) 처리
                    frame[y:y+h, x:x+w] = roi                    # 원본 이미지에 적용
                    cv2.imwrite('photo.jpg', frame)              # 이미지 저장
                    break
            else:
                print('no frame')
                break
    else:
        print('no camera!')
    cap.release()

# 사진 촬영
Cam()
Measure_Time = str(datetime.now())[0:21]

img = "photo.jpg"        # 이미지 경로
frame = cv2.imread(img)  # 이미지 읽어오기