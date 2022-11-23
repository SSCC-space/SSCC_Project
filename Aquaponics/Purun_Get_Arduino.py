# -*- coding: utf-8 -*-

# ====================== Set ======================
import serial  # 아두이노 Serial 통신
from datetime import datetime

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

water_temp, water_level, ph_state, light_intensity, last_feed = round(20.013, 2), 500, round(7.032,2), 532, False

def memo(water_temp, water_level, ph_state, light_intensity, last_feed):
  with open("Purun.txt", "w", encoding = "utf8") as report_file:
        report_file.write("{0}/{1}/{2}/{3}/{4}/{5}".format(datetime.today().strftime("%Y-%m-%d %H:%M:%S"), water_temp, water_level, ph_state, light_intensity, last_feed))

# port = serial.Serial("/dev/ttyUSB0", "9600")

while True:
  try:
    # water_level = port.readline()
    try:
      water_level = water_level.decode()
    except:
      water_level = water_level
    print("water_level: ")
    print(water_level)
  except KeyboardInterrupt:
    break
  memo(water_temp, water_level, ph_state, light_intensity, last_feed)
# port.close()

