{% tabs %}
{% tab title='HR_awk-4.md' %}

> Question

```txt
Input:
A 25 27 50
B 35 37 75
C 75 78 80
D 99 88 76

Output:
A 25 27 50;B 35 37 75
C 75 78 80;D 99 88 76
```

{% endtab %}
{% tab title='HR_awk-4.sh' %}

```sh
awk 'ORS=NR%2?";":"\n"'
```

{% endtab %}
{% endtabs %}
