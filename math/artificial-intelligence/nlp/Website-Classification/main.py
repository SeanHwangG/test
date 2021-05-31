# coding: utf-8

from openpyxl import load_workbook
from xlrd import open_workbook
from score_one_website import score_one_website
from string import ascii_uppercase
from url_to_words import url_to_words

# 엑셀 파일 / 파일 내에 Sheet 이름
EXCEL_FILE_NAME = "10122017"
EXCEL_SHEET_NAME = "10122017"

# 엑셀을 읽어주는 변수
book_r = open_workbook("data/" + EXCEL_FILE_NAME + ".xlsx")
sheet_r = book_r.sheet_by_name(EXCEL_SHEET_NAME)

# 엑셀에 쓸 수 있게 하는 변수
book_w = load_workbook("data/" + EXCEL_FILE_NAME + ".xlsx")
sheet_w = book_w.get_sheet_by_name(EXCEL_SHEET_NAME)

# EXCEL_ROW = ['A','B','C', ..., 'Z', 'AA', 'AB', ..., 'AZ']
EXCEL_ROW = list(ascii_uppercase) + ['A' + b for b in ascii_uppercase]

def main():
    """ 엑셀파일에 있는 URL 들을 자동분류함.

        input:
        A 칼럼 - URL 주소들.

        result:
        B 칼럼 - 선 분류 카테고리
        C 칼럼 - 단어 수
        D 칼럼 - redirect 된 주소 ("www." 항시 제거)
        E 칼럼 ~ AD 칼럼 - 각 카테고리에 매칭 점수
    """
    print str(sheet_r.nrows) + "개의 웹사이트 자동분류 시작"

    # 엑셀 A칼럼 읽어준 후, url들을 list로 반환
    # NOTE: range(sheet_r.nrows) 에 1000 넣으면 처음 1000개만 자동분류함.
    #       한번에 10000개 이하 권장 (RAM 8기가 기준, 메모리 에러남)
    urls = [sheet_r.cell_value(r, 0) for r in range(sheet_r.nrows)]

    for i in range(len(urls)):
        # words = [선분류 카테고리, redirect 주소] + visible_string_list + ["META"] + meta_string_list
        words = url_to_words(urls[i])
        sheet_w['B' + str(i + 1)] = words[0]
        sheet_w['C' + str(i + 1)] = len(words)
        sheet_w['D' + str(i + 1)] = words[1]

        print len(words), "words in", str(i) + "th website:", urls[i]

        for j, score in enumerate(score_one_website(words)):
            # 점수를 엑셀에 기록
            # EXCEL_ROW[4] 는 E 칼럼.
            sheet_w[EXCEL_ROW[j + 4] + str(i + 1)] = score

        # 프로그램 중간에 에러날 수 있으니 수시로 저장.
        # NOTE 1: 저장 도중 엑셀이 열려있으면 프로그램 종료됨 (Permission Error)
        #  -> 확인하고 싶으면 자동분류 중인 엑셀 복사한후 복사한 파일을 본다.
        # NOTE 2: 저장 도중 프로그램을 종료하면 엑셀 파일이 망가짐
        #  -> 자동분류 전에 항상 copy file 만들어 놓는다.
        #  -> i가 100의 배수 가까워지면 절때 종료하지 않는다.
        if i % 100 == 0:
            print "저장중"
            book_w.save("data/" + EXCEL_FILE_NAME + ".xlsx")

    print "저장중"
    book_w.save("data/" + EXCEL_FILE_NAME + ".xlsx")

if __name__ == "__main__":
    main()
