{% tabs %}
{% tab title='HR_text-processing-in-linux-the-grep-command-5.md' %}

> Question

* grep all lines with consecutively repeated digits

```txt
Input:
1234 5678 9101 1234
2999 5178 9101 2234
9999 5628 9201 1232
8482 3678 9102 1232

Output:
1234 5678 9101 1234
2999 5178 9101 2234
9999 5628 9201 1232
```

{% endtab %}
{% tab title='HR_text-processing-in-linux-the-grep-command-5.sh' %}

```sh
grep '\([0-9]\) *\1'
```

{% endtab %}
{% endtabs %}
