# Hash

| Term             | Meaning                                 |
| ---------------- | --------------------------------------- |
| Identity law     | $A \cup \varnothing=A$                  |
| Idempotent Law   | $A \cup A =A$                           |
| Domination Law   | $A \cup U =U$                           |
| Communtative Law | $A \cup B =B \cup A$                    |
| Associative Law  | $(A \cup B) \cup C = A \cup (B \cup C)$ |

* Bloom Filter (Burton Howard Bloom, 1970)
  * space-efficient probabilistic data structure used to test whether an element is a member of a set
  * False positive matches are possible, but false negatives are not

* Cuckoo hashing: Use two hash functions
  * [+] O(1): worst case insert / lookup
  ![cuckoo hasing](images/20210218_232251.png)

{% tabs %}
{% tab title='python' %}

> mmh3

* mmh3.hash('aaaa', -1756908916): hash string based on value

{% endtab %}
{% endtabs %}

## Compression

{% tabs %}
{% tab title='shell' %}

* tar: archiving utility, store multiple files in a single file
  * (-)z: (un)z̲ip
  * (x): ex̲tract files from the archive
  * v: print the filenames v̲erbosely
  * -C: Create a new archive
  * -f: argument is f̱ilename
  * czf main.js package.json LICENSE: create .tar.gz
  * tar -xvzf sample.tar.gz
  * tar -xvjf sample.tar.bz2

* gzip
  * -d: decompress

* md5sum `filename`: calculate md5sum of file

* gunzip: decompress files created by gzip, zip, compress, automatically detect input format
  * .gz: unzip .gz file

* unzip
  * -o: overwrite files WITHOUT prompting
  * file.zip -d folder: Download in

* zip
  * -r my_arch.zip my_folder

```sh
# 1. zip entire directory
zip -r lab3.zip lab3
```

{% endtab %}
{% endtabs %}

## Encoding

* Rules for translating a Unicode string into a sequence of bytes are called an encoding
* Byte Order Mark # Set encoding for file

* ASCII: American Standard Code for Information Interchange
  * code point (U+ or \u)
  * U+0000~U+FFFF: BMP (Basic Multilingual Plane)
  * U+10000~U+1FFFF: SMP (Supplementary Multilingual Plane)

![Ascii](images/20210220_233720.png)

* URL Encoding

| Value | Symbol |
| ----- | ------ |
| %21   | !      |
| %40   | @      |

* UTF-8
  * Three byte encoding for korean
  * Korea [(initial) × 588 + (medial) × 28 + (final)] + 44032

* CP949
* EUC-KR

{% tabs %}
{% tab title='python' %}

> hashlib

* implements a common interface to many different secure hash and message digest algorithms

* sha224(str_.encode()).hexdigest()

{% include 'unicode.test' %}

{% endtab %}
{% endtabs %}

{% include '.encoding.prob' %}

## Decoding

{% tabs %}
{% tab title='shell' %}

* base64
  * -d: Decode base64

{% endtab %}
{% endtabs %}

{% include '.decoding.prob' %}

## Set

{% tabs %}
{% tab title='cpp' %}

> unordered_set

* int count()
* void clear()
* insert()

{% endtab %}
{% tab title='javascript' %}

* length
* add()
* clear()
* delete(`value`): Delete `value` in set
* has(`value`): Check existance of `value` in set

```js
// 1. Basic example
var set = new Set();
new Set([1, 2, 3, 4, 5]);

// 2. Remove duplicate in array
const numbers = [2,3,4,4,2,3,3,4,4,5,5,6,6,7,5,32,3,4,5]
console.log([...new Set(numbers)])
```

{% endtab %}
{% tab title='python' %}

* unordered and unindexed by default, duplicate value will be ignored

{% include 'set.test' %}

> Method

* issubset(`other`)
* set <= other
  * every element in the set is in other

* `set` | `other` | …: union `set` and `other`
* union(*`others`)
  * a new set with elements from the set and all `others`

* set & other
* intersection(*other)
  * element that are in both set and other

* set ^ other
* symmetric_difference(other)
  * set with elements in either the set or other but not both

* set < other: set <= other and set != other
* set >= other: if every element in another is in the set
* set > other: set >= other and set != other
* set - other: set with elements in the set that are not in the others
* add(elem): Add elem to the set
* copy(): a shallow copy of the set
* discard(elem): Remove element elem from the set if it is present
* isdisjoint(`other`): True if the set has no elements in common with `other`
* pop(): Remove and return an arbitrary element. Raises KeyError if empty. O(1)
  * Raise KeyError if set is empty
* remove(elem): Remove elem from the set. Raises KeyError if elem is not in the set

```py
# 1. Create, add, remove
a = set() : Create
a = set([2, 3])

a.add(1)
a.add(3)

a.remove(3)
if 3 in a:
  print("3 exists")

print(a)    # {1, 2, 3}
```

{% endtab %}
{% endtabs %}

{% include '.set.prob' %}

### Multiset

{% include '.multiset.prob' %}

### Ordered Set

* Natively supported in c++ (Implemented in BST)

{% tabs %}
{% tab title='cpp' %}

> set

* count(): `elem`
* erase()
* insert()
  * {1, 2}: insert multiple values
* size()

```cpp
// 1. Comparater
auto cmp = [](int x, int y){ return x < y; };
auto set = set<int,decltype(cmp)>(cmp);

struct cmp {
  bool operator() (int a, int b) const {
    return ...
  }
};

std::set<int, cmp> s;

// 2. Iterate Backward
for (auto rit = myset.rbegin(); rit != myset.rend(); ++rit)
cout << ' ' << *rit;

// 3. multiset erase just one element
auto itr = my_multiset.find(value);
if (itr!=my_multiset.end())
  my_multiset.erase(itr);

m[cur].erase(m[cur].lower_bound(next));
```

{% endtab %}
{% endtabs %}

{% include '.ordered-set.prob' %}

## Map

* used to store data values in key:value pairs, unordered and changeable. no duplicate keys

{% tabs %}
{% tab title='cpp' %}

> unordered_map

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  // Create an unordered_map of three strings (that map to strings)
  std::unordered_map<std::string, std::string> u = {
    {"RED","#FF0000"},
    {"GREEN","#00FF00"},
    {"BLUE","#0000FF"}
  };

  std::cout << "Iterate and print keys and values of unordered_map, being explicit with the type of the iterator, n:\n";
  for( const std::pair<std::string, std::string>& n : u ) {
    std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
  }

  std::cout << "Iterate and print keys and values of unordered_map, using auto:\n";
  for( const auto& n : u ) {
    std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
  }

  std::cout << "Iterate and print keys and values using structured binding (since C++17):\n";
  for( const auto& [key, value] : u ) {
    std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
  }

  // Add two new entries to the unordered_map
  u["BLACK"] = "#000000";
  u["WHITE"] = "#FFFFFF";

  std::cout << "Output values by key:\n";
  std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n";
  std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "]\n";
}
```

{% endtab %}
{% tab title='java' %}

* Map\<K, V\>
  * Set\<K\> keySet(): Returns a Set view of the keys contained in this map
  * Set\<Map.Entry\<K, V\>\>: Returns a Set view of the mappings contained in this map
  * V put(K key, V value): Associates the specified value with the specified key in this map
  * V remove(Object key): Removes the mapping for a key from this map if it is present
  * default V replace(K key, V value): Replaces the entry for the specified key only if exists

* Interface Map.Entry\<K,V>
  * K getKey(): return key corresponding to this entry
  * V getValue(): return value corresponding to this entry
  * V setValue(V value): Replaces the value corresponding to this entry

```java
// 1. Create map with multiple Key
Map<String, Integer> immutableMap = Map.of("One", 1, "Two", 2, "Three", 3);
```

{% endtab %}
{% tab title='javascript' %}

* Map object holds key-value pairs and remembers the original insertion order of the keys

```js
// 1. CRUD Object
var person = {firstName:"John", lastName:"Doe", age:50};
var person = new Object();
person.firstName = "John";
person.lastName = "Doe";
person.age = 50;

obj.[key] || 0           // Use default
delete dict[entry[0]]    // Delete Keys
Object.keys(obj).reduce((a, b) => obj[a] > obj[b] ? a : b);    // Get the largest keys
delete query["obsolte"];

// 2. Merge Object using spread operator
var obj2 = { foo: 'baz', y: 13 };
var mergedObj = { ...obj1, ...obj2 };                    // merge objects

const person = {firstName: “sean”, lastName: “hwang”}   // Destruct object

Object.keys(myObject).length                            // Iterate key value
Object.entries(obj).forEach(([key, value]) => { console.log(key, value); });

where: {
  ...(params.val && {key : val}), // optional key
}

// 3. Destructuring
const {firstName: fn, lastName: ln} = person
console.log(`${fn} ${ln}`)
let [first, last] = ['sean', 'hwang']    // Destruct Array
console.log(first);
```

{% endtab %}
{% tab title='python' %}

{% include 'dictionary.test' %}

* values in dictionary items can be of any data type

> Member function

* [key]: item of d with key key. Raises a KeyError if key is not in the map
* clear(): remove all items from the dictionary
* fromkeys()
* iter(d): an iterator over the keys
* items(): iter((key, value))
* keys(): iter(key)
* list(d): a list of all the keys
* len(d): the number of items
* pop(key[, default]): If key in d, remove it and return, else return default (error if no default)
* setdefault(key, val): returns the value of the item, if doesn’t exist, insert val
* update([other]): Update `dict` with the key|value pairs from other, overwriting existing keys
* values() -> views(): returns views of `dict` value

```py
# 1. CRUD
dic = { "model": "Mustang", "year": 1964 }
dictionary = dict(zip(['a', 'b', 'c'], [1, 2, 3]))

d = {}
for key, value in pairs:
  d.setdefault(key, []).append(value) # Create empty list if not exists (defaultdict)
return d

""" Read """
list(dic)           # All keys
list(dic.values())  # all values

d = {'foo': 1, 'bar': 2, 'baz': 3}
for k in d:
  print(k)  # 'foo', 'bar', 'baz'

link, problem_id, level, title = itemgetter("link", "problem_id", "level", "title")(problem_dic)

""" Add """
sorted_x = sorted(x.items(), key=lambda kv: kv[1]) # Sort by value
inv_map = {v: k for k, v in my_map.items()}        # reverse key, value
dict.fromkeys(iterable[, value])

x = ('key1', 'key2', 'key3')
y = 0
thisdict = dict.fromkeys(x, y) # {'key1': 0, 'key2': 0, 'key3': 0}
thisdict = dict.fromkeys(x)    # {'key1': None, 'key2': None, 'key3': None}

# 2. Get keys as a list
key_list = [*dic]
```

{% endtab %}
{% tab title='vim' %}

```sh
# 1. Dictionary
count(dict, 'x')
empty(dict)
get(dict, "apple")
has_key(dict, 'foo')
keys(dict)
len(dict)
max(dict)
min(dict)
remove(dict, "apple")
let longlist = mylist + [5, 6]
let mylist += [7, 8]
mylist[2:]
let alist = add(mylist, 4)

""" Construct """
let colors = {
\ "apple": "red",
\ "banana": "yellow"
}

""" Access """
echo colors["a"]

for key in keys(dict)
  echo key . ': ' . dict(key)
endfor
```

{% endtab %}
{% endtabs %}

{% include '.map.prob' %}

### Counter

{% tabs %}
{% tab title='python' %}

{% include 'counter.test' %}

> Counter

* subclass of dict
  * elements(): iterator over elements repeating count | ignore if less than one
  * most_common([k]): Return k most common key value pair in order in O(n log k)
  * subtract([iterable-or-mapping]): Subtract another mapping
  * update([iterable-or-mapping]): Add another mapping

* ChainMap
  * keys(): used to display all the keys of all the dictionaries in ChainMap
  * values(): display values of all the dictionaries in ChainMap
  * maps(): display keys with corresponding values of all the dictionaries in ChainMap.
  * new_child(`dic`): Add new dictionary to this chainmap

```py
from collections import Counter, ChainMap

# 1. CRUD Counter
Counter()
Counter('gallahad')            # new counter from an iterable
Counter({'red': 4, 'blue': 2}) # new counter from a mapping
Counter(cats=4, dogs=8)        # keyword args

co['a'] += 1      # update
del c['sausage']  # remove

# 2. ChainMap

d1 = {'a': 1, 'b': 2}
d2 = {'c': 3, 'd': 4}
d3 = {'e': 5, 'f': 6}
c = ChainMap(d1, d2, d3)

print(c)                # ChainMap({'a': 1, 'b': 2}, {'c': 3, 'd': 4}, {'e': 5, 'f': 6})
print(c.maps)           # [{'b': 2, 'a': 1}, {'c': 4, 'b': 3}]
print(list(c.keys()))   # ['a', 'c', 'b']
print(list(c.values())) # [1, 4, 2]
```

{% endtab %}
{% endtabs %}

{% include '.counter.prob' %}

### Ordered map

{% tabs %}
{% tab title="cpp" %}

> map

```cpp
#include <iostream>
#include <map>
using namespace std;

int main () {
  map<char, int> mymap;

  // first insert function version (single parameter):
  mymap.insert ( pair<char,int>('a',100) );
  mymap.insert ( pair<char,int>('z',200) );

  pair<map<char,int>::iterator,bool> ret;
  ret = mymap.insert ( pair<char,int>('z',500) );
  if (ret.second==false) {
    cout << "element 'z' already existed";
    cout << " with a value of " << ret.first->second << '\n';
  }

  map<char,int>::iterator it = mymap.begin();
  mymap.insert (it, pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert (it, pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  map<char, int> anothermap;
  anothermap.insert(mymap.begin(),mymap.find('c'));

  for (it=mymap.begin(); it!=mymap.end(); ++it)
    cout << it->first << " => " << it->second << '\n';

  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    cout << it->first << " => " << it->second << '\n';

  // using range of pair
  map<string, int> m(wordMap.begin(), wordMap.end());k

  auto cmp = [](int a, int b) { return a < b;};
  map<int, int, decltype(cmp)> m(cmp);

  map<int, int> n2m{{1, 2}};
  n2m[5]++;

  // iterate
  for (auto it : n2m)
    cout << it.first << " " << it.second << endl;

  mp.insert({ 2, 30 });
  mp.find(2);

  return 0;
}
```

{% endtab %}
{% tab title='python' %}

> ordereddict

* popitem(last=True)
* move_to_end(key, last=True)

```py
OrderedDict(sorted(dictitems(), key=lambda t: t[0]))  # LRU

from collections import OrderedDict
def align_with_list(dic, li):
  print(OrderedDict([(el, dic[el]) for el in li]))    # OrderedDict([('sandwich', 'C'), ('potato', 'A'), ('tomato', 'B')])
align_with_list({'potato':'A', 'tomato':'B', 'sandwich':'C'}, ['sandwich', 'potato', 'tomato'])
```

{% endtab %}
{% endtabs %}
