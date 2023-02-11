from flask import Blueprint, request
from werkzeug.utils import secure_filename

bp = Blueprint('image', __name__, url_prefix='/image')

# HTTP POST방식으로 전송된 이미지를 저장
@bp.route('/', methods=['POST'])
def save_image():
    f = request.files['file']
    f.save('./save_image/' + secure_filename(f.filename))
    return 'done!'