{% tabs %}
{% tab title='HR_s10-weighted-mean.md' %}

> Question

* Given values and weights, printed weighted mean

```txt
Input:
5
10 40 30 50 20
1 2 3 4 5

Output: 32.0
```

{% endtab %}
{% tab title='HR_s10-weighted-mean.py' %}

```py
size = int(input())
numbers = list(map(int, input().split()))
weighted = list(map(int, input().split()))

sum_items = 0
for i in range(size):
  sum_items = sum_items + (numbers[i] * weighted[i])

print(round(sum_items / sum(weighted), 1))
```

{% endtab %}
{% endtabs %}
