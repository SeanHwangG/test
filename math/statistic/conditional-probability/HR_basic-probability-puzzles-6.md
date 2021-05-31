{% tabs %}
{% tab title='HR_basic-probability-puzzles-6.md' %}

> Question

* X contains 5 white balls and 4 black balls, Y contains 7 white balls and 6 black balls
* draw 1 ball from bag X and, without observing its color, put it into bag Y
* Now, if a ball is drawn from bag Y, find the probability that it is black

```txt
Output: 29/63
```

{% endtab %}
{% tab title='HR_basic-probability-puzzles-6.py' %}

```py
bag_x = ['w', 'w', 'w', 'w', 'w', 'b', 'b', 'b', 'b']
bag_y = ['w', 'w', 'w', 'w', 'w', 'w', 'w', 'b', 'b', 'b', 'b', 'b', 'b']

total, count = 0, 0
while len(bag_x) != 0:
  ball = bag_x.pop()
  bag_y.append(ball)
  total += len(bag_y)
  count += bag_y.count('b')
  bag_y.pop()

print(f"{counter}/{total}")
```

{% endtab %}
{% endtabs %}
