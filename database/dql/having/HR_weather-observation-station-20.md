{% tabs %}
{% tab title='HR_weather-observation-station-20.md' %}

> Question

* STATION

| LAT_N | City       |
| ----- | ---------- |
| 10    | Rotterdam  |
| 123   | Ecottsdale |
| 123   | Corona     |

* Query the median of the Northern Latitudes (LAT_N) from STATION and round your answer to 4 decimal places

| Median   |
| -------- |
| 123.0000 |

{% endtab %}
{% tab title='HR_weather-observation-station-20.sql' %}

```sql
SELECT ROUND(x.LAT_N,4) from STATION x, STATION y
  GROUP BY x.LAT_N
  HAVING SUM(SIGN(1-SIGN(y.LAT_N-x.LAT_N))) = (COUNT(*)+1)/2;
```

{% endtab %}
{% endtabs %}
