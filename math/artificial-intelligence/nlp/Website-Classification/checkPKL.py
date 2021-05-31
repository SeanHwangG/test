from googletrans import Translator
from pickle import load, dump, HIGHEST_PROTOCOL
from trans_url_to_words import isEnglish
special_chars = u"\"\'!@+#$%~}{><:=_/^`”&-–】“;【▴▾?’⋁.「」（↑○|♥）©：》℃★■♡°·‘ⓒ™＞＜®…↓12345。�67890*\)\(,\[\]|"

def checkPKL(pkl_loc):

    with open(pkl_loc, 'rb') as f:
        urls = load(f)
    for i, check in enumerate(urls):
        result = [check[0], check[1]]
        check = check[2:]
        string = ""
        for word in check:
            if isEnglish(word):
                result.append(word)
            else:
                string += (word + " ")

        tran = Translator()

        n = 100
        n_split = []
        groups = string.split(' ')
        while len(groups):
            n_split.append(' '.join(groups[:n]))
            groups = groups[n:]
        text = []

        # First Translation with 100 words
        for j in xrange(len(n_split)):
            if not isEnglish(n_split[j]):
                n_split[j] = tran.translate(n_split[j]).text.lower()
            for char in special_chars:
                n_split[j] = n_split[j].replace(char, ' ')
            text = text + n_split[j].split()

        # Second Translation for each word
        for k in xrange(len(text)):
            if not isEnglish(text[k]):
                text[k] = tran.translate(text[k]).text

        urls[i] = result + [item.lower() for word in text for item in word.split(' ') if len(item) > 1]

    for url in urls:
        print url

checkPKL("data/wordslist_alexa1_1000.pkl")