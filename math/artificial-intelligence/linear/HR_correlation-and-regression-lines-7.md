{% tabs %}
{% tab title='HR_correlation-and-regression-lines-7.md' %}

> Question

```txt
Input:
15 12 8 8 7 7 7 6 5 3
10 25 17 11 13 17 20 13 9 15
Output: 0.208
```

{% endtab %}
{% tab title='HR_correlation-and-regression-lines-7.py' %}

```py
import math
x, y = list(map(int, input().split())), list(map(int, input().split()))
x = [a - sum(x) / len(x) for a in x]
y = [a - sum(y) / len(y) for a in y]
slope = sum([a * b for a, b in zip(x, y)]) / sum([a * a for a in x])
print(f"{slope:.3f}")
```

{% endtab %}
{% endtabs %}
