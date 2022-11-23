from fastapi import FastAPI, Depends
from component import api

app = FastAPI()
app.include_router(api.router)