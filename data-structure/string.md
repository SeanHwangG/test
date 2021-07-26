# String

{% tabs %}
{% tab title='c' %}

* stdlib.h / cstdlib: cstdlib contained in std::, so its preferred
  * If ptr doesn’t point to a block of memory allocated with malloc, calloc, or realloc, undefined behavior
  * free does not change the value of ptr itself, hence it still points to the same (now invalid) location
  * atof(): string to double
  * atoi(): string to integer
  * atol(): string to long integer
  * atoll(): string to long long integer
  * strtod(): string to double
  * sleep(`ms`): sleep for `ms` mili-seconds
  * strtof(): string to float
  * strtol(): string to long integer
  * strtold: string to long double
  * strtoll: string to long long integer
  * strtoul: string to unsigned long integer
  * strtoull: string to unsigned long long integer
  * rand: Generate random number
  * srand: Initialize random number generator
  * calloc(): Allocate and zero-initialize array
  * free(): Deallocate memory block
  * malloc(): Allocate memory block
    * sizeof(int): allocate int pointer
  * realloc(): Reallocate memory block
  * srand (time(NULL));: give new seed
  * rand()%(max-min + 1) + min;: Generate number between a to b

* cstring
  * memcpy, memmove(): Copy Move block of memory
  * strcpy, strncpy(): Copy string / characters from string
  * strcat(): Concatenate strings
  * strncat(): Append characters from string
  * memcmp(): Compare two blocks of memory
  * strcmp: strncmp() // Compare two strings, Compare characters of two strings
  * strcoll(): Compare two strings using locale
  * strxfrm(): Transform string using locale
  * memchr(): Locate character in block of memory
  * strchr(): Locate first occurrence of character in string
  * strcspn(): Get span until character in string
  * strpbrk(): Locate characters in string
  * strrchr(): Locate last occurrence of character in string
  * strspn(): Get span of character set in string
  * strstr(): Locate substring
  * strtok(): Split string into token
  * memset(): Fill block of memory
  * strerror(): Get pointer to error message string
  * strlen(): Get string length

```c
// strlen vs sizeof
// # characters between the beginning of the string and the terminating null character
char mystr[100]="test string"; // sizeof : 100, strlen : 11
```

{% endtab %}
{% tab title="cpp" %}

> string

* c_str()
  * printf("%s", str.c_str());: printf string
* setfill()
  * setw(5) << setfill('0'): leading string
* string(1, 'c'): char to string
* to_string(): number tos = 0, size_t len = npos);
* size_t find_first_not_of (string/char str, size_t pos = 0);: if no result return string::npos
* string& replace (size_t pos,  size_t len,  const string& str);
* string substr (size_t pos = 0, size_t len = npos) const;

> sstream

* Useful for building strings

> stringview

* Less memory

```cpp
#include <cwchar>
#include <iostream>
#include <string>
#include <string_view>

#include <sstream>
using namespace std;

// 1. string conversions
/* from deque */
vector<int> v(make_move_iterator(q.begin()), make_move_iterator(q.end()));
/* to decimal, hexadecimal */
to_string(i);
string toHex(string s) {
  stringstream ss;
  for (char ch : s)
    ss << hex << (int)ch;
  return ss.str();
}
/* Ascii number to string */
stringstream ss;
unsigned char num = (unsigned char)205;
ss.write((char*)&num, sizeof(num)) ;
cout << ss.str();

// 2. Trim
void trimLeftTrailingSpaces(string &input) {
  input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {return !isspace(ch);}));
}

void trimRightTrailingSpaces(string &input) {
  input.erase(find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch);}).base(), input.end());
}

inline string& trim(string& str, const string& chars = "\t\n\v\f\r ") {
  str.erase(0, str.find_first_not_of(chars));
  str.erase(str.find_last_not_of(chars) + 1);
  return str;
}

// 3. split string
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
  if (!v.empty()) {
    out << '[';
    std::copy(v.begin(), v.end(), ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}
auto SplitString = [](const string &s, char delim = ' ') {
  vector<string> splitteds;
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    splitteds.push_back(item);
  }

  return splitteds;
};

int main() { cout << SplitString("ABC BC E") << "\n\n"; }

// 4. print_array
wchar_t wcstr_v[2] = L"A";

char array[3] = {'B', 'a', 'r'};
string_view array_v(array, size(array));

string cppstr = "Foo";
string_view cppstr_v(&cppstr[0], cppstr.size());

cout << cppstr_v << '\n' << array_v << '\n' << *wcstr_v;  // Foo Bar 65
```

{% endtab %}
{% tab title='java' %}

* character charAt(`idx`): return character in `idx`
* String[] split(`str`A):
* StringTokenizer(BufferedReader)
  * int countTokens(): count the number of tokens
  * boolean hasMoreTokens(): Check if more tokens left
  * string nextToken(): read next token

```java
import java.util.StringTokenizer;

// 1. Print in format
System.out.println(System.getProperty("file.encoding"));  // Print encoding type of file
String.format("%s, %.2f and %d", “string”, 0.01, 12);     // Print file format

getBytes()
split(String regex, int limit)                            // if limit = 0, remove trailing empty strings, if neg, keep

// 2. Print Korean in java
public class a {
  private static void printIt(String string) {
    for (int i = 0; i < string.length(); i++) {
      System.out.print(String.format("U+%04X ", string.codePointAt(i)));
    }
    System.out.println();
  }

  public static void main(String[] args) {
    String han = "한";

    String nfd = Normalizer.normalize(han, Normalizer.Form.NFD);
    printIt(nfd);
    String nfc = Normalizer.normalize(nfd, Normalizer.Form.NFC);
    printIt(nfc);
  }
}

// 3. Count number of words
StringTokenizer stb = new StringTokenizer(new BufferedReader(new InputStreamReader(System.in)).readLine(), " ");
BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
bw.write(Integer.toString(stb.countTokens()));
bw.flush();
bw.close();
```

{% endtab %}
{% tab title='javascript' %}

* charAt / charCodeAt()
* concat()
* constructorendsWith()
* fromCharCode()
* includes()
* lastIndexOf()
* lengthlocaleCompare()
* prototyperepeat()
* search()
* startsWith()
* substr()
* substring()
* toLocaleLowerCase / UpperCase()
* toLowerCase / UpperCase()
* toString()
* trim()
* valueOf()

* split(delim, time)
  * str.split("o").length-1: count number of occurence →
* indexOf()
  * s.indexOf(" ")

* match(): search a string for a match and returns matches

* replace()
  * ("bef", "aft"): only once
  * (/bef/g, "after"): replace all

* slice(start, end): extract parts of a string
  * .slice(1, end - 1): removes first and last char
  * ("000" + n).splice(-4): rihgt pad
  * (n + "000").splice(4): rihgt pad
  * hit.objectID.split('-').slice(0, -1).join('-'): python rsplit

```js
// 1. split_string
var splits = [s.slice(0, i) + s.slice(i + 1)]
```

{% endtab %}
{% tab title='python' %}

* Sequence of unicode Character

* ascii_letters: ascii_lowercase + ascii_uppercase
* digits, punctuation

* count(‘a’): count number of str
* find(sub[, start[, end]]): lowest index in the string where substring sub is found | -1 if not
* index(sub[, start[, end]]): equivalent to find raise value error
* isdigit(): Checks if string only contains 0-9
* isupper() islower(): Return True if upper case or lower case
* join(`iterable`) -> str
* lower() / upper(): convert to upper or lower case
* maketrans()
* partition(word): Search for word, and return a tuple with before, match, after
* replace(“P”, “-”): replace P to -
* rstrip([chs]): default whitespaces | e.x. 'mississippi'.rstrip('ipz') → 'mississ'
* rfind(str, beg=0 end=len(string)): highest index in the string where substring sub is found | -1 if not
* rjust(width[, fillchar]): right justified in a string of specified length
* split(sep=None, maxsplit=-1): using sep as the delimiter string
* strip(): removes chars from side (default whitespace)

![split](images/20210213_152758.png)

* startswith(str, beg=0)): check if starts with str
* swapcase(): all the upper case letters are lower case and vice versa
* title(): Upper only first char

```py
# 1. join
"".join([str(x) for x in l])

# 2. maketrans
tb = 'ab'.maketrans({'a': '1', 'b': '4'}) # create dictionary
'ab'.translate(tb)  # 14
```

{% include 'string-1.test' %}
{% include 'string-2.test' %}
{% include 'split.test' %}
{% include 'join.test' %}

{% endtab %}
{% tab title='shell' %}

* multiple spaces and tab is replaced by space (" preserves space and new line)
* \ to use multiline string
* -z / -n: if string is empty / filled
* -d: if directory exists
* ${#PARAMETER}: length of string
* ${parameter:+word}
* Single quote: No string is escaped
  * added with $'' to use escape characters

* double quote: make string separated by space, prevents globbing

```sh
# 1. Single Quote
AA=100
sh -c "AA=200; echo $AA"    # 100 -> variable is expanded first
sh -c 'AA=200; echo $AA'    # 200 -> variable is not expanded

# I love
# you
echo $'I love\n\'you\''

# 2. Double quote
echo "I
Love you"        # prints in multiline
AA="I
Love you"
echo $AA         # prints in single line unless quoted "$AA" (in bash)
$(( 0377 ))      # expand oct
$(( 0xff ))      # expand hex
```

{% endtab %}
{% tab title='vim' %}

```sh
# 1. String
len(str)
split("one.two.three", '.')    # ['one', 'two', 'three']
tolower('Hello')
'hello ' . name

str2float("2.3")
str2nr("3")
```

{% endtab %}
{% endtabs %}

{% include '.string.prob' %}

## Case

{% include '.case.prob' %}

### Unicode

{% tabs %}
{% tab title='python' %}

* python2 encoding ‘ascii’ encoding
* Unicode → ASCII, code point is < 128, value of the code point, error otherwise

* unicodedata
  * unicodedata.name('/'): SOLIDUS
  * unicodedata.decimal('9'): 9
  * unicodedata.category(): [ex] 'A': Lu
  * unicodedata.bidirectional(): [ex] '한': L
  * unicodedata.lookup(): [ex] 'LEFT CURLY BRACKET' {
  * unicodedata.normalize('NFD', u'\u00C7'): decompose: convert Ç to "C + ̧"
  * unicodedata.normalize('NFC', u'C\u0327'): compose: convert "C + ̧" to Ç

```py
'한'.encode('UTF-8'))            # b'\xed\x95\x9c (bytes)
b'\xed\x95\x9c'.decode('utf-8') # 한 (str)
str(b'\xed\x95\x9c', 'utf-8')   # 한 (str)
f"'한' | u'한' \t '한' ({type('한')})"  # 한

'한'.encode('UTF-8')             # b'\xed\x95\x9c' <class 'bytes'>
b'\xed\x95\x9c'.decode('utf-8') # 한
f"{str(b'hello', 'utf-8')}"
# print(b'\u0660'.decode('utf-8'))

# Python 2
coding: utf-8  # python2 header
type('가')      # <type 'str'>
type(u'가')     # <type unicode'>
'hello'.decode('utf-8')     # byte → str
unicode('hello', 'utf-8')

# python 3
type('한')            # <class 'str'>
'한'.encode('UTF-8')  #
unicode_string.encode(enc)  # unicode → str
byte_string.decode(enc)     # str → unicode
b'hello'.decode('utf-8')    # byte → str
str(b'hello', 'utf-8')

unicode(string[, encoding, errors])  # convert
```

{% endtab %}
{% endtabs %}

{% include '.unicode.prob' %}

## Regex

{% tabs %}
{% tab title='cpp' %}

```cpp
#include <regex>
using namespace std;

// 1. Regex match
string a = "GeeksForGeeks";
regex b("(Geek)(.*)");
regex_match(a, b);

// 2. replace string
string defangIPaddr(string address) {
  return regex_replace(address, regex("[.]"), "[.]");     // regex(“\\.”)
}
```

{% endtab %}
{% tab title='javscript' %}

* /()/;

```js
"a,b".match(/([^,]*,(.*)/))   // split once using regex
```

{% endtab %}
{% tab title='python' %}

> re

* re.DOTALL: match new line
* re.I: case insensitive matching
* r"(?<=...)": positive lookbehind
* r"(?<!...)": negative lookbehind
* r"(?=...)": positive lookahead. A (?!B) only match if A followed by B
* r"(?!...)": negative lookahead. A (?!Sam) match Tom Sam

* Escape \\: for dot(.), dash(-), braces()), bracket(])

* findall(pattern, string, flags=0): Return all non-overlapping matches of pattern
* finditer(pattern, string)
* match(): match at the beginning of the string
* search(): Checks for one match
* split(pattern, string, maxsplit=0): split(r'\W+', 'Words, words') ⇒ ['Words', 'words', '']

* Word
  * r"[a-c]": contain a, b, c
  * r"[^a-c]": not contain a, b, c
  * r"^a": starts with a
  * r"a$": ends with a
  * r"\b(words)\b": word boundary
  * r".*a": greedy match (all the way to the end, and then backtrack to a)
  * r".*?": non-greedy (will try to match extra characters until it matches 1)
  * "\n": references the nth capturing group
  * "^([aeiou]).+\1$": Starts and End with same vowel
  * "^\d\d(-?)\d\d\1\d\d\1\d\d": 12345678 or 12-34-56-78
  * r"一-龥": Chineses Character
  * r"가-힇": Korean Character
  * r"ぁ-ゔ|ァ-ヴー|々〆〤": Japanese Character

* Length
  * {5}: five character
  * {2,6}: between 2, 6
  * \+ / *: 1 / 0 or more
  * ?: optional

* Conditional
  * (cat | dog): cat or dog

* Type
  * r"\w": Unicode letter, ideogram, digit, underscore  ; Capital <>
  * [r"\d", r"\D"]: digit | Non-digit
  * [r"\s", r"\S"]: space, tab, newline | non-space, tab, newline
  * r"\t": tab

* match()
  * expand(template): obtained by doing backslash substitution on template
  * group(n): 0 for entire match, n th match
  * groups(): Tuples containing all match
  * groupdict(): (?P<first_name>\w+) → firstname:
  * string: The string passed to match() or search()

* findall()
  * ("{[^{}]+}", "{A}, {{B}} {{C}, {D}, E}"): Nested Parenthesis
  * ("\((?:1|82)\)", "(82) (821) (1) 82 1"): phone number
  * ("(?i)\d{2}:\d{2}(?:am|pm)", "02:40pm 12:29AM"): Non capture group
  * (r'(.*?)D', "ABCD, ABD"): Grap little as possible
  * (r'([a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+)', "rbtmd10@gmail.com, fakeemail@@f.com"): email

* search()
* split()
* sub()
  * re.sub('\W+', ' ', ex): made up string to Test 2 한국different regex23 methods

```py
# 1. findall
ex = 'made|up string*.to>>>>Test----   2""""""한국different~regex23-methods'
re.findall('\S+', ex)     # ['made|up', 'string*.to>>>>Test----', '2""""""한국different~regex23-methods']
re.findall('\w+', ex)     # ['made', 'up', 'string', 'to', 'Test', '2', '한국different', 'regex23', 'methods']
re.findall(dr, ex)        # ['23']
re.findall('\w{4}\-', ex) # ['Test-', 'ex23-']

# 2. Search
txt = "The rain in Spain"
x = re.search(r"\bS\w+", txt)
print(x.string)    # "The rain in Spain"
ex = 'made|up string*.to>>>>Test----   2""""""한국different~regex23-methods'
re.search('\w+', ex) #   <re.Match object; span=(0, 4), match='made'>
re.search('\w+', ex)    # end : 4, group : made, groupdict : {}, groups : (), span : (0, 4), start : 0

# 3. split
ex = 'made|up string*.to>>>>Test----   2""""""한국different~regex23-methods'
re.split('\s', ex)  # ['made|up', 'string*.to>>>>Test----', '', '', '2""""""한국different~regex23-methods']
re.split('\s+', ex) # ['made|up', 'string*.to>>>>Test----', '2""""""한국different~regex23-methods']
re.split('\w+', ex) # ['', '|', ' ', '*.', '>>>>', '----   ', '""""""', '~', '-', '']
re.split('\W+', ex) # ['made', 'up', 'string', 'to', 'Test', '2', '한국different', 'regex23', 'methods']
```

{% endtab %}
{% endtabs %}

### Alternation

{% include '.alternation.prob' %}

### Anchor

| Syntax | Description                                                                                 |
| ------ | ------------------------------------------------------------------------------------------- |
| $      | Matches before final line break in string in addition to matching at the very end of string |
| ^      | matching at the start of each line in the string                                            |
| \A     | Start of the string                                                                         |
| \Z     | end of the string the regex pattern is applied to                                           |

{% include '.anchor.prob' %}

### Assertion

| Syntax  | Term                          | Meaning                                |
| ------- | ----------------------------- | -------------------------------------- |
| x(?=y)  | Lookahead assertion           | Match x only if x is followed by y     |
| x(?!y)  | Negative lookahead assertion  | Match x only if x is not followed by y |
| (?<=y)x | Lookbehind assertion          | Match x only if x is preceded by y     |
| (?<!y)x | Negative Lookbehind assertion | Match x only if x is not preceded by y |

{% include '.assertion.prob' %}

### Flag

{% include '.flag.prob' %}

### Group

{% include '.group.prob' %}

### Referencing

{% include '.referencing.prob' %}

### Repetition

| Syntax    | Meaning                 |
| --------- | ----------------------- |
| { n }     | Match exactly n times   |
| { n ,}    | Match at least n times  |
| { n , m } | Match from n to m times |

{% include '.repetition.prob' %}

### Quantifier

| Syntax | Meaning                  |
| ------ | ------------------------ |
| \*     | Match zero or more times |
| +      | Match one or more times  |
| ?      | Match zero or one time   |

{% include '.quantifier.prob' %}
