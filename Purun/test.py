import requests
import json

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

check()

datas = [{
  "time": time, "water_temp": water_temp, "water_level": water_level, "ph_state": ph_state, "light_intensity": light_intensity, "last_feed": last_feed
}]

url = "http://114.71.48.94:8080/nCnt"

response = requests.post(url, data = datas)