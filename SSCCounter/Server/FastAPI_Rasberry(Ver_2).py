#  -*- coding: utf-8 -*-
from fastapi import FastAPI, File, UploadFile
from fastapi.templating import Jinja2Templates
from datetime import datetime
from socket import *
from os.path import exists
import sys


def Post_Image():
    serverSock = socket(AF_INET, SOCK_STREAM)
    serverSock.bind(('', 8080))
    serverSock.listen(1)

    connectionSock, addr = serverSock.accept()

    print(str(addr),'에서 접속했습니다')

    filename = connectionSock.recv(1024) #클라이언트한테 파일이름(이진 바이트 스트림 형태)을 전달 받는다
    print('받은 데이터 : ', filename.decode('utf-8')) #파일 이름을 일반 문자열로 변환한다
    data_transferred = 0

    if not exists(filename):
        print("no file")
        sys.exit()

    print("파일 %s 전송 시작" %filename)
    with open(filename, 'rb') as f:
        try:
            data = f.read(1024) #1024바이트 읽는다
            while data: #데이터가 없을 때까지
                data_transferred += connectionSock.send(data) #1024바이트 보내고 크기 저장
                data = f.read(1024) #1024바이트 읽음
        except Exception as ex:
            print(ex)
    print("전송완료 %s, 전송량 %d" %(filename, data_transferred))

app = FastAPI()

templates = Jinja2Templates(directory="templates")

@app.post("/files/")
async def create_file(file: bytes = File()):
    return {"file_size": len(file)}

@app.post("/uploadfile/")
async def create_upload_file(file: UploadFile):
    return {"filename": file.filename}

@app.get("/SSCC_INFO")
async def POST_Sensor():
    # Data_Get()  People_Number, Measure_Time, Temperature, Humidity, Lamp
    People_Number, Measure_Time, Temperature, Humidity, Lamp = 100, "2022-11-25 03:01:10", 24, 80, "On"
    Current_Time = str(datetime.now() )[0:21]  # 필요한 부분 가공
    return {"Send_Time": Current_Time,"People_Number": People_Number, "Measure_Time": Measure_Time, "Temperature": Temperature, "Humidity": Humidity, "Lamp": Lamp}