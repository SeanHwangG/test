{% tabs %}
{% tab title='HR_weather-observation-station-1.md' %}

> Question

* Station

| Field  | Type     |
| ------ | -------- |
| ID     | NUMBER   |
| CITY   | VARCHAR2 |
| STATE  | VARCHAR2 |
| LAT_N  | NUMBER   |
| LONG_W | NUMBER   |

* Query a list of CITY and STATE from the STATION table.

| City    | State |
| ------- | ----- |
| Acme    | LA    |
| Addison | MI    |
| Agency  | MO    |
| Aguanga | CA    |
| Alanson | MI    |

{% endtab %}
{% tab title='HR_weather-observation-station-1.sql' %}

```sql
SELECT City, State FROM STATION;
```

{% endtab %}
{% endtabs %}
