# Python 3

from math import log10

def check( excel_loc, sheet_name ):
    import urllib3
    urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)
    from openpyxl import load_workbook
    import pickle

    book_w = load_workbook(excel_loc)
    sheet_w = book_w.get_sheet_by_name(sheet_name)

    '''If you have list.pkl '''
    with open('data/wordslist_' + sheet_name + '.pkl', 'rb') as f:
        urlList = pickle.load(f)

    with open('data/dict_porn.pkl', 'rb') as f:
        dict_porn = pickle.load(f)

    with open('data/dict_other.pkl', 'rb') as g:
        dict_other = pickle.load(g)

    print("dict was successful")

    for index, string_list in enumerate(urlList):
        if index < 20000:
            continue
        score = [0, 0, 0, 0, 0, 0, 1, 1, 1]
        string_list = set(string_list)

        for string in string_list:
            string = string.lower()
            try:
                porn = dict_porn[string] + 1
            except:
                porn = 1
            try:
                other = dict_other[string] + 1
            except:
                other = 1

            score[8] *= float(porn)/(other)

        score[0] = len(string_list)

        if score[0] != 0:
            for x in range(1, 6):
                score[x] /= float(score[0])

        for x in range(6,9):
            if score[x] == float("inf"):
                score[x] = 350
            elif score[x] == 0:
                score[x] = -350
            else:
                score[x] = log10(score[x])


        # 67 is C
        for x in range(0, 9):
            sheet_w[chr(67+ x)+str(index+1)]= score[x]
        if index % 300 == 5:
            print index
            book_w.save(excel_loc)
    book_w.save(excel_loc)

if __name__ == "__main__":
    check( "data/porn.xlsx", "porn" )
    check( "data/other.xlsx", "other" )
