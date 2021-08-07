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
{% tab title='sv' %}

* truncate decimal when divide
* negative number truncate to infinity

| Verilog                             | Systemverilog                                              |
| ----------------------------------- | ---------------------------------------------------------- |
| hardware description language (HDL) | Combination of HDL and Hardware Verification Language(HVL) |
| hierarchy of modules                | based on classes                                           |
| Supports Structured paradigm        | structured, OOP                                            |

* Standardized as IEEE 1364
  * verilog 95, 2001 (new features), 2005
  * SystemVerilog: superset of Verilog
* free formatiting: spaces can be added freely
* [Install on mac](https://medium.com/macoclock/running-verilog-code-on-linux-mac-3b06ddcccc55)
* iverilog -o hello hello.v
* vvp hello

* begin / end: when if, always block are multiline
* localparam: constants in verilog

* Initial block: is not synthesizable and cannot be converted into a hardware schematic with digital elements

![Flow diagram](images/20210413_150755.png)

```v
// Gate Implementation
module is_prime_gates(input c, b, a output P);
  wire w1, w2, w3;
  not(w1, c);
  and(w2, w1, b);
  and(w3, a, c);
  or(P, w2, w3);
endmodule

// Boolean Implemenation
module is_prime_gates(input c, b, a output P);
  assign P = (c & a) | (~c & b);
endmodule

// Procedural Implemenation
module is_prime_gates(input c, b, a output P);
  wire [2:0] cba;
  always @ (cba)
    if (cba == 3'd2 || cba == 3'd3 || cba == 3'd5 || cba == 3'd7)
      P = 1'b1;
    else:
      P = 1'b0;
endmodule
```

![Verilog Operation Precedence](images/20210406_222500.png)

* arithmetic

| symbol | description                            |
| ------ | -------------------------------------- |
| +      | add                                    |
| -      | subtract                               |
| *      | multiply                               |
| /      | divide may not synthesize              |
| %      | modulus (remainder) may not synthesize |
| **     | power may not synthesize               |
| &&     | and                                    |
| \|\|   | or                                     |
| {}     | concatenate binary or replicate        |

* sensitivity list is an expression that defines when the always block executed

* posedge: trigger a flop at positive (rising) edge of clock
* negedge: triggers on the negative (falling) edge

```v
// 1. Time
always clk = ~clk;     // results in infinite loop
always #10 clk = ~clk; // clock inversion is done after every 10-time units


// 2. Clock divider
module clock_divider(input clk_in, output reg clk_out, input reset, input [31:0] ratio);
  reg [31:0] counter;

  always @ (posedge clk_in, negedge reset)
    if (reset == 0) begin
      counter <= 32 * d0;
      clk_out = 0;
    end
    else if (counter == ratio - 1) begin
      $display("ratio-1 = counter:%d", counter);
      clk_out <= 0;
      counter <= 32'd0;
    end
    elif if (counter == ratio / 2 = 1) begin
      $display("ratio/2 - 1 = counter:%d", counter);
      clk_out <= 1;
      counter <= counter+1;
    end
    else
      counter <= counter+1;

module clock_divider_TB();
  reg clk_fast, reset;
  wire clk_slow;

  always #5 clk_fast = ~clk_fast;

  clock_divider DUT_divider(clk_fast, clk_slow, reset, 32'd100_000);

  initial begin
    clk_fast=0; reset=0; #999_996;
    reset=1;
    #10_000_000;
    $stop;
  end
```

![master_slave_jk](images/20210413_152734.png)

```v
module JK(input J, input K, input clk, output reg Q, output QN);
  assign QN = ~Q;
  always @ (negedge clk)
    case ({J, K})
      2'b00 : Q <= Q;
      2'b01 : Q <= 0;
      2'b10 : Q <= 1;
      2'b11 : Q <= QN;
    endcase
endmodule
```

* Wires: Make connetions between elements
  * Implement nets (or nodes) driven by signal
  * Many not always have a value
  * b: binary
  * o: octal
  * d: decimal
  * h: hexadecimal

* Gates: buffer_type[instance_name](output, input, input, ...);
  * nand(`x`, `a`, `b`): compute `a` nand `b` and stores in `x`
  * and(`x`, `a`, `b`): compute `a` and `b` and stores in `x`
  * or(`x`, `a`, `b`): compute `a` or `b` and stores in `x`
  * xor(`x`, `a`, `b`): compute `a` xor `b` and stores in `x`

* Buffers
  * buffer_type[instance_name](output, ..., output, input);
  * buf()
  * not(`x`, `a`): negate `a` and stores in `x`

* Tristate
  * bufif1 [instance_name](output, input, enable)

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
* assign: doesn't need posedge, negedge, always evaluated
  * only works for one line

* always: use <=
  * @ (`event`): indicates that the block will be triggered in `event`
  * (`x`) [statements]: execute always block whenever value of `x` change
  * (posedge clk or negedge rstn): triggered at the positive edge of clk or negative edge of rstn

```v
/* 1. synchronous_reset_d-ff.v */
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

/* 2. shift using <= */
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

/* 3. Different Size assign */
// smaller -> larger
logic signed[3:0] a = 1010; // -6 signed-two's comp (-8 ~ 7)
logic signed[7:0] b;
assign b = a;               // 0'b11110101 if both signed we sign extend

logic [3:0] c = 1010;       // 10 unsigned by default (0 ~ 15)
logic [7:0] d;
assign d = c;               // b = 8'b00001010; zero extend 4 to 8

// truncate
logic [3:0] e;
assign e = b;               // e = 4'b1010 {{4{a[3]}},a[3:0]};
assign d = a;               // 0000_1010 = 10 (Not recommended)
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
