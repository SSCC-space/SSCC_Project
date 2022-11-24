# ============ Set ============

#  -*- coding: utf-8 -*-
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from datetime import datetime
import requests

url = "http://114.71.48.94:8080/nCnt"

data = requests.get(url).json()

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

@app.get("/", response_class=HTMLResponse)
# , ncnt_people: str, current_time: str, standard_time: str):
async def Page(request: Request):
    # check()
    temp, hum, lamp, ncnt_people, standard_time = "Testing", "Testing", "Testing", 100, "Testing"
    current_time = str(datetime.now() )[0:21] + " (Developing)"  # 필요한 부분 가공
    if ncnt_people <= 6:
        countable = 1
    else:
        countable = 0
    # FastAPI로 new.html에 변수 값 전달
    return templates.TemplateResponse("index(Ver_7).html", {"request": request, "temperature": temp, "humidity": hum, "lamp": lamp,"people_count": ncnt_people, "countable": countable, "last_time": current_time, "get_time": current_time})

@app.get("/nCnt")
async def nCnt():
    # check()
    temp, hum, lamp, ncnt_people, standard_time = 0, 0, 0, 0, "Testing"
    current_time = str(datetime.now() )[0:21]  # 필요한 부분 가공
    print(ncnt_people)
    return {"temperature": temp, "humidity": hum, "lamp": lamp,"people_count": ncnt_people, "last_time": current_time, "get_time": standard_time}