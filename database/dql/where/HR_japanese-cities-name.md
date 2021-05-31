{% tabs %}
{% tab title='HR_japanese-cities-name.md' %}

> Question

| Id   | City       | Country | State        | Zip    |
| ---- | ---------- | ------- | ------------ | ------ |
| 6    | Rotterdam  | JPN     | Zuid-Holland | 593321 |
| 1661 | Ecottsdale | USA     | Arizona      | 202705 |
| 3965 | Corona     | USA     | California   | 124966 |

* Query the names of all the Japanese cities in the CITY table. The COUNTRYCODE for Japan is JPN

| Id   | City       | Country | State        | Zip    |
| ---- | ---------- | ------- | ------------ | ------ |
| 6    | Rotterdam  | JPN     | Zuid-Holland | 593321 |
| 1661 | Ecottsdale | USA     | Arizona      | 202705 |
| 3965 | Corona     | USA     | California   | 124966 |

{% endtab %}
{% tab title='HR_japanese-cities-name.sql' %}

```sql
SELECT Name FROM City WHERE CountryCode = 'JPN';
```

{% endtab %}
{% endtabs %}
