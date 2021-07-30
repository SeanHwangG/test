{% tabs %}
{% tab title='KT_exam.md' %}

> Question

* First line number of correct from friend, and answer sheets from mine and my friend are given
* Print maximum number of questions that I could have gotten right

```txt
Input:
3
FTFFF
TFTTT

Output: 2
```

{% endtab %}
{% tab title='KT_exam.py' %}

```py
correct = int(input())
my = input()
fr = input()
total = len(my)
same = 0
for m, f in zip(my, fr):
  if m == f:
    same += 1

if same > correct:
  print(correct + (total - same))
else:
  print(same + (total - correct))
```

{% endtab %}
{% endtabs %}
