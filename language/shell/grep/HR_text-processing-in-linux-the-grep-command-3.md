{% tabs %}
{% tab title='HR_text-processing-grep-3.md' %}

> Question

* Use grep to remove all those lines that contain the word 'that'
* The search should NOT be sensitive to case

```txt
Input:
From fairest creatures we desire increase,
That thereby beauty's rose might never die,
But as the riper should by time decease,
His tender heir might bear his memory:
But thou contracted to thine own bright eyes,
Feed'st thy light's flame with self-substantial fuel,

Output:
From fairest creatures we desire increase,
But as the riper should by time decease,
His tender heir might bear his memory:
But thou contracted to thine own bright eyes,
Feed'st thy light's flame with self-substantial fuel,
```

{% endtab %}
{% tab title='HR_text-processing-grep-3.sh' %}

```sh
# -v   : Invert the sense of matching
grep -viw 'that'
```

{% endtab %}
{% endtabs %}
