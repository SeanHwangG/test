{% tabs %}
{% tab title='HR_s10-normal-distribution-2.md' %}

> Question

* grades for a exam taken by students have a mean of 70 and a STD of 10, find probabilities
* higher than 80, 60 / lower than 60

```txt
Input: 70 10

Output:
80
60
```

{% endtab %}
{% tab title='HR_s10-normal-distribution-2.py' %}

```py
import math
mean, std = 70, 10
cdf = lambda x: 0.5 * (1 + math.erf((x - mean) / (std * (2 ** 0.5))))

print(round((1 - cdf(80)) * 100, 2))
print(round((1 - cdf(60)) * 100, 2))
print(round((cdf(60)) * 100, 2))
```

{% endtab %}
{% endtabs %}
