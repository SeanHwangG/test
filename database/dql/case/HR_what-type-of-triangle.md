{% tabs %}
{% tab title='HR_what-type-of-triangle.md' %}

> Question

| A   | B   | C   |
| --- | --- | --- |
| 20  | 20  | 23  |
| 20  | 20  | 20  |
| 20  | 21  | 22  |
| 13  | 14  | 30  |

* Determine type of each triangle

| Type           |
| -------------- |
| Isosceles      |
| Equilateral    |
| Scalene        |
| Not A Triangle |

{% endtab %}
{% tab title='HR_what-type-of-triangle.py' %}

```sql
SELECT CASE WHEN A + B <= C OR A + C <= B OR B + C <= A THEN 'Not A Triangle'
            WHEN A = B AND B = C THEN 'Equilateral'
            WHEN A = B OR A = C OR B = C THEN 'Isosceles'
            ELSE 'Scalene'
  END
FROM TRIANGLES
```

{% endtab %}
{% endtabs %}
