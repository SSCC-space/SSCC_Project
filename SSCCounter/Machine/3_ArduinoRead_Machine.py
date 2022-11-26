#  -*- coding: utf-8 -*-
from fastapi import FastAPI, File, UploadFile
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from datetime import datetime
import serial

#port = serial.Serial("/dev/ttyUSB0", "9600")
port = serial.Serial("COM3", "9600")

def Get_Arduino():
  global temp, hum, cds, lamp
  response_data = port.radline()
  print(response_data)
  data = response_data.split("/")
  temp = data[1]
  hum = data[2]
  cds = data[3]
  if cds >= 500:
    lamp = "On"
  else:
    lamp = "Off"
    
app = FastAPI()

@app.get("/SSCC_info")
async def nCnt():
    Get_Arduino()
    measurement_time = str(datetime.now())[0:21]  # 필요한 부분 가공
    print("온도: {}, 습도: {}, 조도: {}\n".format(temp, hum, cds))
    return {"measurement_time": measurement_time, "temperature": temp, "humidity": hum, "lamp": lamp}

@app.post("/files/")
async def create_file(file: bytes = File()):
  return {"file_size": len(file)}

@app.get("/uploadfile/")
async def create_upload_file(file: UploadFile):
  return {"filename": file.filename}