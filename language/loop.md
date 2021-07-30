# Loop

{% tabs %}
{% tab title='python' %}

* tuple, strings, list, set, dictionary are iterables
* `s`.index(x[, i[, j]]) -> int: index of the first occurrence of x in s (at or after index i and before index j)
* len(`s`) -> int: find length of `s`
* min(`s`): Find minimum item of `s`
* max(`s`): Find maximum of `s`k
* `x` in `s` -> bool: True if an item s in eqal to x else False
* `x` not in `s` -> bool: False if an item of s is equal to x, else True
* `s` + `t`: the concatenation of s and t
* s[i]: ith item of s, origin 0

* itertools: iterator building blocks inspired by constructs in APL, Haskell, SML, with recast suitable for Python
  * accumulate(`iter`, func, *, initial): [ex] ([1,2,3,4,5]) → 1 3 6 10 15
  * chain(*`iter`): [ex] ('ABC', 'DEF') → A B C D E F
  * compress(data, selectors) [ex] ('ABCDEF', [1,0,1,0,1,1]) → A C E F
  * count(`start`=0, `step`=1): [ex] (2.5, 0.5): 2.5 3.0 3.5 ..
  * cycle(`iter`): [ex] ('ABCD') → A B C D A B C
  * dropwhile(`predicate`, `iterable`): [ex] (lambda x: x<5, [1,4,6,4,1]): 6, 4, 1
  * takewile(`predicate`, `iterable`): [ex] (lamda x: x<5, [1,3,6,4,1]): 1, 3
  * islice(`iter`, `start`, `stop`, [step]): [ex] ('ABCDEFG', 2, None): C D E F G
  * product(`*iter`, repeat=**1**): [ex] ('ABCD', 'xy'): Ax Ay Bx By Cx Cy Dx Dy
  * repeat(`object`[, times]): [ex] (10, 3) → 10 10 10

{% endtab %}
{% endtabs %}

## Continue

{% tabs %}
{% tab title='python' %}

```py
# 1. Skip for i
for val in "string":
  if val == "i":
    continue
  print(val)

print("The end")
```

{% endtab %}
{% endtabs %}

## Count

{% tabs %}
{% tab title='cpp' %}

```cpp
#include <algorithm>
// 1. count
int myints[] = {10,20,30,30,20,10,10,20};   // 8 elements
cout << "10 appears " << count (myints, myints+8, 10) << " times.\n";

```

{% endtab %}
{% endtabs %}

{% include '.count.prob' %}

## Generator

{% tabs %}
{% tab title='python' %}

* yield: generator function (not thread-safe)
  * from: yield list of elemens by one
  * Insert a line result = [] at the start of the function
  * Replace each yield expr with result.append(expr)
  * Insert a line return result at the bottom of the function

```py
# 1: Cube numbers
def cube_numbers(nums):
  for i in nums:
    yield(i**3)

cubes = cube_numbers([1, 2, 3, 4, 5])

for i in range(5):
  print((next(cubes)), 1)

# 2. Recursive yield
def recursive_items(dictionary):
  for key, value in dictionary.items():
  if type(value) is dict:
    yield from recursive_items(value)
  else:
    yield (key, value)

a = {'a': {'b': 'c', 'd': 'e'}, 'f': 'g'}
print(list(recursive_items(a)))
```

{% endtab %}
{% endtabs %}

{% include '.generator.prob' %}

## Len

{% tabs %}
{% tab title='cpp' %}

```cpp
sizeof(arr) / sizeof(arr[0]);
```

{% endtab %}
{% tab title='python' %}

* len(`iter`): length of iterable

{% include 'len.test' %}

{% endtab %}
{% endtabs %}

{% include '.len.prob' %}

## Min Max element

{% tabs %}
{% tab title='cpp' %}

* ForwardIt max_element(ForwardIt first, ForwardIt last): return max element
* ForwardIt min_element(ForwardIt first, ForwardIt last): return min element

{% endtab %}
{% tab title='python' %}

* min(`...`): return minimum element in `iterable`
* max(`...`): return maximum element in `iterable`

{% endtab %}
{% endtabs %}

{% include '.min-max-element.prob' %}

## Filter

{% tabs %}
{% tab title='shell' %}

* uniq: report or filter out repeated lines in a file
  * -c: show counting
  * -d: only print duplicate files
  * -u: Only print uniq line

* tee: read from standard input and write to standard output and files
  * -a: Append output to files rather than overwriting
  ![tee](images/20210209_173837.png)

* cut: cut out selected portions of each line
  * -d: use as separater (-f1) to grep index
  * -c n-: remove first n - 1 chatacter
  * -d -f1 /etc/passwd: Get all user I can use

* tr
  * -d: search and delete any character or string from a text
  * -s: compress same adjacent character output to single token
  * `a-z` `A-Z`: prints in capital letters

```sh
# 1. Cut example
rev | cut -c -5 | rev # Grep last 5 charcter
cut -f -1 -d "/"  # remove filename

# 2. tr
tr ':' '\n' <<< $PATH  # Print path in one line
```

{% endtab %}
{% endtabs %}

{% include '.cut.prob' %}
{% include '.tr.prob' %}
{% include '.uniq.prob' %}
{% include '.filter.prob' %}

## Sum

{% tabs %}
{% tab title='cpp' %}

> numeric

* accumulate(): Accumulate values in range

```cpp
#include <numeric>
using namespace std;

// 1. sum vector
vector<vector<int>> m = {{0, 1}, {2, 3}};
auto sum = accumulate(m.cbegin(), m.cend(), 0, [](auto lhs, const auto& rhs) {
  return accumulate(rhs.cbegin(), rhs.cend(), lhs);
});

vector<int> nums(5);
iota(nums.begin(), nums.end(), 1);
int sum = accumulate(nums.begin(), nums.end(), 0, [](int total, int current) {
  return total + current;
});
```

{% endtab %}
{% endtabs %}

{% include '.sum.prob' %}

## Iterate

{% include 'comprehension.test' %}
{% include '.sum.prob' %}

## In

{% tabs %}
{% tab title='cpp' %}

```cpp
#include <algorithm>

using namepsace std;

// 1. search for sublist
search(seq.begin(), seq.end(), sublist.begin(), sublist.end());
```

{% endtab %}
{% endtabs %}

{% include '.in.prob' %}

## Index

{% tabs %}
{% tab title='python' %}

* negative index starts from backward (-1 for last element)

```py
# 1. list index
li = [1, 2, 0, 6]
li[0]     # 1
li[-2]    # 0

# 2. string indexing
'python index'[12:22:3]  # esre
'python index'[5::2]     # nidx
'python index'[:,:,-1]   # xedni nohtyp
```

{% endtab %}
{% endtabs %}

{% include 'index.test' %}

{% include '.index.prob' %}

## Reverse

* Supported Language: python

{% include '.reverse.prob' %}

## Slice

{% tabs %}
{% tab title='python' %}

![index](images/20210220_175525.png)

```py
""" 1. Insertion """
a = [1, 2, 3]
a[0:0] = [-3, -2, -1, 0]
[-3, -2, -1, 0, 1, 2, 3]

""" 2. Deletion """
# a = [-3, -2, -1, 0, 1, 2, 3]
a[2:4] = []
# a [-3, -2, 1, 2, 3]

```

{% endtab %}
{% tab title='shell' %}

* ${parameter:offset}
* ${parameter:offset:length}

```sh
# 1. substring
Str="Learn Linux from LinuxHint"
subStr=${Str:6:5}
echo $subStr

string=01234567890abcdefgh
${string:7/-7}   # 7890abcdefgh / bcdefgh
${string:7:2/-2} # 78 / 7890abcdef
```

{% endtab %}
{% endtabs %}

{% include '.slice.prob' %}

## For

{% tabs %}
{% tab title='javascript' %}

```js
for ... in Loop  // iterates over the index in the array
```

{% endtab %}
{% tab title='Makefile' %}

```sh
# 1. logging function
$(error   VAR is $(VAR))
$(warning VAR is $(VAR))
$(info    VAR is $(VAR))

# 2. variable swap
reverse = $(2) $(1)
foo = $(call reverse,a,b)

# 3. parsed by make before the shell is invoked
foo: ; @for i in a b c d; do $(info $$i); done  # WRONG
```

{% endtab %}
{% tab title='python' %}

> Comprehension

* constructs that allow sequences to be built from other sequence

```py
# 1. Loop numbers, lists, string
for x in range(2, 6):
  print(x)

[n * 10 for n in [1, 2, 3, 4]               # [10, 20, 30, 40]
[i for i in range(30) if i % 3 == 0]        # [0, 3, 6, 9, 12, 15, 18, 21, 24, 27]
[n for li in lis for n in [[1, 2], [4, 5]]] # [1, 2, 4, 5]
{x**2 for x in [1, 1, 2]}                   # Set Comprehension
dic = {'a': 10, 'b': 34, 'A': 7, 'Z': 3}    # Dict Comprehension
{ k.lower(): dic.get(k.lower(), 0) + dic.get(k.upper(), 0)  for k in dic.keys()}    # {'a': 17, 'z': 3, 'b': 34}
print(f"{a}=5" if a == 5 else f"{a}!=5 ")
print(f"{a}=={b}" if a == b else f"{a} != {b}")
```

{% include 'for.test' %}

{% endtab %}
{% tab title='shell' %}

```sh
# 1. Update_repo
for d in */ ; do
  cd $d
  echo $d
  git add -A && git commit --amend --no-edit && git push --force
  cd ..
done

# 2. Infinite loop
for (( ; ; )); do
  echo "infinite loops [ hit CTRL+C to stop]"
done

# 3. Multiplication
read x
read y
for i in {+,-,"*",/}; do
  var=$(((x)$i(y)))
  echo $var
done

# 4. renmae multi
for file in Picture*.jpg; do
  mv "$file" "vacation-$file"
done
```

{% endtab %}
{% tab title='vim' %}

```sh
for s in list
  echo s
  continue  " jump to start of loop
  break     " breaks out of a loop
endfor
```

{% endtab %}
{% endtabs %}

{% include '.for.prob' %}

### For input

{% include '.for-input.prob' %}

### For variable

{% include '.for-variable.prob' %}

### For each

{% tabs %}
{% tab title='cmake' %}

```sh
foreach(var RANGE 0 10 2)           # prints 0 \n 2 \n 4 \n 6 \n 8 \n 10
  message("${var}")
endforeach()

set(li A B)
foreach(var IN LISTS li ITEMS foo)  # prints A \n B \n foo
  message("${var}")
endforeach()
```

{% endtab %}
{% tab title='cpp' %}

* Function for_each(): [ex] for_each( v.cbegin(), v.cend(), [] (const char c) {cout << c << " ";} );)
  * InputIterator first, InputIterator last
  * Function fn

```cpp
#include <iostream>
#include <utility>
using namespace std;

// 1. for_each
string v1[5] = {"one", "two", "three", "four", "five"};
string v2[5];

for_each(begin(v1), end(v1), [](const string &s) { cout << s << " "; });
cout << endl;
move(begin(v1), end(v1), v2);
for_each(begin(v1), end(v1), [](const string &s) { cout << s << " "; });
cout << endl;
for_each(begin(v2), end(v2), [](const string &s) { cout << s << " "; });
```

{% endtab %}
{% tab title='javascript' %}

```js
// 1. iterates over the object of objects
for ... of Loop

// 2. Jquery
<!-- check jQuery version -->
<!-- console.log(jQuery.fn.jquery) -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1/jquery.js"></script>

$( "li" ).each(function( index ) {
  console.log( index + ": " + $( this ).text() );
});
```

{% endtab %}
{% tab title='Makefile' %}

```make
NUMS = 1 2 3 4
target:
  for number in $(NUMS); do \
    echo $$number ; \
  done
```

{% endtab %}
{% tab title='python' %}

```py
fruits = ["apple", "banana", "cherry"]
for x in fruits:
  print(x)

for x in "banana":
  print(x)
```

{% endtab %}
{% tab title='shell' %}

```sh
for fn in `cat filenames.txt`; do
  echo "the next file is $fn"
  cat $fn
done
```

{% endtab %}
{% endtabs %}

{% include '.for-each.prob' %}

### For break

{% include '.for-break.prob' %}

### For nested

{% tabs %}
{% tab title='python' %}

```py
# 1. Print multiplicationt table
for i in range(1, 10):
  for j in range(1, 10):
    print(f"{i} X {j} = {i * j}")
```

{% endtab %}
{% endtabs %}

{% include '.for-nested.prob' %}

### For comprehension

{% tabs %}
{% tab title='javascript' %}

```js
[for (x of iterable) x]
[for (x of iterable) if (condition) x]
[for (x of iterable) for (y of iterable) x + y]
```

{% endtab %}
{% endtabs %}

{% include '.for-comprehension.prob' %}

### For zip

{% include '.for-zip.prob' %}

### Enumerate

{% include '.enumerate.prob' %}

## While

![While](images/20210514_015704.png)

{% include 'while.test' %}

{% tabs %}
{% tab title='python' %}

```py
""" 1. Print until i == 6 """
i = 1
while i < 6:
  print(i)
  i += 1
```

{% endtab %}
{% tab title='shell' %}

```sh
""" 1. Sleep and run """
echo "pid is $$"

while (( COUNT < 10 )); do
  sleep 10
  (( COUNT ++ ))
  echo $COUNT
done
exit 0

""" 2. keep input key """
valid=true
while [ $valid ]; do
  echo "press q to quit"
  read key
  if [[ $key = "q" ]] || [[ $key = "Q" ]]; then
    break
  fi
done

""" 3. Check for postgres connection """
postgres_ready() {
python << END
import sys
import psycopg2
try:
    psycopg2.connect(
        dbname="${POSTGRES_DB}",
        user="${POSTGRES_USER}",
        password="${POSTGRES_PASSWORD}",
        host="${POSTGRES_HOST}",
        port="${POSTGRES_PORT}",
    )
except psycopg2.OperationalError:
    sys.exit(-1)
sys.exit(0)
END
}
until postgres_ready; do
  >&2 echo 'Waiting for PostgreSQL'
  sleep 1
done
>&2 echo 'PostgreSQL is available'
```

{% endtab %}
{% tab title='vim' %}

```sh
while x < 5
endwhile
```

{% endtab %}
{% endtabs %}

{% include '.while.prob' %}

### While break

{% tabs %}
{% tab title='python' %}

```py
""" 1. Stop when i == 3 """
i = 1
while i < 6:
  print(i)
  if i == 3:
    break
  i += 1

""" 2. a + b until input is 0 0 """
while True:
  a, b = map(int, input().split())
  if a == b == 0:
    break
  print(a + b)
```

{% endtab %}
{% endtabs %}

{% include '.while-break.prob' %}
