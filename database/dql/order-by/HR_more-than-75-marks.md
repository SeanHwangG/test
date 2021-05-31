{% tabs %}
{% tab title='HR_more-than-75-marks.md' %}

> Question

| ID  | Name     | Marks |
| --- | -------- | ----- |
| 1   | Ashley   | 81    |
| 2   | Samantha | 75    |
| 4   | Julia    | 76    |
| 3   | Belvet   | 84    |

* Query the Name of any student in STUDENTS who scored higher than 75 Marks
* Order your output by the last three characters of each name
  * If students both have names ending in same last three characters (i.e.: Bobby, Robby, etc.), sort them by ascending ID

{% endtab %}
{% tab title='HR_more-than-75-marks.sql' %}

```sql
SELECT Name FROM Students WHERE Marks > 75
  ORDER BY RIGHT(Name, 3), Id;
```

{% endtab %}
{% endtabs %}
