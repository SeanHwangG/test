{% tabs %}
{% tab title='HR_bash-tutorials-remove-the-first-capital-letter-from-each-array-element.md' %}

> Question

* Transform the names as described and display the entire array of country names with a space between each of them

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

Output: .amibia .auru .epal .etherlands .ewZealand .icaragua .iger .igeria .orthKorea .orway
```

{% endtab %}
{% tab title='HR_bash-tutorials-remove-the-first-capital-letter-from-each-array-element.py' %}

```sh
sed 's/^[A-Z]/./' | tr '\n' ' '
```

{% endtab %}
{% endtabs %}
