{% tabs %}
{% tab title='HR_the-blunder.md' %}

> Question

* Employees

| ID  | Name     | Salary |
| --- | -------- | ------ |
| 1   | Kristeen | 1420   |
| 2   | Ashley   | 2006   |
| 3   | Julia    | 2210   |
| 4   | Maria    | 3000   |

* finding the difference between her miscalculation (salaries with any zeros removed), and the actual average salary

| Salary |
| ------ |
| 2061   |

{% endtab %}
{% tab title='HR_the-blunder.sql' %}

```sql
SELECT CEIL(AVG(Salary) - AVG(REPLACE(CAST(Salary AS CHAR), "0", ""))) FROM Employees;
```

{% endtab %}
{% endtabs %}
