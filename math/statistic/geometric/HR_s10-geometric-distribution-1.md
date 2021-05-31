{% tabs %}
{% tab title='HR_s10-geometric-distribution-1.md' %}

> Question

* probability that a machine produces a defective product is 1/3.
* What is the probability that the 1st defect is found during the 5th inspection?

```txt
Input:
1 3
5

Output: 0.066
```

{% endtab %}
{% tab title='HR_s10-geometric-distribution-1.py' %}

```py
probability = list(map(int, input().split()))
p = probability[0] / probability[1]
q, n = 1 - p, int(input())

print(round(q ** (n - 1) * p, 3))
```

{% endtab %}
{% endtabs %}
