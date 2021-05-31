# coding: utf-8
from googletrans import Translator
from re import sub, match
from textwrap import wrap
from bs4 import BeautifulSoup

def print_unicode_list(list):
    """ unicode의 List를 출력하는 함수 """
    print(u'[' + u','.join([u"'" + unicode(i) + u"'" for i in list]) + u']')

def print_unicode_dict(dict):
    """ unicode의 Dictionary를 출력하는 함수"""
    print('{%s}' % ',\n'.join("'%s': '%s'" % pair for pair in dict.iteritems()))

def ignore_common_words(string_list):
    """ String List에서 자주 쓰이는 자동분류에 의미 없는 단어들을 제거함.

    :param string_list: 단어를 제거할 리스트.
    :return: 의미 없는 단어가 제거된 리스트.
    """
    ignore_set = {
        'and', 'are',
        'by', 'but', 'be',
        'com', 'content', 'contents', 'css', 'co',
        'edge',
        'for',
        'google', 'get',
        'http', 'https', 'html', 'height', 'have',
        'in', 'it', 'is', 'index', 'ie',
        'javascript', 'jpg',
        'my',
        'no', 'not',
        'or', 'origin', 'on',
        'png',
        'self', 'so', 'size',
        'the', 'to', 'that', 'this', 'txt', 'text',
        'utf',
        'width', 'www',
        'you'
        }
    return [x for x in string_list if x not in ignore_set]

def remove_special_chars(string):
    """String에서 알파벳이(언어 불문) 아닌 특수문자를 제거하고 빈칸으로 바꿈
        ex) 황규@승 sfer"fwe rwer -> 황규 승 sfer fwe rwer
    """

    res = ""

    # 스트링이 ascii 인경우 unicode 로 바꿈
    if not isinstance(string, unicode):
        string = string.decode('utf-8')

    for ch in string:
        # 알파벳인지 체크
        if ch.isalpha():
            res += ch
        # 아니면 빈칸으로 바꿈
        else:
            res += ' '

    # 빈칸이 여러개 있거나 탭, 새로운 줄을 하나의 빈칸으로 바꿈
    res = sub('\s+', ' ', res)

    return res

# NOTE: 영어 알파벳으로 확인하는 함수기 때문에 알파벳을 쓰는 Spanish나 French는 True로 반환 될 수 있음.
def is_english(string):
    """ Input String이 오로지 영어로만 구성되있으면 True, 아니면 False
        ex) "english" - true
            "english한국" - false
    """
    return match(r'^[a-zA-Z]+\Z', string) is not None

def add_http_remove_m_from_url(url):
    """ URL에 http/ https를 붙이고 "m."(모바일 전용)을 제거함.
        ex) m.naver.com, http://google.com, https://m.daum.net/
    -> http://naver.com, http://google.com, https://daum.net/
    """

    if url[:8] == "https://" or url[:7] == "http://":
        url = url.split("//")[1]
    if "m." == url[:2]:
        url = url[2:]
    return "http://" + url

def extract_visible_text_from_html(HTML):
    """ HTML에서 실제로 보여지는 글자들을 반환

    :param html: HTML 파일
    :return: url 에서 보여지는 글자
    """
    soup = BeautifulSoup(HTML, 'html.parser')

    for script in soup(["script", "style"]):
        script.extract()
    return remove_special_chars(soup.get_text())


def translate_to_english(before_trans):
    """ 아무 언어 감지해서 영어로 번역

    :param before_trans(string): 번역 할 글자
    :return: 번역된 글자
    """

    translated = ""

    # 5번 이상 번역해도 번역 해야 될 string 이 남아있으면 무시.
    for i in range(5):
        before_trans = remove_special_chars(before_trans).lower()
        split = before_trans.split()
        before_trans = u""

        for str in split:
            # 한자리 글자는 무시
            if len(str) < 2:
                continue
            # 번역 되있으면 translated 에 저장
            elif is_english(str):
                translated += str + " "
            # 번역 안되있으면 before_trans 에 저장
            else:
                before_trans += str + " "

        # 번역이 다 됬으면 loop 종료
        if len(before_trans) == 0:
            break

        '''
        wrap(): string 을 한 리스트당 최대 "width" 글자가 되게 나눔.  // "한글str @" 는 총 7개의 글자

        예를들어,     before_trans = "I am a boy and you are a girl"
                      ->
                      n_split = ["I am a", "boy and", "you are", "a girl"]
        '''
        n_split = wrap(before_trans, width = 1450, break_long_words=False)

        for j in xrange(len(n_split)):
            tran = Translator()
            n_split[j] = tran.translate(n_split[j]).text.lower()
            before_trans += remove_special_chars(n_split[j])


    return translated.encode('ascii', 'ignore')

def pre_classify(url, title, string):
    """ warning.or, 404 Forbidden, 혹은 blog 포멧의 url 을 선분류.

    :param url: url
    :param title: title of the web page
    :param string: translated words in url
    :return: 선분류 카테고리 (1 - 성인, 44 - 확인불가, 45 - 블로그)
             -1  - 재분류 필요
             100 - 일반 웹사이트
    """
    if "403 Forbidden" == title or "404 Not Found" == title:
        return 44
    if ".vonvon." in url:
        return 6
    if "clean.internet." in url or "kids.kt." in url:
        return -1
    if "warning." in url:
        return 1
    if ".blogspot." in url:       # http://randomzzzzqqqq.blogspot.kr/
        if "Blog not found" == title:
            return 45
        return 45
    if ".tumblr" in url:
        if "safe-mode?" in url:     # https://tumblr.com/url=[http://homofucks.tumblr.com/]
            return 1
        if "Untitled" == title:     # https://randomqqqqqq.tumblr.com/
            return 45
        if "Not found." == title:   # https://randomzzzzqqqq.tumblr.com/
            return 45
        return 45
    if ".over-blog." in url:
        if "Erreur" == title:       # http://entrejambes.over-blog.com/
            return 45
        return 45
    if "blog.me" in url:            # http://sdfi23.blog.me/
        return 45

    return 100

def write_to_file():
    ''' pkl 로 된 파일을 읽을 수 있는 txt 로 변경 (파일 이름 바꾸세요) '''
    import pickle
    file = open('pkl.txt', 'w')
    with open('data/trans_1.pkl','rb') as f:
        a = pickle.load(f)
        print >> file, a
    file.close()

if __name__ == "__main__":
    print translate_to_english("네이버 %n 네이버 메인에서 다양한 정보와 유용한 컨텐츠를 만나 보세요")