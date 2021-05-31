{% tabs %}
{% tab title='HR_s10-mcq-2.md' %}

> Question

* Two toss of six-sided dice, find probability that values rolled by each die will be different and two dice sum to 6

```txt
Output: 1/9
```

{% endtab %}
{% tab title='HR_s10-mcq-2.py' %}

```py
from fractions import Fraction
poss = 0

for d1 in range(1, 7):
  for d2 in range(1, 7):
    if d1 != d2 and d1 + d2 == 6:
      poss += 1
      print(f"{d1} + {d2} = {d1 + d2}")

print(f"Probability: {Fraction(poss, 36)}")
```

{% endtab %}
{% endtabs %}
