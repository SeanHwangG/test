{% tabs %}
{% tab title='HR_s10-normal-distribution-1.md' %}

> Question

* time taken to assemble a car is a random variable, X having a normal distribution mean = 20 hours, STD = 2 hours
* What is the probability that a car can be assembled at this plant in:
  * Less than 19.5 hours?
  * Between 20 and 22 hours?

```txt
Input:
20 2
19.5
20 22

Output:
0.401
0.341
```

{% endtab %}
{% tab title='HR_s10-normal-distribution-1.py' %}

```py
import math
mean, std = 20, 2
cdf = lambda x: 0.5 * (1 + math.erf((x - mean) / (std * (2 ** 0.5))))

print(f'{cdf(19.5):.3f}')         # Less than 19.5
print(f'{cdf(22) - cdf(20):.3f}') # Between 20 and 22
```

{% endtab %}
{% endtabs %}
