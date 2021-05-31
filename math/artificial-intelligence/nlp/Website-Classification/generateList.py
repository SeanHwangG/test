# coding: utf-8

from xlrd import open_workbook
from openpyxl import load_workbook
from url_to_words import url_to_words
from pickle import dump, HIGHEST_PROTOCOL
from gc import collect

sheet_name = "kim"

book_r = open_workbook("data/" + sheet_name + ".xlsx")
sheet_r = book_r.sheet_by_name(sheet_name)
book_w = load_workbook("data/" + sheet_name + ".xlsx")
sheet_w = book_w.get_sheet_by_name(sheet_name)

def generateList(fromI, toI):
    """
    Excel 첫번째 줄에 url, 두번째 줄에 category.

    Note:
        - Remove duplicates from excel. "m.naver.com/", "www.naver.com/", "naver.com/"
        - URL must be ends with slash (google.com/)
        - You may or may not include http or https
        - sheet name and excel file name must be same

    Args:
        sheet_name (str): the name of excel file or sheet name
        fromI/toI (int): the range of urls

    Returns:

    Output:

    -1  - not yet classified
    1   - warning
    44  - 응답하는 시간이 너무 오래 걸립니다 / Forbidden
    """

    urls = [sheet_r.cell_value(r, 0) for r in range(fromI, toI + 1)]
    cate = [sheet_r.cell_value(r, 1) for r in range(fromI, toI + 1)]

    words_list = []

    for index, url in enumerate(urls):
        try:
            words_in_url = url_to_words(url)
        except:
            continue

        if words_in_url[0] == 100:
            words_in_url[0] = cate[index]

        sheet_w["D" + str(fromI + index)] = words_in_url[0]

        collect()

    #book_w.save("data/" + sheet_name + ".xlsx")
    with open('data/wordslist_all_alexa.pkl', 'wb') as f:
        dump(words_list, f, HIGHEST_PROTOCOL)

if __name__ == "__main__":
    for x in range(1, 2):
        generateList(x * 1000 - 999, x * 1000)