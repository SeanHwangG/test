{% tabs %}
{% tab title='HR_average-population.md' %}

> Question

* City

| Population | City       | Country | State        | Zip    |
| ---------- | ---------- | ------- | ------------ | ------ |
| 100        | Rotterdam  | JPN     | Zuid-Holland | 593321 |
| 200        | Ecottsdale | USA     | Arizona      | 202705 |
| 300        | Corona     | USA     | California   | 124966 |

* Query the average population for all cities in CITY, rounded down to the nearest integer

| Poplution |
| --------- |
| 400       |

{% endtab %}
{% tab title='HR_average-population.sql' %}

```sql
SELECT ROUND(AVG(Population)) FROM City;
```

{% endtab %}
{% endtabs %}
