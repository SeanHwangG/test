# Operation

* [What is a function?](https://www.youtube.com/watch?v=kvGsIo1TmsM)

{% tabs %}
{% tab title='Makefile' %}

| Symbols | Meaning                   |
| ------- | ------------------------- |
| @       | Not echoed as it executed |

{% endtab %}
{% tab title='python' %}

![Operation](images/20210213_030253.png)

| Operator | Meaning        | Example                                                                              |
| -------- | -------------- | ------------------------------------------------------------------------------------ |
| +        | addition       | "1" + "1" = "11" (for str concat) int("1") + int("1") = 2 (convert to int if needed) |
| \*       | multiplication | "1" \* 5 = "11111" (for str * int)                                                   |
| **       | exponent       | 2 \* 3 = 8 $\\$ 4 \** (0.5) = 2 (sqrt)                                               |
| -        | subtraction    |                                                                                      |
| /        | division       | 3 / 2 = 1.5                                                                          |
| //       | floor division | 8 // 3 = 2                                                                           |
| \        | modular        | 7 % 3 = 1, 5.1 % 1 = 0.1                                                             |

{% include 'operation-1.test' %}

{% endtab %}
{% tab title='verilog' %}

* truncate decimal when divide
* negative number truncate to infinity

{% endtab %}
{% endtabs %}

## Assignment

{% tabs %}
{% tab title='makefile' %}

* :=: Expanded when they are defined
* =: Expanded when they are used

```make
MY_VAR := $(shell echo whatever)
```

{% endtab %}
{% tab title='python' %}

```py
a = [1,2]
b = copy.copy(a) # equivalent to [e for e in a], a[:]

# deepcopy()     preserve the graphical structure of the original compound data
a = [1,2]
b = [a,a]        # there's only 1 object a
c = copy.deepcopy(b)

c[0] is a        # return False, a new object a' is created
c[0] is c[1]     # return True, c is [a',a'] not [a',a'module.md']
```

{% endtab %}
{% tab title='sv' %}

* =: blocking assignment, used in combinational logic
  ![= assignment](images/20210505_004647.png)
  ![Assignment](images/20210413_150409.png)

* <=: assign using temp, used in sequential logic
  ![Non-blocking](images/20210413_150558.png)

* always_comb (assign): continuously evaluating
* always / always_ff: only changes when variable in @, changes
  * always use <=

```v
// 1. synchronous_reset_d-ff.v
module dff_sync_reset (
  input wire data, clk, reset,
  output reg q
);

always_ff @ (posedge clk)
if (~reset)
  q <= 1*b0;
else
  q <= data;
end module

// 2. shift using <=
module shift_reg(input clk, reset, a, output logic d):

logic b, c;
always_ff @(posedge clk)
  if (reset) begin
    b <= 0;
    c <= 0;
    d <= 0;
  end
  else begin
    b <= a;
    c <= b;
    d <= c;
end

end module

// Blocking vs non blocking assignment
module assignments(input i, input clk, output reg o);
  reg temp;
  always @ (posedge clk) begin
    temp = i; // <=
    o = temp; // <=
  end
end module
```

{% endtab %}
{% endtabs %}

## Concat

{% tabs %}
{% tab title='v' %}

```v
// concat_replicate
wire[1:0] a = 2b'01;
wire[2:0] b = 3b'001;
wire[3:0] c ;
assign c = {a, b} // c = 01001 is created using a and b;

assign c = { 2{a}, 1'b0 } // c = 01010 i.e. a is repeated two times i.e. 01-01
```

{% endtab %}
{% endtabs %}

{% include '.concat.prob' %}

## Eval

{% tabs %}
{% tab title='python' %}

> ast

* helps Python applications to process trees of the Python abstract syntax grammar

* literal_eval(): error on "rm -rf", so safer than eval
  * `str`: accept str, num, tuples, lists, dicts, booleans, None

> js2py

```py
import js2py

code = " function test(a, b) { return a + b; } "
js_func = js2py.eval_js(code)
print(js_func(1, 2))
```

{% endtab %}
{% endtabs %}

{% include '.eval.prob' %}

## Overloading

{% tabs %}
{% tab title="cpp" %}

* . /:: / ? /: / sizeof - cannot be overloaded
* operator++();        # overload for ++a
* operator++(int);     # overload for a++

* How computer overload function
  1. Find function with exact type
  2. Char, unsigned char, short → int / Unsigned short → int, unsigned int / Float →  double / Enum →  int
  3. float → int / Enum →  double, float / 0 → pointer, float, double / pointer → void pointer
  4. Function Overload
  5. Defined overloading

```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1. outside of class → equal binary operators implement this operator // as a non-member function.
bool operator<(const c& p1, const c& p2) {
  return p1.data < p2.data;
}

// 2. within class
// a unary operator or a binary operator doesn’t treat both of operands equally (it will change its left)
// useful to make it a member function of left operand’s type, if it has to access operand's private parts
bool operator<(c p) const {
  return n < p.n;
}

// 3. create struct
struct Compare {
  bool operator()(c a, c b) {
    return a.data < b.data;
  }
};

// 4. Complex class
class Complex {
 private:
  double real, img;

 public:
  explicit Complex(double r) : real(r){};

  Complex(double r, double i) : real(r), img(i) {}

  Complex operator+(const Complex &obj) const { return Complex(real + obj.real, img + obj.img); }

  Complex operator++() {  // ++var
    Complex temp(*this);
    real++;
    return temp;
  }

  Complex &operator++(int) {  // var++
    real++;
    return *this;
  }

  Complex &operator+=(const Complex &c) {
    (*this) = (*this) + c;
    return *this;
  }

  friend ostream &operator<<(ostream &os, const Complex &c) {
    return os << c.real << " + " << c.img << "i";  // can access private
  }

  double &operator[](const int index) { return index == 0 ? real : img; }
  Complex abs() {
    real *= -1;
    img *= -1;
    return *this;
  }

  double val() const { return real * real + img * img; }
};
bool operator<(const Complex &p1, const Complex &p2) { return p1.val() < p2.val(); }

Complex a = Complex(1, 0);
Complex b = {1, 2};
if (a < b) {
  cout << "b is greater \n";
}
a[0] = 2;
cout << "a + b \t" << a + b << endl;
a += b;
cout << "a += b \t" << a << "\t" << a[0] << "\t" << a[1] << endl;

a.abs().abs();
cout << "a.abs().abs() \t" << a << "\n\n";  // should be Complex &abs()

// Complex c = 3; doesn't work because explicit
```

{% endtab %}
{% tab title='python' %}

* Dunder Method: method used with \_\_<dunder_name>__
  * add: when a + b
  * code: co_varnames
  * hash: immutable built-in objects are hashable | hashable equal objects have same hash
  * init: called to initialize the object | cannot return value
  * len: same as len('test')
  * new(cls): called when object is created | cls represents class that is needed to be instantiated
  * repr: to be unambiguous, compare / readable
  * slots
    * only allocate space for a fixed set of attributes in slots, Reduce RAM
  * PyPy by default

```py
# __repr__
return "Class: '{}' \n{!r}".format(self.__class__.__name__, self.__dict__)

# __slots__
class MyClass(object):
  __slots__ = ['name', 'identifier']
  def __init__(self, name, identifier):
    self.name = name
  self.identifier = identifier
    self.set_up()

setitem   # Setter
getitem   # Getter
class Building(object):
  def __init__(self, floors):
    self._floors = [None]*floors
  def __setitem__(self, floor_number, data):
    self._floors[floor_number] = data
  def __getitem__(self, floor_number):
    return self._floors[floor_number]
building1 = Building(4)   # Construct a building with 4 floors
building1[0] = 'Reception'
building1[1] = 'ABC Corp'
building1[2] = 'DEF Inc'
print( building1[2] )
```

{% endtab %}
{% tab title='static.py' %}

```py
# Static
@staticmethod
def is_workday(day):
  return day.weekday() != 5 and day.weekday() != 6

# Overloading multiple constructor
@classmethod
def from_string(cls, emp_str):
  first, last = emp_str.split(‘-’)
  return cls(first, last)
```

{% endtab %}
{% endtabs %}

## Swap

{% include '.swap.prob' %}
