# Math

{% tabs %}
{% tab title='vim' %}

* vscode: Install Mactex www.tug.org/mactex/mactex-download.html
  * sudo tlmgr update --self
  * sudo tlmgr install latexmk

* vscode.Markdown-preview-enhanced

  ```json
  // settings.json
  {
    "markdown-preview-enhanced.mathInlineDelimiters": [[ "$$", "$$" ]]
  }
  ```

{% endtab %}
{% endtabs %}

## Add

* +: Add two numbers

{% tabs %}
{% tab title='nasm' %}

* mov `a` `b`: move `b` to `a`
* add `a` 1: add 1 to `a`
  * Only valid for register
* incl `a`: increment `a` by 1

```nasm
# counter += 1
mov rax, qword ptr [rbp - 8]
mov ecx, dword ptr [rax]
add ecx, 1
mov dword ptr [rax], ecx
```

{% endtab %}
{% tab title='python' %}

{% include 'add.test' %}

{% endtab %}
{% endtabs %}

{% include '.add.prob' %}

## Subtract

* -: subtract two numbers

{% tabs %}
{% tab title='python' %}

{% include 'subtract.test' %}

{% endtab %}
{% endtabs %}

{% include '.subtract.prob' %}

## Multiply

* [Basic Multiplication](https://www.youtube.com/watch?v=mvOkMYCygps)
* [Multiplication table](https://www.youtube.com/watch?v=xO_1bYgoQvA&list=PLD45913551291638C)
* [- * - is positive 1](https://www.youtube.com/watch?v=rK4sXm_MPWo)
* [- * - is positive 2](https://www.youtube.com/watch?v=pzQY-9Nmtws)
* [Order of operation 2](https://www.youtube.com/watch?v=ClYdw4d4OmA)
* [Order of operation 2](https://www.youtube.com/watch?v=GiSpzFKI5_w)

{% include 'multiply.test' %}
{% include 'multiply-2.test' %}

{% include '.multiply.prob' %}

## Quotient

{% tabs %}
{% tab title='python' %}

* //: integer division

{% endtab %}
{% tab title='shell' %}

* /: integer division

```sh
read a b
echo $((a/b)).$((a%b*1000000000/b))
```

{% endtab %}
{% endtabs %}

{% include 'quotient.test' %}
{% include '.quotient.prob' %}

## Division

* [Idea of Division](https://www.youtube.com/watch?v=QI6x0KNxiCs)
* [Multiplication to division](https://www.youtube.com/watch?v=qcMJ1pN36r4)
* [Dividing 0](https://www.youtube.com/watch?v=SQzjzStU1RQ)
* [Divising negative](https://www.youtube.com/watch?v=bQ-KR3clFgs)
* [Unknowns Multiplication](https://www.youtube.com/watch?v=TqAtt3g6Tkc)
* [Partial quotient](https://www.youtube.com/watch?v=Ws4Zq-gceSY)
* [Long Division](https://www.youtube.com/watch?v=KFzcwWTEDDI)
* [Adding fraction](https://www.youtube.com/watch?v=bcCLKACsYJ0)
* [Improper Fraction](https://www.youtube.com/watch?v=-sA-vI2a2mM)
* [Comparing Fraction](https://www.youtube.com/watch?v=8OKTrN0uT-Q)
* [Addming mixed number](https://www.youtube.com/watch?v=4TBVB4hLQhY)

{% tabs %}
{% tab title='python' %}

```py
from decimal import Decimal

# 1. Precise float division
a, b = map(Decimal, input().split())
print(a / b)
```

{% endtab %}
{% endtabs %}

{% include 'division.test' %}

{% include '.division.prob' %}

## Log

* Definition
  $$ y=\log _{b}(x) \Leftrightarrow b^{y}=x $$

* Quotient rule
  $$ \log_{a}\left(\frac{x}{y}\right)=\log_{a} x-\log _{a} y $$

* Change of base
  $$ \log_{a} x=\frac{\log_{b} x}{\log _{b} a} $$

{% include '.log.prob' %}

## Modulo

| Property     | Example                                        |
| ------------ | ---------------------------------------------- |
| communative  | (a \* b) % N = (a + b) % n                     |
| Distributive | (a \* (b + c)) % N = ((a \* b) + (a \* c)) % N |

* [Remainder](https://www.youtube.com/watch?v=P1qyjdh_sIw)

{% tabs %}
{% tab title='cpp' %}

* mod on negative number will still get a negative number

{% endtab %}
{% tab title='java' %}

* mod on negative number will still get a negative number

{% endtab %}
{% tab title='python' %}

* %: modulo (remainder)
* divmod() -> Tuple(quotient: int, remainder: int)

{% endtab %}
{% tab title='shell' %}

* %: modulo (remainder)

{% endtab %}
{% endtabs %}

{% include 'modulo.test' %}

{% include '.modulo.prob' %}

## Round

{% include 'round.test' %}

{% include '.round.prob' %}

## Exponent

* [Intro to Exponent](https://www.youtube.com/watch?v=XZRQhkii0h0)
* [Negative Exponent](https://www.youtube.com/watch?v=JnpqlXN9Whw)
* [Fractional Exponent](https://www.youtube.com/watch?v=tOuCdKqO6-s)
* [Square Root](https://www.youtube.com/watch?v=mbc3_e5lWw0)
* [Cube Root](https://www.youtube.com/watch?v=87_qIofPwhg)

{% tabs %}
{% tab title='python' %}

* pow(`x`, `y`, `base`): equivalent to (x ** y) % base
* Decimal()
  * value ="0"
  * quantize(): rounds a number to a fixed exponent
    * rounding=ROUND_DOWN, ROUND_UP, ROUND_HALF_DOWN

```py
import decimal

# 1. Concise
decimal.getcontext().prec = 5000
decimal.Decimal(0.999592935235).sqrt()
```

{% endtab %}
{% endtabs %}

{% include 'exponent.test' %}

{% include '.exponent.prob' %}

## Complex

{% tabs %}
{% tab title='python' %}

* complex(`re`, `im`) -> complex: complex number with real part `re`, imaginary part `im` ([ex] (1, **0**))

{% endtab %}
{% endtabs %}

## Sigma

{% include '.sigma.prob' %}
