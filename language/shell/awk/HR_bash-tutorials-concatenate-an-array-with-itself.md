{% tabs %}
{% tab title='HR_bash-tutorials-concatenate-an-array-with-itself.md' %}

> Question

* Concatenate three repetitions of the original array

```txt
Input:
Namibia
Nauru
Nepal
Netherlands
NewZealand
Nicaragua
Niger
Nigeria
NorthKorea
Norway

Output:
Namibia Nauru Nepal Netherlands NewZealand Nicaragua Niger Nigeria NorthKorea Norway Namibia Nauru Nepal Netherlands \
NewZealand Nicaragua Niger Nigeria NorthKorea Norway Namibia Nauru Nepal Netherlands NewZealand Nicaragua Niger Nigeria \
NorthKorea Norway
```

{% endtab %}
{% tab title='HR_bash-tutorials-concatenate-an-array-with-itself.sh' %}

```sh
tr `$'\n' ' ' | awk '{print $`0 `$0 $`0}'
```

{% endtab %}
{% endtabs %}
