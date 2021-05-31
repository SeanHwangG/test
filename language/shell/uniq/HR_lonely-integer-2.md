{% tabs %}
{% tab title='HR_lonely-integer-2.md' %}

> Question

* first line of input contains number of integers, next contains space-separated integers that form array
* Output, the number that occurs only once

```sh
Input:
5
0 0 1 2 1

Output: 2
```

{% endtab %}
{% tab title='HR_lonely-integer-2.sh' %}

```sh
read
tr ' ' '\n' | sort | uniq -u
```

{% endtab %}
{% endtabs %}
