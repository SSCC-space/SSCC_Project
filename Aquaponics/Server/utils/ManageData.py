import sqlite3

from utils.STATUS_CODE import *
from utils.TimeFormmat import now

conn = sqlite3.connect("SSCC.db", check_same_thread=False)
conn.row_factory = sqlite3.Row
cur = conn.cursor()
# 아쿠아포닉스 전체 데이터 저장
conn.execute(
    'CREATE TABLE IF NOT EXISTS AQUA_PONICS_TB (ID INTEGER PRIMARY KEY AUTOINCREMENT, TIMESTAMP TEXT, TEMP FLOAT, PH FLOAT, WATER_LEVEL INT, LED INT, FEED INT)'
)

# 아쿠아포닉스 모듈 데이터 저장
AQUA_PONICS_LED = 0
AQUA_PONICS_FEED = 0


def UpdateModuleData(module):
    global AQUA_PONICS_LED, AQUA_PONICS_FEED
    # LED On/Off
    if module.upper() == "LED":
        AQUA_PONICS_LED = 1 - AQUA_PONICS_LED
        ACCESS_MOUDLE(module=module, state=AQUA_PONICS_LED)
    # Feed
    elif module.upper() == "FEED":
        AQUA_PONICS_FEED = 1
        ACCESS_MOUDLE(module=module, state=AQUA_PONICS_FEED)
    else:
        ERROR_CANT_ACCESS_MOUDLE(module=module, state="Not Found Module")


def GetModuleData():
    global AQUA_PONICS_LED, AQUA_PONICS_FEED
    postData = {"LED": AQUA_PONICS_LED, "FEED": AQUA_PONICS_FEED}
    AQUA_PONICS_LED, AQUA_PONICS_FEED = 0, 0
    return postData


def SelectData(**props):
    cur.execute(props["query"] + " " + (props["option"] if "option" in props else ""))
    return cur.fetchall()


def InsertData(data):
    try:
        cur.execute(
            'INSERT INTO AQUA_PONICS_TB (TIMESTAMP, TEMP, PH, WATER_LEVEL, LED, FEED) VALUES (?, ?, ?, ?, ?, ?)',
            (now(cur), data.TEMP, data.PH, data.WATER_LEVEL, AQUA_PONICS_LED, AQUA_PONICS_FEED)
        )
        conn.commit()
        SAVE_DATA_FROM_DB()
    except:
        ERROR_CANT_SAVE_DATA_FROM_DB(error="Posted Data Type Error")
