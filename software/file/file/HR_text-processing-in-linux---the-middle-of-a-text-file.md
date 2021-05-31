{% tabs %}
{% tab title='HR_text-processing-in-linux---the-middle-of-a-text-file.md' %}

> Question

* Display the lines (from line number 12 to 22, both inclusive) for the input file

{% endtab %}
{% tab title='HR_text-processing-in-linux---the-middle-of-a-text-file.sh' %}

```sh
# cut -d$'\n' -f12-22
head -n 22 | tail -n +12
```

{% endtab %}
{% endtabs %}
