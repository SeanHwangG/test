# Data Structure

> Term

* Abstract data types: Logical description ([ex] List, Map)
* Data Structure: concrete ([ex] LinkedList, ArrayList, HashMap, TreeMap)

## Time

{% tabs %}
{% tab title="cpp" %}

* chrono
  * this_thread::sleep_for(milliseconds(x)): Pause

```cpp
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
using namespace std;
using namespace std::chrono;

// 1. Current time
std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
std::cout << std::ctime(&end_time); // Mon Oct  2 00:59:08 2017


// 2. Measure time
auto start_time = system_clock::to_time_t(system_clock::now());
cout << start_time << endl;  // 1606398149
this_thread::sleep_for(chrono::seconds(1));
auto end_time = system_clock::to_time_t(system_clock::now());
cout << end_time - start_time << " second passed" << endl;  // 1 second passed

auto start = std::chrono::high_resolution_clock::now();
this_thread::sleep_for(chrono::seconds(1));
auto finish = std::chrono::high_resolution_clock::now();
std::cout << duration_cast<milliseconds>(finish - start).count() << "ms\n";  // 1001ms
```

{% endtab %}
{% tab title="python" %}

* time
  * time.perf_counter\[_ns](): clock with highest available resolution to measure a short duration
  * tm_zone: EDT, EST
  * time() / time_ns() / ctime(): time in ms / nice format
  * gmtime() / localtime(): 0 is struct_time(1970, 1, 1), and none is current time

* django-extension
  * db.models
    * TimeStampedModel: extends instead of Model to have created at, modified at field

```py
from datetime import date, datetime

# 1. Display settings
today = date.today()
print(today.strftime("%d/%m/%Y"))  # dd/mm/YY
print(today.strftime("%B %d, %Y")) # Textual month, day and year
print(today.strftime("%m/%d/%y"))  # mm/dd/y
print(today.strftime("%b-%d-%Y"))  # Month abbreviation, day and year
print(datetime.now())              # datetime object containing current date and time
print(datetime.now().strftime("%d/%m/%Y %H:%M:%S"))   # dd/mm/YY H:M:S

# 2. Timer context
class Time:
  def __init__(self, f):
  self.func = f

  def __call__(self, *args, **kwargs):
  cur = time.perf_counter()
  print(cur)   # 185.006554938
  self.func(*args, **kwargs)
  print(f"Took {time.perf_counter() - cur:.3f}s")

@Time
def complex():
  li = []
  for i in range(1000000):
  li.append(i)
  li.sort()

complex()       # Took 0.111s
```

{% endtab %}
{% tab title='shell' %}

* time
  * -v: change verbosity, more statistics with Linux kernel v2.6
  * user: time CPU spent executing application code on behalf of program
  * Swaps: num times the process was swapped to disk
  * system: time CPU spent executing system or kernel code on behalf of application
  * Exit status: exit status of the application
  * real / elapsed: time between when the program started and finished execution
  * Page size (bytes): page size of the system
  * Major (I/O) page faults: num major page faults that required to be read from disk
  * In / Voluntary context switch: num times the process yielded / taken from CPU

{% endtab %}
{% endtabs %}

### Timezone

{% tabs %}
{% tab title='shell' %}

* timedatectl: show current time zone
  * list-timzeons: Available time zone
  * set-timezone: [ex] UTC

{% endtab %}
{% endtabs %}

## Date

{% tabs %}
{% tab title='javascript' %}

* new Date()
* new Date(year, month, day, hours, minutes, seconds, milliseconds)   // month from 0
* new Date(milliseconds)
* new Date(date string)

* toDateString()
* toUTCString()
* toString()

```js
// 1. Check Same date
var isSameDay = (dateToCheck.getDate() === actualDate.getDate()
     && dateToCheck.getMonth() === actualDate.getMonth()
     && dateToCheck.getFullYear() === actualDate.getFullYear())


// 2. Add Days
Date.prototype.addDays = function(d) {
  return new Date(this.valueOf() + 864E5 * d);
}

// 3. Iterate date
var now = new Date();
var daysOfYear = [];
for (var d = new Date(2012, 0, 1); d <= now; d.setDate(d.getDate() + 1)) {
    daysOfYear.push(new Date(d));
}

// 4. moment
<script src="https://momentjs.com/downloads/moment.min.js"></script>

moment().format('YYYY-MM-DD HH:MM:SS') // convert javascript date to string
moment(A).isSameOrAfter(B)

type: DataTypes.VIRTUAL,               // automatically set +3
get() {
  return moment(this.arrivalDate).add(3, "days");
},

now = moment()
now.startOf('day') / endOf('day')        // Start / End of today
```

{% endtab %}
{% tab title='python' %}

* DateTime
  * datetime(year, month, day[, hour[, minute[, second[, microsecond[, tzinfo]]]]])
  * end_date = date_1 + datetime.timedelta(days=10): add date to datetime

* date
  * date(2002, 12, 31)
  * isocalendar() / isoformat() / strftime('%d/%m/%y'): (y, m, d) / (2002-12-31) / (31/12/02)
  * replace(day=26): replace
  * weekday(): Monday is 0 and Sunday is 6
  * timedelta(days=1, hours=0, minutes=50): date - timedelta

* Time
  * replace([hour[, minute[, second[, microsecond[, tzinfo]]]]])
  * strftime("%H:%M:%S %Z")
  * min: time(0, 0, 0, 0)
  * max: time(23, 59, 59, 999999)

```py
from datetime import date, datetime, timedelta

print(f"strftime \t {d.}")
print(f"timedelta \t {d - timedelta(days=1, hours=0, minutes=50)}")
```

{% endtab %}
{% tab title='shell' %}

* display date
* +%Y%m%d: Format
* -s "2 OCT 2006 18:00:00": Change format using +
* -u {month}{day}{hour}{minute}{year}: set date
* -s "`ssh server date`"

```sh
backup_filename="${BACKUP_FILE_PREFIX}_$(date +'%Y_%m_%dT%H_%M_%S').sql.gz"
```

{% endtab %}
{% endtabs %}

{% include '.date.prob' %}
