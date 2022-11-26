# -*- coding: utf-8 -*-

# ============ Set ============

import cv2
import numpy as np
from datetime import datetime

# 변수 지정
People_Number, Measure_Time = 0, "0"
x,y,w,h = 321, 85, 80, 47 # 관심영역 선택
Blur_Size = 30              # 블러 처리에 사용할 커널 크기

# 사물 class
classes = ["person",  "bench", "umbrella", "handbag","bottle", "chair", "bed", "dining table",
           "laptop", "remote", "keyboard", "cell phone", "microwave", "refrigerator", "book"]

# Yolov3 네트워크 블러오기
net = cv2.dnn.readNet("yolov3.weights", "yolov3.cfg")
layer_names = net.getLayerNames()
output_layers = [layer_names[i - 1] for i in net.getUnconnectedOutLayers()]



# ============ Function ============ 

# 사진 촬영 함수
def Cam():
    cap = cv2.VideoCapture(0)
    if cap.isOpened():
        while True:
            ret, frame = cap.read()
            if ret:
                if cv2.waitKey(1) == -1:
                    global x,y,w,h
                    roi = frame[y:y+h, x:x+w]   # 관심영역 지정
                    roi = cv2.blur(roi, (Blur_Size, Blur_Size)) # 블러(모자이크) 처리
                    frame[y:y+h, x:x+w] = roi   # 원본 이미지에 적용
                    cv2.imwrite('photo.jpg', frame)  # 이미지 저장
                    break
            else:
                print('no frame')
                break
    else:
        print('no camera!')
    cap.release()

# Yolov3 분석 함수
def yolo(frame, size, score_threshold, nms_threshold):
    global People_Number
    height, width, channels = frame.shape  # 이미지의 높이, 너비, 채널 받아오기
    blob = cv2.dnn.blobFromImage(frame, 0.00392, (size, size), (0, 0, 0), True, crop=False)  # 네트워크에 넣기 위한 전처리
    net.setInput(blob)  # 전치리된 blob 네트워크에 입력
    outs = net.forward(output_layers)  # 결과 받아오기
    # 각각의 데이터를 저장할 빈 리스트
    class_ids = []
    confidences = []
    boxes = []
    for out in outs:
        for detection in out:
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0.1:
                # 탐지된 객체의 너비, 높이 및 중앙 좌표값 찾기
                center_x = int(detection[0] * width)
                center_y = int(detection[1] * height)
                w = int(detection[2] * width)
                h = int(detection[3] * height)
                # 객체의 사각형 테두리 중 좌상단 좌표값 찾기
                x = int(center_x - w / 2)
                y = int(center_y - h / 2)
                boxes.append([x, y, w, h])
                confidences.append(float(confidence))
                class_ids.append(class_id)
    indexes = cv2.dnn.NMSBoxes(boxes, confidences, score_threshold=score_threshold, nms_threshold=nms_threshold)# 후보 박스(x, y, width, height)와 confidence(상자가 물체일 확률) 출력
    People_Number = 0
    for i in range(len(boxes)):
        if i in indexes:
            x, y, w, h = boxes[i]
            try:  # 인식된 사물 분석 시도
                class_name = classes[class_ids[i]]
                if class_name == "people":
                    People_Number += 1  # 사람이 인식되면 People_Number 변수 +1
            except IndexError:  # 오류 발생시 pass
                pass
    return frame


Cam()
Measure_Time = str(datetime.now())[0:21]
img = "photo.jpg"  # 이미지 경로
frame = cv2.imread(img)  # 이미지 읽어오기
size_list = [320, 416, 608]  # 입력 사이즈 리스트 (Yolov3에서 사용되는 네트워크 입력 이미지 사이즈)
frame = yolo(frame=frame, size=size_list[2], score_threshold=0.4, nms_threshold=0.4)  # 이미지 분석
with open("nCnt.txt", "w", encoding = "utf8") as report_file:
    report_file.write("{0}/{1}".format(People_Number, Measure_Time))
    print(People_Number)