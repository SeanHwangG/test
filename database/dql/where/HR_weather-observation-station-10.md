{% tabs %}
{% tab title='HR_weather-observation-station-10.md' %}

> Question

| Id   | City       | Country | State        | Zip    |
| ---- | ---------- | ------- | ------------ | ------ |
| 6    | Rotterdam  | NLD     | Zuid-Holland | 593321 |
| 1661 | Ecottsdale | USA     | Arizona      | 202705 |
| 3965 | Corona     | USA     | California   | 124966 |

* Query the list of CITY names from STATION that do not end with vowels without duplicates

| Id  | City      | Country | State        | Zip    |
| --- | --------- | ------- | ------------ | ------ |
| 6   | Rotterdam | NLD     | Zuid-Holland | 593321 |

{% endtab %}
{% tab title='HR_weather-observation-station-10.sql' %}

```sql
SELECT DISTINCT City FROM Station
  WHERE RIGHT(City, 1) NOT IN ('A', 'E', 'I', 'O', 'U');
```

{% endtab %}
{% endtabs %}
