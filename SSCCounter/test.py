from fastapi import FastAPI, File, UploadFile
import os
from datetime import datetime

app = FastAPI()

@app.get("/photo")
async def upload_photo(file: UploadFile):
    UPLOAD_DIR = "./photo"  # 이미지를 저장할 서버 경로
    
    content = await file.read()
    filename = f"{str(datetime.now())[:10]}.jpg"  # uuid로 유니크한 파일명으로 변경
    with open(os.path.join(UPLOAD_DIR, filename), "wb") as fp:
        fp.write(content)  # 서버 로컬 스토리지에 이미지 저장 (쓰기)

    return {"filename": filename}