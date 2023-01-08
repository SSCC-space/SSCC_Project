import requests
import re
from bs4 import BeautifulSoup
url = 'http://prod.danawa.com/list/?cate=112758&15main_11_02'
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.127 Safari/537.36'}
res = requests.get(url, headers=headers)
res.raise_for_status()
soup = BeautifulSoup(res.text, 'lxml') #가져온 문서를 lxml 객체로 만듦
print(soup)