{% tabs %}
{% tab title='HR_text-processing-in-linux-the-grep-command-4.md' %}

> Question

* Grep all lines with containing any of the followings: "the" "that" "then" "those"

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
That thereby beauty's rose might never die,
But as the riper should by time decease,
Thou that art now the world's fresh ornament,
```

{% endtab %}
{% tab title='HR_text-processing-in-linux-the-grep-command-4.sh' %}

```sh
grep -Eiw 'th(e|ose|en|at)'
```

{% endtab %}
{% endtabs %}
