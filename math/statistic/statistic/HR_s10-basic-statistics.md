{% tabs %}
{% tab title='HR_s10-basic-statistics.md' %}

> Question

* Print mean median mode of followings

```txt
Input:
10
64630 11735 14216 99233 14470 4978 73429 38120 51135 67060

Output:
43900.6
44627.5
4978
```

{% endtab %}
{% tab title='HR_s10-basic-statistics.py' %}

```py
import numpy as np
from scipy import stats

size = int(input())
numbers = list(map(int, input().split()))
print(np.mean(numbers))
print(np.median(numbers))
print(int(stats.mode(numbers)[0]))
```

{% endtab %}
{% endtabs %}
