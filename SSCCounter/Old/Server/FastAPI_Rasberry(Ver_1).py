# ============ Set ============

#  -*- coding: utf-8 -*-
from fastapi import FastAPI, File, UploadFile
from fastapi.templating import Jinja2Templates
from datetime import datetime

# ============ Machine ============

# 웹 출력
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