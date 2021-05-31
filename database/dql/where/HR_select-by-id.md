{% tabs %}
{% tab title='HR_select-by-id.md' %}

> Question

| Id   | City       | Country | State        | Zip    |
| ---- | ---------- | ------- | ------------ | ------ |
| 6    | Rotterdam  | NLD     | Zuid-Holland | 593321 |
| 1661 | Ecottsdale | USA     | Arizona      | 202705 |
| 3965 | Corona     | USA     | California   | 124966 |

* Query all columns for a city in CITY with the ID 1661

| Id   | City       | Country | State   | Zip    |
| ---- | ---------- | ------- | ------- | ------ |
| 1661 | Ecottsdale | USA     | Arizona | 202705 |

{% endtab %}
{% tab title='HR_select-by-id.sql' %}

```sql
SELECT * FROM City WHERE Id = 1661;
```

{% endtab %}
{% endtabs %}
