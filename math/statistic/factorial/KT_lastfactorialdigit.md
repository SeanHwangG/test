{% tabs %}
{% tab title='KT_lastfactorialdigit.md' %}

> Question

* print last digit of factorial

```txt
Input:
3
1
2
3

Output:
1
2
6
```

{% endtab %}
{% tab title='KT_lastfactorialdigit.py' %}

```py
n_test = int(input())
for _ in range(n_test):
  n = int(input())
  ret = 1
  for i in range(1, n + 1):
    ret *= i
  print(ret % 10)
```

{% endtab %}
{% endtabs %}
