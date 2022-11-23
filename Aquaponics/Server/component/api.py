from fastapi import Depends, APIRouter, status
import sys

from utils.ManageData import *
from pydantic import BaseModel
from typing import Optional

sys.path.append("..")
router = APIRouter(prefix="/api", tags=["api"])


@router.get("/data")
async def GetterDate(count: int = -1):
    return SelectData(query="SELECT * FROM AQUA_PONICS_TB", option=f"ORDER BY ID DESC") if count == -1 else \
        SelectData(query="SELECT * FROM AQUA_PONICS_TB", option=f"ORDER BY ID DESC LIMIT {count}")


@router.get("/control/{module}")
async def ControlModule(module: str):
    UpdateModuleData(module)


@router.get("/check")
async def CheckControl():
    return GetModuleData()


class Item(BaseModel):
    TEMP: Optional[float] = -1
    PH: Optional[float] = -1
    WATER_LEVEL: Optional[int] = -1


@router.post("/data", status_code=status.HTTP_201_CREATED)
def update_item(item: Item):
    InsertData(item)
