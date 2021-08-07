# Algebra

## Linear Equation

* [Linear Equation 1](https://www.youtube.com/watch?v=_y_Q3_B2Vh8)
* [Linear Equation 2](https://www.youtube.com/watch?v=AOxMJRtoR2A)

{% include 'linear-equation-1.test' %}
{% include 'linear-equation-2.test' %}

## Simultaneous Equations

{% include '.simultaneous-equations.prob' %}

## Quadratic Equation

{% include '.quadratic-equation.prob' %}

## Prime

* 25% of the numbers from 1 through 100 inclusive are prime
* 21% of the numbers from 101 through 200 inclusive are prime
* 14% of the numbers from 901 through 1,000 inclusive are prime
* 9% of the numbers from 9,001 through 10,000 inclusive are prime

{% include 'prime.test' %}

* [Prime numbers](https://www.youtube.com/watch?v=mIStB5X4U8M)
* [Prime Factorization](https://www.youtube.com/watch?v=XWq8bplP-_E)

* Check if a number is prime

  | -                  | Run Time     |
  | ------------------ | ------------ |
  | Basic loop         | O(N ^ 0.5)   |
  | Miller rabin       | O(k log^3 n) |
  | Miller rabin + FFT | O(k log^2 n) |

* Find all primes under N

  | -                        | Run Time       | Space |
  | ------------------------ | -------------- | ----- |
  | Eratosthenes             | O(N log log N) | O(N)  |
  | Manipulated Eratosthenes | O(N)           | O(N)  |

> Example

* Proof Fermat little theorem
  * When p is prime and a is not multiple of p then

  $$
  a^{p-1} \bmod p=1 \\
  ↔ a^{p-1} \equiv 1(\bmod p)
  $$

{% include '.prime.prob' %}

### Eratosthenes

{% tabs %}
{% tab title='python' %}

```py
# 1. Updated
for every number i where i varies in range(2, N):
  Check if the number is prime. If the number is prime, store it in prime array.

for every prime numbers j less than or equal to the smallest prime factor p of i:
  Mark all numbers j*p as non_prime.
  Mark smallest prime factor of j*p as j
```

{% endtab %}
{% endtabs %}

{% include '.eratosthenes.prob' %}

> Reference

<https://www.geeksforgeeks.org/sieve-eratosthenes-0n-time-complexity/>

### Miller Rabin

* Probablistic primality test algorithm

* For small n, you can use few a values

| tested a               | maximum n           |
| ---------------------- | ------------------- |
| 2, 3                   | 1,373,653           |
| 31, 73                 | 9,080,191           |
| 2, 7, 61               | 4,759,123,141       |
| 2, 3, 5, 7, 11, 13, 17 | 341,550,071,728,321 |

> Example

* Proof Miller Rabin
  * If x is odd, x - 1 is even which can be
  $$ x - 1 = 2^s \cdot d, (d is odd) $$
  * Using Fermat's little theorem
  $$ a^{x-1} \equiv 1 \bmod x \Longleftrightarrow a^{2^{s} d}-1 \equiv 0 \bmod x $$
  $$
  ↔(a^{2^{s-1}} d+1)(a^{2^{s-1} d}-1) \equiv 0 \bmod x \\
  ↔(a^{2^{s-1} d}+1)(a^{2^{s-2} d}+1)(a^{2^{s-2} d}-1) \equiv 0 \bmod x \\
  \vdots \\
  ↔(a^{2^{s-1} d}+1)(a^{2^{s-2} d}+1) \cdots(a^{d}+1)(a^{d}-1) \equiv 0 \bmod x
  $$

{% include '.miller-rabin.prob' %}

### Euler Phi

{% include '.euler-phi.prob' %}

## Number Theory

{% tabs %}
{% tab title='python' %}

```py
# 1. modular multiplicative inverse
def modInverse(a, m):
  for x in range(1, m):
    if (a * x) % m == 1:
      return x
  return 1
```

{% endtab %}
{% endtabs %}

* Modular multiplicative inverse: an integer 'x' such that
  * a x ≅ 1 (mod m)
  * The multiplicative inverse of “a modulo m” exists iff a and m are relatively prime
  * [ex] Input: a = 3, m = 11, Output: 4 (Since (4*3) mod 11 = 1, 4 is modulo inverse of 3(under 11))

* Zellar's Formula
  $$
  (d+\lfloor\frac{13(m+1)}{5}\rfloor+y+\lfloor\frac{y}{4}\rfloor+\lfloor\frac{y / / 100}{4}\rfloor-2 y / / 100) \% 7
  $$

{% include '.number-theory.prob' %}

### Divisibility Rule

{% include '.divisibility-rule.prob' %}

### Euclidean

* [Euclidean-algorithm)](https://velog.io/@yerin4847/W1-%EC%9C%A0%ED%81%B4%EB%A6%AC%EB%93%9C-%ED%98%B8%EC%A0%9C%EB%B2%95)
* [GCD](https://www.youtube.com/watch?v=bLTfBvkrfsM)
* [LCM 1](https://www.youtube.com/watch?v=znmPfDfsir8)
* [LCM 2](https://www.youtube.com/watch?v=QUem_2dkB9I)
* [LCM 3](https://www.youtube.com/watch?v=D6yHKOYJiso)

{% include '.euclidean.prob' %}

### Lucas

* Faster computation for $$ \left(\begin{array}{l} n \\ k \end{array}\right) \bmod p $$

$$
\begin{array}{l}
n=n_{m} p^{m}+n_{m-1} p^{m-1}+\cdots+n_{1} p+n_{0}
\end{array}
$$
$$
\begin{array}{l}
k=k_{m} p^{m}+k_{m-1} p^{m-1}+\cdots+k_{1} p+k_{0}
\end{array}
$$

$$
\left(\begin{array}{l} n \\
k \end{array}\right) = \prod_{i=0}^{k}\left(\begin{array}{l}
n_{i} \\ k_{i} \end{array}\right)(\bmod p)
$$

> Example

* $$ \left(\begin{array}{c} 1432 \\ 342 \end{array}\right) $$ mod 7

  $$
  \left(\begin{array}{c}
  1432 \\ 342
  \end{array}\right) \equiv\left(\begin{array}{l}
  4 \\ 0
  \end{array}\right) \cdot\left(\begin{array}{l}
  1 \\ 6
  \end{array}\right) \cdot\left(\begin{array}{l}
  1 \\ 6
  \end{array}\right) \cdot\left(\begin{array}{l}
  4 \\ 6
  \end{array}\right)(\bmod 7)
  $$

{% include '.lucas.prob' %}

### FFT

{% include '.fft.prob' %}

## Binary

| Operation | Meaning                         | Example                           |
| --------- | ------------------------------- | --------------------------------- |
| x \| y    | bitwise or of x and y           | 5 (0101) \| 12 (1100) = 13 (1101) |
| x ^ y     | bitwise exclusive or of x and y | 5 (0101) ^ 12 (1100) = 9 (1001)   |
| x & y     | bitwise and of x and y          | 5 (0101) & 12 (1100) = 8 (0100)   |
| x << n    | x shifted left by n bits        | 5 (0101) << 1 = 10 (1010)         |
| x >> n    | x shifted right by n bits       | 5 (0101) >> 1 = 2 (0010)          |
| ~x        | the bits of x inverted          | ~5 (0101) = -6 (11011)            |

![Bitwise Operator](images/20210206_123607.png)

* [Binary](https://www.youtube.com/watch?v=ku4KOFQ-bB4)
* [Decimal to Binary](https://www.youtube.com/watch?v=H4BstqvgBow)
* [Adding in binary](https://www.youtube.com/watch?v=RgklPQ8rbkg)
* [Multiplying in binary](https://www.youtube.com/watch?v=xHWKYFhhtJQ)
* [Hexadecimal](https://www.youtube.com/watch?v=4EJay-6Bioo)
* [Bin to Hex](https://www.youtube.com/watch?v=8T4F7WboWPQ)

{% tabs %}
{% tab title='cpp' %}

* Binary

```cpp
// 1. Basic bitset usage
bitset<32>(153).to_string()
bitset<32> bin(52);
bin[1] = 1;
cout << bin.count();                    // return the number of set bit
cout << hex << n;

// 2. IO binary
string s;
cin>>s; // Suppose s = "100100101"
int n = (int) bitset<64>(s).to_ulong(); // read as binary
bitset<16> y(15); // output as binary
cout << y << '\n';
```

{% endtab %}
{% tab title='python' %}

* Negative shift counts are illegal and cause a ValueError to be raised
* A left shift by n bits is equivalent to multiplication by pow(2, n)
* A right shift by n bits is equivalent to floor division by pow(2, n)
* bit_length(): number of bits necessary to represent an integer in binary
* from_bytes(bytes, byteorder, *, signed=False) -> int
  * integer represented by the given array of bytes
* to_bytes(): return array of bytes representing an integer

```py
# 1. bit operation
n&-n           # Get lowest set bit
(n&(n-1))==0   # Check power of two

# 2: Bit conversion
int('0b1111')  # 15    (2 → 10)
int('A0', 16)  # 160   (16 → 10)
bin(11)        # '0b1011' (10 → 2)
oct(15)        # '0o17'   (10 → 8)
hex(10)        # '0xA'    (10 → 16)

print('2', '10', '16')   # table
for i in range(50):
  print(bin(i)[2:], '\t', i, '\t', hex(i)[2:])
```

{% include 'binary.test' %}

{% endtab %}
{% tab title='shell' %}

* od: octal, decimal, hex, ASCII dump
  * -i: same as -t dI, select decimal ints

  ```sh
  od -i binary.out
  # 0000000           0           1           2           3
  # 0000020           4           5           6           7
  # 0000040           8           9          10          11
  ```

{% endtab %}
{% tab title='sv' %}

| symbol | description |
| ------ | ----------- |
| &      | and         |
| ^      | xor         |
| ~&     | or          |
| &~     | nand        |

```v
// Gate Level half adder
and(Cout, a, b);
xor(S, a, b);

// RTL half adder
assign {Cout, S} = a + b;
```

{% endtab %}
{% endtabs %}

{% include '.binary.prob' %}

### Nary

{% include '.nary.prob' %}

### Bit shift

{% tabs %}
{% tab title='sv' %}

| symbol | description                           |
| ------ | ------------------------------------- |
| >>     | right shift                           |
| <<     | left shift                            |
| >>>    | right shift with MSB shifted to right |
| <<<    | same as <<                            |

{% endtab %}
{% endtabs %}

{% include '.bit-shift.prob' %}

### And Or

{% tabs %}
{% tab title='python' %}

{% include 'and-or.test' %}

{% endtab %}
{% endtabs %}

{% include '.and-or.prob' %}

### Xor

{% tabs %}
{% tab title='python' %}

```py
# 1. xor every element
nums = [1, 2, 3, 4, 5]
reduce(lambda x, y: x ^ y, nums)
```

{% endtab %}
{% endtabs %}

{% include '.xor.prob' %}
