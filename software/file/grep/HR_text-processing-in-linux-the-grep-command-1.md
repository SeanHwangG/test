{% tabs %}
{% tab title='HR_text-processing-grep-1.md' %}

> Question

* Output only those lines that contain the word 'the'

```txt
Input:
From fairest creatures we desire increase,
That thereby beauty's rose might never die,
But as the riper should by time decease,
His tender heir might bear his memory:
But thou contracted to thine own bright eyes,
Feed'st thy light's flame with self-substantial fuel,
Making a famine where abundance lies,
Thy self thy foe, to thy sweet self too cruel:
Thou that art now the world's fresh ornament,

Output:
But as the riper should by time decease,
Thou that art now the world's fresh ornament,
```

{% endtab %}
{% tab title='HR_text-processing-grep-1.sh' %}

```sh
grep  " the "
```

{% endtab %}
{% endtabs %}
