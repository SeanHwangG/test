# coding: utf-8

from pickle import load, dump, HIGHEST_PROTOCOL
from xlrd import open_workbook
from url_to_words import url_to_words

def generateDict( category_number, EXCEL_FILE_NAME ):
    """
        단어의 빈도수를 저장하는 Dictionary를 만듬.
        예를들어 게임 사이트에서 "play"라는 단어가 5번 등장하고, "over" 이라는 단어가 3번 등장하면
        ["play" : 5, "over" : 3]
        또한 빈도수를 체크할때 같은 웹사이트가 두번 카운트 되지 않도록
        "URL" 이라는 key에서 모든 웹사이트 url이 list로 저장이 되있고,
        "URL_COUNT"  key에서는 url 갯수가 저장.

        :param category_number: 카테고리 번호 ex) 1, 44
        :param filename: 학습시킬 데이타가 담긴 엑셀 파일.
                         A 칼럼에는
    """

    book_r = open_workbook("data/" + EXCEL_FILE_NAME + ".xlsx")
    sheet_r = book_r.sheet_by_name(EXCEL_FILE_NAME)
    urls = [sheet_r.cell_value(r, 0) for r in range(sheet_r.nrows)]

    try:
        with open ('data/trans_' + str(category_number) + '.pkl', 'rb') as f:
            in_dict = load(f)
        print str(category_number) + "카테고리 dictionary 업데이트 중"
    except:
        print str(category_number) + "카테고리 dictionary 생성중"
        in_dict = {}
        in_dict["URL_COUNT"] = 0
        in_dict["URL"] = []

    for url in urls:
        # words = [선분류 카테고리, redirect 주소] + visible_string_list + ["META"] + meta_string_list
        words = url_to_words(url)

        # 웹사이트 안에 있는 단어가 10개 이하면 넘김
        if words[0] != category_number or len(words) < 12:
            continue

        # 이미 사전에 추가된 웹사이트는 넣지 않음
        if words[1] in in_dict["URL"]:
            print words[1] + " is duplicate!"
            continue
        else:
            in_dict["URL"].append(words[1])
            in_dict["URL_COUNT"] += 1

        for index, string in enumerate(words):
            # index 0 은 카테고리 번호고 index 1은 리다이렉트 주소기 때문에 X
            # 단어가 너무 길면 dictionary 에 추가 X
            if index < 2 or len(string) > 15:
                continue
            try:
                in_dict[string] += 1
            except:
                in_dict[string] = 1

    with open('data/trans_' + str(category_number) + '.pkl', 'wb') as f:
        dump(in_dict, f, HIGHEST_PROTOCOL)


if __name__ == "__main__":
    generateDict(1, 'data/trans_learning20001_30000.pkl')
