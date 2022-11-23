from fastapi import HTTPException


def ERROR_CANT_ACCESS_MOUDLE(**props):
    raise HTTPException(status_code=400, detail={"module": props["module"], "state": props["state"]})


def ACCESS_MOUDLE(**props):
    raise HTTPException(status_code=201, detail={"module": props["module"], "state": props["state"]})


def ERROR_CANT_SAVE_DATA_FROM_DB(**props):
    raise HTTPException(status_code=400, detail={"error:": props["error"]})

def SAVE_DATA_FROM_DB(**props):
    raise HTTPException(status_code=201, detail="Save Senser Data")


LED_STATE = {
    0: "off",
    1: "on"
}


def MODULES_ACCESS(**props):
    # print(props)
    if "led_state" in props:
        raise HTTPException(status_code=200, detail=LED_STATE[props["led_state"]])
    raise HTTPException(status_code=200, detail="Item not found")


def MODULES_DENIED():
    raise HTTPException(status_code=400, detail="Item not found")
