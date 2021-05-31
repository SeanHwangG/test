{% tabs %}
{% tab title='HR_s10-standard-deviation.md' %}

> Question

* Print standard deviation of given array up to 1st decimal

```txt
Input:
5
10 40 30 50 20

Output: 14.1
```

{% endtab %}
{% tab title='HR_s10-standard-deviation.py' %}

```py
import statistics as stats

N = int(input())
X = list(map(int, input().split()))

print(f"{stats.pstdev(X):.1f}")
```

{% endtab %}
{% endtabs %}
