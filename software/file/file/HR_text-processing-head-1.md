{% tabs %}
{% tab title='HR_text-processing-head-1.md' %}

> Question

* Output first 20 lines

{% endtab %}
{% tab title='HR_text-processing-head-1.sh' %}

```sh
# cat | cut -d$'\n' -f -20
head -n 20
```

{% endtab %}
{% endtabs %}
