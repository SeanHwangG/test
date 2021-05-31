# coding: utf-8
from selenium import webdriver
from helper import *
from selenium.webdriver.common.by import By
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support.expected_conditions import presence_of_element_located
from gc import collect
from time import sleep

'''
100  - not yet classified
-1   - 페이지 로드하는데 오래걸리거나, clean internet으로 redirect됨
44   - 403 Forbidden / 404
'''

options = webdriver.ChromeOptions()
# 실제로 브라우저가 켜지는게 보이지 않음
options.add_argument('headless')
# 팝업 차단
options.add_argument("--disable-popup-blocking")
# 로그가 남지 않음
options.add_argument("--incognito")

driver = webdriver.Chrome(executable_path="./chrome_driver", chrome_options=options)

# 20초가 지나도 열리지 않을시, TimeoutException 이 걸림.
driver.set_page_load_timeout(30)

def url_to_words(url):
    """ 웹사이트에 보여지는 단어들과 메타 테그 단어들을 긁어 낸뒤 영어로 번역한다.

    :param url: url - ex) m.naver.com, http://google.com, https://daum.net/
    :return: [선분류 카테고리, redirect 주소] + visible_string_list + ["META"] + meta_string_list
    """
    global driver

    url = add_http_remove_m_from_url(url)

    try:
        driver.get(url)
        sleep(5)
        WebDriverWait(driver, timeout=30).until(presence_of_element_located((By.TAG_NAME, "body")))

        # redirect 된 주소로 변경.
        url = driver.current_url
        visible_strings = extract_visible_text_from_html(driver.find_element_by_tag_name("body").text)
        title = driver.title
    except TimeoutException:
        # 크롬 다 닫고 다시 크롬 킴. 안그러면 계속 이 웹사이트 열리기를 기다림.
        driver.quit()
        driver = webdriver.Chrome(executable_path="./chrome_driver", chrome_options=options)
        driver.set_page_load_timeout(30)
        return [-1, url]
    except:
        return [44, url]
    finally:
        # url에 "www." 제거 (Exception 뜰 때도 제거됨)
        url = url.replace("www.", "")

    # meta contents 빼오는 코드
    meta_strings = ""
    try:
        for item in driver.find_elements_by_xpath("//meta"):
            meta_strings += (remove_special_chars(item.get_attribute("content")) + " ")
    except:
        # 메타태그가 존재하지 않을때는 넘김
        pass

    visible_string_list = translate_to_english(visible_strings).split()
    meta_string_list = translate_to_english(meta_strings).split()

    # NOTE:  - "and", "to", "for", "http" 이런 단어들은 무시함.
    #        -  2자 ~ 15자의 단어만 저장함.
    text = [pre_classify(url, title, ""), url]\
           + [j for j in ignore_common_words(visible_string_list) if 15 > len(j) > 1]\
           + ["META"]\
           + [k for k in ignore_common_words(meta_string_list) if 15 > len(k) > 1]

    # 불필요한 메모리 정리
    collect()

    return text

if __name__ == "__main__":
    urls = ['http://facebook.com/']
    for url in urls:
        print url_to_words(url)