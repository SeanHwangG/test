{% tabs %}
{% tab title='HR_text_processing-sort-5.md' %}

> Question

* Rearrange the rows of the table in descending order of the values for the average temperature in January

```txt
Input:
Bismarck, N.D.    10.2    43.3    70.4    45.2    16.84    96    44.3    64
Austin, Texas    50.2    68.3    84.2    70.6    33.65    85    0.9    62 / 58
Baton Rouge, La.    50.1    66.6    81.7    68.1    63.08    110    0.2    52 / 46

Output:
Austin, Texas    50.2    68.3    84.2    70.6    33.65    85    0.9    62 / 58
Baton Rouge, La.    50.1    66.6    81.7    68.1    63.08    110    0.2    52 / 46
Bismarck, N.D.    10.2    43.3    70.4    45.2    16.84    96    44.3    64
```

{% endtab %}
{% tab title='HR_text_processing-sort-5.sh' %}

```sh
sort -nr -k2 -t $'\t'
```

{% endtab %}
{% endtabs %}
