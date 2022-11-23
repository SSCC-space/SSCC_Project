# ============ Set ============

# -*- coding: utf-8 -*-
from flask import Flask, render_template 
import numpy as np
from datetime import datetime
# ============ Machine ============ 

# 웹 출력    
app = Flask(__name__)

@app.route('/')
def OUTPUT():
    return '현재 점검중입니다.'
    
if __name__ == '__main__':
    app.debug = True
    app.run(host='0.0.0.0')