{% tabs %}
{% tab title='KT_chanukah.md' %}

> Question

* for each day n light is needed
* determines how many candles would be necessary for a Chanukah holiday lasting for a given number of days

```txt
Input:
3
1 8
2 1
3 10

Output:
1 44
2 2
3 65
```

{% endtab %}
{% tab title='KT_chanukah.py' %}

```py
n_test = int(input())
for i in range(n_test):
  t, n = map(int, input().split())
  print(t, n + (n * (n + 1)) // 2)
```

{% endtab %}
{% endtabs %}
