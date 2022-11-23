# ============ Set ============

# -*- coding: utf-8 -*-
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates

# 수온: water_temp
# PH농도: ph_state
# 물 수위: water_level
# 조도센서: light_intensity
# 먹이 줬는지: last_feed

# 값 처리
# 수온: float
# ph농도: float
# 물 수위: int
# 조도센서: int
# 먹이 줬는지: bool

# ============ Function ============ 
def check():
  global time, water_temp, water_level, ph_state, light_intensity, last_feed
  with open("Purun.txt", "r") as file:
      for line in file.readlines():
        value_list = line.split("/")
        time = value_list[0]
        water_temp = value_list[1]
        water_level = value_list[2]
        ph_state = value_list[3]
        light_intensity = value_list[4]
        last_feed = value_list[5]

# ============ Machine ============ 

# 웹 출력    
app = FastAPI()

@app.get("/api/data")
async def data_request():
  check()
  return {"time": time, "water_temp": water_temp, "water_level": water_level, "ph_state": ph_state, "light_intensity": light_intensity, "last_feed": last_feed}