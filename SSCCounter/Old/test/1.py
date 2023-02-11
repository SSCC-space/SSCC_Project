import requests

files = open('photo.jpg', 'rb')

upload = {'file': files}

res = requests.get(' http://127.0.0.1:8000/photo', files = upload)