import requests

files = open('메일 오류.png', 'rb')

upload = {'file': files}

res = requests.get(' http://127.0.0.1:8000/photo', files = upload)