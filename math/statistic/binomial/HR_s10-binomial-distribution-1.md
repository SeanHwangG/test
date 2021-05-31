{% tabs %}
{% tab title='HR_s10-binomial-distribution-1.md' %}

> Question

* The ratio of boys to girls for babies born is 1.09:1
* What's proportion of families with exactly 6 children will have at least 3 boyes?

```txt
Input: 1.09 1
Output: 0.696
```

{% endtab %}
{% tab title='HR_s10-binomial-distribution-1.py' %}

```py
from math import comb

def binomial(x, n, p):
  return comb(n, x) * p ** x * (1 - p) ** (n - x)

l, r = map(float, input().split())
odds = l / r
print(round(sum([binomial(i, 6, odds / (1 + odds)) for i in range(3, 7)]), 3))
```

{% endtab %}
{% endtabs %}
