# coding: utf-8

from pickle import load
from collections import Counter
from math import log10
from url_to_words import url_to_words

# List of Dictionary. dict_list[0] -> 성인 키워드.
dict_list = []

# Dictionary 랑 비슷한 형식, 여러개의 Dictionary 를 합칠때 이용됨.
dict_other = Counter()

# 자동분류할 카테고리 리스트
category = [1, 2, 3, 5, 10, 12, 15, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36, 46]

# 모든 dictionary 를 합쳐서 dict_other 을 만듬
# ex) trans_1 = {'a': 1, 'b': 2}, trans2 = {'b': 3, 'c':4} -> dict_other = {'a': 1,'b': 5, 'c': 4}
for cate in category:
    with open('data/trans_' + str(cate) + '.pkl', 'rb') as f:
        category_dict = load(f)
    dict_list.append(category_dict)
    dict_other += Counter(category_dict)

dict_other = dict(dict_other)

def score_one_website(words):
    '''

    :param words:
    '''

    # score_list 의 초기 값을 [1, 1, ..., 1] 로 설정 (카테고리 개수만큼의 1 리스트)
    score_list = [1 for x in range(len(category))]

    # 카테고리, url 뺀 나머지중, 중복 제거 된 단어들
    words = set(words[2:])

    for i, cate in enumerate(category):
        # dict_other 은 모든 카테고리를 합친 것이므로, value 들이 큼.
        # 따라서 각 카테고리별로 weight 을 구해서 그만큼 곱해줌으로, dict_other 과 value 를 맞춤.
        weight = (dict_other["URL_COUNT"] - dict_list[i]["URL_COUNT"]) / dict_list[i]["URL_COUNT"]
        for string in words:
            # 단어가 META 인 경우는 넘김
            if string == "META":
                pass

            # get 함수는 key 값에 맞는 value 를 반환
            # 두번째 parameter 에 0 은 key 값이 사전에 존재하지 않을때의 기본값.
            porn = dict_list[i].get(string, 0) * weight + 1
            other = dict_other.get(string, 0) - dict_list[i].get(string, 0) + 1

            # dictionary 에 아예 저장되 있지 않은 단어를 발견하면, 점수를 낮춤.
            if porn == 1 and other == 1:
                score_list[i] *= 0.3

            score_list[i] *= float(porn) / other

        # 점수가 너무 커지면 무한이 되는데, 그 경우 350으로 변환.
        if score_list[i] == float("inf"):
            score_list[i] = 350

        # 점수가 너무 낮아지면 0이 되는데, 그 경우 -350으로 변환.
        elif score_list[i] == 0:
            score_list[i] = -350

        # 로그 base 10 씌우고 0.1의 자리로 반올림
        else:
            score_list[i] = round(log10(score_list[i]), 1)

    return score_list

if __name__ == "__main__":
    urls = [ 'cesmac.edu.br/']
    for url in urls:
        print score_one_website(url_to_words(url))