{% tabs %}
{% tab title='AC_arc124_b.md' %}

> Question

* Given are sequences a and b, each of length N, consisting of non-negative integers
* i -th elements of a and b are ai and bi, respectively.
* A non-negative integer x is said to be good if
  * It's possible to permute b so that ai XOR bi=x holds for all integer i st 1≤i≤N , where XOR is the bitwise XOR
* List all good integers in ascending order.

```txt
Input:
2
0 1
0 2

Output: 0

Input:
3
1 2 3
6 4 7

Output:
1
5
```

{% endtab %}
{% tab title='AC_arc124_b.py' %}

```py
from collections import Counter

N = int(input())
a = list(map(int, input().split()))
b = sorted(map(int, input().split()))

X = set()
for j in range(N):
  x = a[0] ^ b[j]
  X.add(x)

ans = []
for x in sorted(X):
  c = sorted([av ^ x for av in a])
  if b == c:
    ans.append(x)

print(len(ans))
if ans:
  print(*ans, sep="\n")
```

{% endtab %}
{% endtabs %}
