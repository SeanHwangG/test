{% tabs %}
{% tab title='KT_transitwoes.md' %}

> Question

* Time to leave home s, class start time t, n이 주어진다
* n+1 times that took to go next station by walk
* n times that took for a bus to go
* n kimes that took for a bus to move to station
* Print if he can arrive at class in time

```txt
Input:
0 20 2
2 2 2
5 5
3 5

Output: yes
```

{% endtab %}
{% tab title='KT_transitwoes.py' %}

```py
cur, t, n = map(int, input().split())
D = list(map(int, input().split()))
B = list(map(int, input().split()))
C = list(map(int, input().split()))
for d, b, c in zip(D, B, C):
  cur += d
  cur += (cur % c)
  cur += b
if cur + D[-1] < t:
  print("yes")
else:
  print("no")
```

{% endtab %}
{% endtabs %}
