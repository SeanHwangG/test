{% tabs %}
{% tab title='HR_text-processing-in-linux-the-uniq-command-4.md' %}

> Question

* Remove duplicate line

```txt
Input:
A00
a00
01
01
00
00
02
02
A00
03
aa
aa
aa

Output:
A00
a00
A00
03
```

{% endtab %}
{% tab title='HR_text-processing-in-linux-the-uniq-command-4.sh' %}

```sh
uniq -u
```

{% endtab %}
{% endtabs %}
