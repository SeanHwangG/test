{% tabs %}
{% tab title='HR_population-density-difference.md' %}

> Question

* City

| Population | City       | Country | State        | Zip    |
| ---------- | ---------- | ------- | ------------ | ------ |
| 100        | Rotterdam  | JPN     | Zuid-Holland | 593321 |
| 200        | Ecottsdale | USA     | Arizona      | 202705 |
| 300        | Corona     | USA     | California   | 124966 |

* Query the difference between the maximum and minimum populations in CITY

| Poplution |
| --------- |
| 200       |

{% endtab %}
{% tab title='HR_population-density-difference.sql' %}

```sql
SELECT MAX(Population) - MIN(Population) FROM City;
```

{% endtab %}
{% endtabs %}
