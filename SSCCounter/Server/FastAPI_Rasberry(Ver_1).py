# ============ Set ============

#  -*- coding: utf-8 -*-
from fastapi import FastAPI
from fastapi.templating import Jinja2Templates
from datetime import datetime

# ============ Function ============
# def check():
#     global ncnt_people, standard_time
#     with open("nCnt.txt", "r") as file:
#         for line in file.readlines():
#             info_list = line.split("/")
#             ncnt_people = info_list[0]
#             standard_time = info_list[1]
#             print("\n", line, "\n")

# ============ Machine ============

# 웹 출력
app = FastAPI()

templates = Jinja2Templates(directory="templates")

@app.get("/SSCC_INFO")
async def POST_Sensor():
    # Data_Get()  People_Number, Measure_Time, Temperature, Humidity, Lamp
    People_Number, Measure_Time, Temperature, Humidity, Lamp = 100, "2022-11-25 03:01:10", 24, 80, "On"
    Current_Time = str(datetime.now() )[0:21]  # 필요한 부분 가공
    return {"Send_Time": Current_Time,"People_Number": People_Number, "Measure_Time": Measure_Time, "Temperature": Temperature, "Humidity": Humidity, "Lamp": Lamp}