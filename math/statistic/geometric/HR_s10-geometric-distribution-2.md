{% tabs %}
{% tab title='HR_s10-geometric-distribution-2.md' %}

> Question

* The probability that a machine produces a defective product is 1/3
* What is the probability that 1st defect is found during the first 5 inspections?

```txt
Input:
1 3
5

Output: 0.868
```

{% endtab %}
{% tab title='HR_s10-geometric-distribution-2.py' %}

```py
frac = list(map(int, input().split()))
p = frac[0] / frac[1]
n = int(input())
q = 1 - p
print(round(1 - q ** n,3))
```

{% endtab %}
{% endtabs %}
