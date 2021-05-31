{% tabs %}
{% tab title='KT_reversebinary.md' %}

> Question

* Print reversed binary

```txt
Input: 13
Output: 11
```

{% endtab %}
{% tab title='KT_reversebinary.py' %}

```py
a = bin(int(input()))[2:]
print(int(a[::-1],2))
```

{% endtab %}
{% endtabs %}
