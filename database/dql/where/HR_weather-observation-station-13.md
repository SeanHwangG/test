{% tabs %}
{% tab title='HR_weather-observation-station-13.md' %}

> Question

| LAT_N | City       |
| ----- | ---------- |
| 10    | Rotterdam  |
| 123   | Ecottsdale |
| 300   | Corona     |

* Query the sum of Northern Latitudes (LAT_N) from STATION having values greater than 38.7880 and less than 137.2345
* Truncate your answer to 4 decimal places

| SUM      |
| -------- |
| 123.0000 |

{% endtab %}
{% tab title='HR_weather-observation-station-13.sql' %}

```sql
SELECT TRUNCATE(SUM(LAT_N), 4) FROM Station
  WHERE LAT_N > 38.7880 AND LAT_N < 137.2345;
```

{% endtab %}
{% endtabs %}
