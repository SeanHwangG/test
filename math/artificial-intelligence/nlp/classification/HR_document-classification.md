{% tabs %}
{% tab title='HR_document-classification.md' %}

> Question

* [Full Train](https://s3.amazonaws.com/hr-testcases/597/assets/trainingdata.txt)

```txt
Input:
5485
1 champion products ch approves stock split champion products inc said its board of directors approved a two for ...
2 computer terminal systems cpml completes sale computer terminal systems inc said it has completed the sale of ...
1 cobanco inc cbco year net shr cts vs dlrs net vs assets mln vs mln deposits mln vs mln loans mln vs mln note th ...

Output:
```

{% endtab %}
{% tab title='HR_document-classification.py' %}

```py
from sklearn.svm import LinearSVC
from sklearn.feature_extraction.text import HashingVectorizer
transformer = HashingVectorizer(stop_words='english')

trains, labels = [], []
with open('trainingdata.txt') as f:
  for i in range(int(f.readline())):
    s = f.readline().rstrip()
    idx = s.find(' ')
    trains.append(s[idx+1:])
    labels.append(int(s[:idx]))
train = transformer.fit_transform(trains)
svm = LinearSVC()
svm.fit(train, labels)
_test = []
for i in range(int(input())):
  s = input().rstrip()
  _test.append(s)
test = transformer.transform(_test)
print(*svm.predict(test), sep='\n')
```

{% endtab %}
{% endtabs %}
