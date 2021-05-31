{% tabs %}
{% tab title='HR_weather-observation-station-4.md' %}

> Question

* Station

| Id   | City       | Country | State        | Zip    |
| ---- | ---------- | ------- | ------------ | ------ |
| 6    | Rotterdam  | NLD     | Zuid-Holland | 593321 |
| 1661 | Ecottsdale | USA     | Arizona      | 202705 |
| 3965 | Corona     | USA     | California   | 124966 |

* find difference between total number of CITY entries in table and number of distinct CITY entries in table

| Count |
| ----- |
| 13    |

{% endtab %}
{% tab title='HR_weather-observation-station-4.sql' %}

```sql
SELECT COUNT(City) - COUNT(DISTINCT City) FROM Station;
```

{% endtab %}
{% endtabs %}
