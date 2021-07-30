{% tabs %}
{% tab title='KT_detaileddifferences.md' %}

> Question

* Print . if two character are same, else *

```txt
Input:
3
ATCCGCTTAGAGGGATT
GTCCGTTTAGAAGGTTT
abcdefghijklmnopqrstuvwxyz
bcdefghijklmnopqrstuvwxyza
abcdefghijklmnopqrstuvwxyz0123456789
abcdefghijklmnopqrstuvwxyz0123456789

Output:
ATCCGCTTAGAGGGATT
GTCCGTTTAGAAGGTTT
*....*.....*..*..

abcdefghijklmnopqrstuvwxyz
bcdefghijklmnopqrstuvwxyza
**************************

abcdefghijklmnopqrstuvwxyz0123456789
abcdefghijklmnopqrstuvwxyz0123456789
....................................

```

{% endtab %}
{% tab title='KT_detaileddifferences.py' %}

```py
N = int(input())
for _ in range(N):
  st1 = input()
  st2 = input()
  print(st1)
  print(st2)
  for c1, c2 in zip(st1, st2):
    if c1 == c2:
      print('.', end='')
    else:
      print('*', end='')
  print()
```

{% endtab %}
{% endtabs %}
