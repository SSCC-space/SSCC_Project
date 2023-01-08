from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
# 사용에 아무런 의미가 없음 걍 쓴거임.
import undetected_chromedriver as uc

# 대기 시간 1초
LOADING_WAIT_TIME= 1
# 크롤링할 상품 코드
# num = ['0', '1', '2', '3', '4', '5', '6', '7', '8' ,'9']
Kind = ['CPU', 'MainBoard', 'Cooler', 'Ram', 'SSD', 'Power', 'Case']
pcodes = ['18038831', '18265187', '16525058', '15759071', '13276568', '18087947', '7924210']
Product = []
# 결과 리스트
result = []
price = []


def init_driver():
    driver = uc.Chrome(use_subprocess=True)
    return driver

def find_name(pcode, driver):
    url = f'http://prod.danawa.com/info/?pcode={pcode}'
    driver.get(url)
    num = 0
    for name in driver.find_elements(By.CLASS_NAME, 'title'):
        print(name.text)
        Product.append(name.text)
        num += 1
        if num == 2:
            break


def find_price(pcode, driver):
    url = f'http://prod.danawa.com/info/?pcode={pcode}'
    driver.get(url)
    for price in driver.find_elements(By.CLASS_NAME,'lwst_prc'):
        result.append(price.text)
# if __name__ == "__main__":
#     driver = init_driver()
#     for pcode in pcodes:
#         find_price(pcode, driver)
#         price.append(result[1])
#         result = []
#     # print(len(result))
#     sum = 0
#     for r in range(0, len(Kind)):
#         print("{0}: {1}".format(Kind[r], price[r]))
#         price[r] = price[r].replace(",", "")
#         price[r] = price[r].strip("원")
#         sum += int(price[r])
    
#     print("======================")
#     print("총 가격: {0}원".format(format(sum,',')))

if __name__ == "__main__":
    driver = init_driver()
    for pcode in pcodes:
        find_name(pcode, driver)