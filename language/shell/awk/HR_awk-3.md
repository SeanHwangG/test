{% tabs %}
{% tab title='HR_awk-3.md' %}

> Question

* A >=80, B >= 60, C >= 60, FAIL otherwise

```txt
Input:
A 25 27 50
B 35 37 75
C 75 78 80
D 99 88 76

Output:
A 25 27 50 : FAIL
B 35 37 75 : FAIL
C 75 78 80 : B
D 99 88 76 : A
```

{% endtab %}
{% tab title='HR_awk-3.sh' %}

```sh
awk '{avg=($2+$3+$4)/3; print $0, ":", (avg<50)?"FAIL":(avg<80)?"B":"A"}'
```

{% endtab %}
{% endtabs %}
