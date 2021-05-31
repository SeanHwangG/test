{% tabs %}
{% tab title='HR_weather-observation-station-8.md' %}

> Question

| Id   | City       | Country | State        | Zip    |
| ---- | ---------- | ------- | ------------ | ------ |
| 6    | Rotterdam  | JPN     | Zuid-Holland | 593321 |
| 1661 | Ecottsdale | USA     | Arizona      | 202705 |
| 3965 | Corona     | USA     | California   | 124966 |

* Query the unique list of CITY names from STATION which have vowels as both their first and last characters

| Id   | City       | Country | State   | Zip    |
| ---- | ---------- | ------- | ------- | ------ |
| 1661 | Ecottsdale | USA     | Arizona | 202705 |

{% endtab %}
{% tab title='HR_weather-observation-station-8.sql' %}

```sql
SELECT DISTINCT city FROM station
  WHERE city REGEXP '^[aeiou].*[aeiou]$'
```

{% endtab %}
{% endtabs %}
