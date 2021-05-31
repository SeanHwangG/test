{% tabs %}
{% tab title='HR_the-trigram.md' %}

> Question

* Print most frequent trigram in the text, first one in case of tie

```txt
Input: I came from the moon. He went to the other room. She went to the drawing room.
Output: went to the
```

{% endtab %}
{% tab title='HR_the-trigram.py' %}

```py
import sys
from collections import Counter
from functools import reduce
from operator import iconcat

def getTrigrams(sentence):
  words = sentence.split()
  return [" ".join(words[i:i+3]) for i in range(len(words)-2)]

txt = sys.stdin.read()
trigrams = Counter(reduce(iconcat, map(getTrigrams, txt.lower().split('.')), []))
print(max(trigrams, key=trigrams.get))
```

{% endtab %}
{% endtabs %}
