{% tabs %}
{% tab title='KT_fiftyshades.md' %}

> Question

* Count number of lines with rose or pink (Ignore case)

```txt
Input:
12
pink
tequilaSunrose
mExicanPInK
Coquelicot
turqrose
roSee
JETblack
pink
babypink
pInKpinkPinK
PInkrose
lazerlemon

Output: 9
```

{% endtab %}
{% tab title='KT_fiftyshades.py' %}

```py
N = int(input())
count = 0
for _ in range(N):
  st = input().lower()
  if st.find('pink') != -1 or st.find('rose') != -1:
    count += 1

print(count if count != 0 else "I must watch Star Wars with my daughter")
```

{% endtab %}
{% endtabs %}
