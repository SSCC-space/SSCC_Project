# ============ Set ============

#  -*- coding: utf-8 -*-
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
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

app.mount("/static", StaticFiles(directory="static"), name="static")

templates = Jinja2Templates(directory="templates")

@app.get("/SSCC_INFO")
async def POST_Sensor():
    # check()
    temp, hum, lamp, ncnt_people, standard_time = 0, 0, 0, 0, "Testing"
    current_time = str(datetime.now() )[0:21]  # 필요한 부분 가공
    print(ncnt_people)
    return {"temperature": temp, "humidity": hum, "lamp": lamp,"people_count": ncnt_people, "last_time": current_time, "get_time": standard_time}