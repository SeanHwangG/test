# -*- coding: utf-8 -*-
def isEnglish(s):
    try:
        s.encode(encoding='utf-8').decode('ascii')
    except:
        return False
    else:
        return True

def trans_url_to_words(urls):
    special_chars = u"\"\'!@+#$ª%~¨ı}{>§<:º㎡¤¸㎏¬㎞³=_/»^`¿”&-–¾½¼«】“;【¹±▴▾¯?’¶⋁.「」（↑○|♥）©：》℃★■♡°·‘ⓒ™＞＜®…↓12345。�67890*\)\(,\[\]|"

    """

    NOTE:


    Args:
        urls (list) - list of urls 

    
    Output:
    
    -1  - not yet classified
    1   - warning
    44  - 응답하는 시간이 너무 오래 걸립니다 / Forbidden
    -3  - not available tumblr, blog, blogme or blogpost
    """
    import time
    import re
    import sys
    from bs4 import BeautifulSoup
    import grequests
    from googletrans import Translator

    urls = ['naver.com','daum.net', 'fomos.kr','google.com','facebook.com','warning.or.kr']

    for i, url in enumerate(urls):
        if "http" != url[:4]:
            urls[i] = "http://" + url
    results = grequests.map(grequests.get(u, stream=False, timeout=15) for u in urls)
    toreturn = []

    for i, page in enumerate(results):
        try:
            tran = Translator()
            soup = BeautifulSoup(page.text, 'html.parser')

            if "warning." in page.url:
                toreturn.append([1, urls[i]])
                continue

            for script in soup(["script", "style"]):
                script.extract()

            before_trans = soup.get_text()
            for char in special_chars:
                before_trans = before_trans.replace(char, ' ')
                before_trans = re.sub('\s+', ' ', before_trans)     # remove multiple whitespaces

            text = ""

            while len(before_trans) != 0:
                split = before_trans.split()
                before_trans = ""
                for word in split:
                    if len(word) < 2:
                        continue
                    if not word.isalpha():
                        before_trans = before_trans + word + " "
                    else:
                        text = text + word + " "
                n = 512


            '''            
            text = 
            n = 512
            while True:
                if n == 0:
                    break
                # Translator takes long, so
                try:
                    n_split = []
                    all_Translated = True
                    groups = string.split(' ')
                    string = ""

                    while len(groups):
                        n_split.append(' '.join(groups[:n]))
                        groups = groups[n:]

                    for j in xrange(len(n_split)):
                        for char in special_chars:
                            n_split[j] = n_split[j].replace(char, ' ')

                        if not isEnglish(n_split[j]):
                            n_split[j] = tran.translate(n_split[j]).text.lower()
                            # You have to translate again
                            if not isEnglish(n_split[j]):
                                all_Translated = False
                                string = string + n_split[j]
                            else:
                                print n_split[j]
                                text = text + n_split[j]
                        else:
                            text = text + n_split[j]

                    if not all_Translated:
                        raise
                        #print u'[' + u','.join([u"'" + unicode(i) + u"'" for i in text]) + u']'
                except:
                    n /= 2
                else:
                    break
            '''

            for char in special_chars:
                text = text.replace(char, ' ')

            text = [100, urls[i]] + [item.lower() for item in text.split() if len(item) > 1]

            # http://whatpornshouldiwatch.com/
            if len(text) > 4 and text[2] == "forbidden" and text[3] == "forbidden":
                text[0] = 44

            elif ".blogspot." in urls[i]:
                pass
            elif "clean.internet" in urls[i]:
                pass

            elif ".tumblr." in urls[i]:
                # http://korean.tumblr.com/
                if len(text) > 4 and text[2] == "not" and text[3] == "found":
                    text[0] = -3
                if len(text) > 5 and text[2] == "tumblr" and text[4] == "insign":
                    text[0] = -3

            # http://sfd.over-blog.com/
            elif ".over-blog." in urls[i]:
                if len(text) > 4 and text[2] == "erreur":
                    text[0] = -3

            # http://l.zeroloss.pro/
            elif len(text) > 4 and text[2] == "not" and text[3] == "found":
                text[0] = 44

            toreturn.append(text)
        except Exception as e:
            print 'Error on line {}'.format(sys.exc_info()[-1].tb_lineno), type(e).__name__, e
            toreturn.append([44, urls[i]])

    return toreturn

if __name__ == "__main__":
    import time
    ff= time.time()
    a = trans_url_to_words("sd")
    print time.time() - ff
    #www.proxtik.com
    for list in a:
        print u'[' + u','.join([u"'" + unicode(i) + u"'" for i in list]) + u']'
        print ""
        print ""
