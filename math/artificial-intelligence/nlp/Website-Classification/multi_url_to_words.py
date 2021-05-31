# coding: utf-8
from helper import *
import grequests
from time import time
from gc import collect

def multi_url_to_words(urls):
    """ extract all visible words contained in each URLs.

    :param urls: list of URLs (ex ['naver.com', 'm.google.com', 'http://daum.net']
    :return: list of list. Each URL will be converted into a list which
    :        [ category #, redirected url, [word1], [word2] ... ]
    """

    for i, url in enumerate(urls):
        urls[i] = add_http_remove_m_from_url(url)

    # stream=False
    results = grequests.map(grequests.get(u, stream=False, timeout=15) for u in urls)
    grequests.encoding = 'utf-8'
    to_return = []

    for i, page in enumerate(results):
        # Just showing crawling is being done.
        if i % 200 == 0:
            print str(i) + "is done"
        try:
            # change this line, if you don't want to translate.
            string = translate_to_english(extract_visible_text_from_html(page.text))
            text = [pre_classify(page.url), page.url] + [j for j in string.split() if 15 > len(j) > 1]

            to_return.append(text)
        # cannot load page
        except AttributeError as e:
            to_return.append([44, urls[i]])
        finally:
            collect()

    return to_return

if __name__ == "__main__":
    se= time()
    a = multi_url_to_words("sd")
    #www.proxtik.com
    for list in a:
        print_unicode_list(list)
        print ""
        print ""
    print time() -se
    #a = multi_url_to_words("http://homofucks.tumblr.com")