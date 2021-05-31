{% tabs %}
{% tab title='HR_text-processing-cut-7.md' %}

> Question

* print the characters from thirteenth position to the end

```txt
Input:
How was the math test?
We have a test tomorrow.
I finally passed that test.
test

Output:
math
test
that
test
```

{% endtab %}
{% tab title='HR_text-processing-cut-7.sh' %}

```sh
cut -d' ' -f4
```

{% endtab %}
{% endtabs %}
