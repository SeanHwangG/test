# Conditional

* avoid nested conditional as it's hard to follow, some objects might not fully initialized

{% tabs %}
{% tab title='java' %}

* public int compareTo(Object obj)
  * return 0: if the obj is equal to the other string
  * return < 0: if the obj is less than the other obj
  * return> 0: if the obj is greater than the other obj

{% endtab %}
{% tab title='javascript' %}

* ===: returns true if both operands are of the same type and contain the same value

```js
// 1. compare address
var x = "John";
var y = new String("John");
(x === y)     // false

// 2. All of these evaluate to true
console.log(false == '0');
console.log(null == undefined);
console.log(" \t\r\n" == 0);
console.log('' == 0);
if ({}) // ...
if ([]) // ...
```

{% endtab %}
{% tab title='Makefile' %}

```make
django_cont := $(shell docker-compose ps -q django)

.PHONY: check_env
check_env:
ifndef COMPOSE_FILE
  $(error env COMPOSE_FILE is undefined ([ex] export COMPOSE_FILE=local.yml))
endif
```

{% endtab %}
{% tab title='python' %}

| Operator | Description                                           |
| -------- | ----------------------------------------------------- |
| >        | greater than                                          |
| <        | less than                                             |
| ==       | equal to                                              |
| is       | compare object's address (never changes once created) |
| <=       | less or equal to                                      |
| >=       | greater or equal to                                   |
| !=       | not equal to                                          |

* any object is consider to be True unless it \_\_bool\_\_ defined as False or \_\_len__ is 0
* "", (), [], {}, set(), range(0), 0, 0.0, 0j, Decimal(0), Fraction(0, x) are False

{% include 'conditional.test' %}
{% include 'logical.test' %}

{% endtab %}
{% tab title='shell' %}

| Operator | Meaning                            |
| -------- | ---------------------------------- |
| t1 -a t2 | AND                                |
| t1 -o t2 | OR                                 |
| ! t      | NOT                                |
| ()       | Change precedence (must escape)    |
| -o `opt` | check if `opt` is on               |
| -v `var` | Check if `var` exists              |
| R `var`  | Check if `var`  is naemd reference |

* doesn’t have data types → used as string in string operation / int in int operation
* Files
  * -a / e / f / s / L FILE: Exists / regular file / non-empty / symbolic link
  * -r / w / x FILE aa: readable / writable / executable
  * file1 -ef file2: if file1 and file2 refer to the same device and inode numbers
  * file1 -nt file2: file1 modification date is newer than file2 (file1 exists not file2)
  * file1 -ot file2: file1 modification date is older than file2 (file2 exists not file1)
* Operation
  * :: True
  * && / ||: and / or
  * -R `name`: True if shell variable `name` is set and is name reference
  * -z `string`: True if the length of `string` is zero
  * -n: string not empty

```sh
# 1. Compare two numbers
read a b
if [ $a -gt $b ]; then
    echo ">"
elif [ $a -lt $b ]; then
    echo "<"
else
    echo "=="
fi
```

{% endtab %}
{% tab title='vim' %}

```sh
# 1. Conditional
if name ==# 'John'    # case-sensitive
if name ==? 'John'    # case-insensitive
if name == 'John'     # depends on :set ignorecase
"hello" =~ '/x/'      # regex match
"hello" !~ '/x/'
&&    # and
||    # or
if

let char = getchar()
if char == "\<LeftMouse>"
  # …
elseif char == "\<RightMouse>"
  # …
else
  # …
endif
```

{% endtab %}
{% endtabs %}

## If

{% tabs %}
{% tab title='html' %}

```py
# 1. Basic if
{% if title %} {% else %} {% endif %}
{% if ( (foo == 'foo' or bar == 'bar') and (fo == 'fo' or ba == 'ba') ) %}

# 2. login check
{% if current_user and current_user.id %}
  <a class="btn" style="display:inline">Hi {{ current_user.id }} </a>
  <a class="btn content-login-link" href="/signout">Sign out</a>
{% if current_user.class_id == "" %}
  <a class="btn content-login-link" href="/premium">Premium</a>
{% endif %}
{% else %}
  <a class="btn content-login-link" href="{{ url_for('signin') }}">Sign in</a>
{% endif %}
```

{% endtab %}
{% tab title='python' %}

{% include 'if.test' %}

{% endtab %}
{% tab title='shell' %}

* space between braces
* == and = is equivalent
* ~= for regex match

```sh
# 1. ENV check
cd ~/tempdir && rm -rf *     # only remove if cd success
if [[ -z $ENV ]]; then       # check environment variable is set
  echo "Please set ENV"
  exit 1
fi

if [[ "a" == "$1" ]]; then
  echo 1
elif [[ "b" == "$1" ]]; then
  echo 2
else
  echo "0"
fi

# 2. Contains check
string='My long string'
if [[ $string == *"My long"* ]]; then
  echo "It's there!"
fi
```

{% endtab %}
{% tab title='v' %}

```v
// 1. Basic If
module ifEx(
  input wire[1:0] s,
  input wire i0, i1, i2, i3,
  output reg y
);

always @(s) begin
  if (s==2'b00) begin //begin-end is required for more than one statements
      y = i0;
      // more statements
    end
  else if (s==2'b01)
    y = i1;
  else if (s==2'b10)
    y = i2;
  else if (s==2'b11)
    y = i3;
  else
    y = y; // no change
end

endmodule
```

{% endtab %}
{% endtabs %}

{% include '.if.prob' %}

### Ternary

{% tabs %}
{% tab title='javascript' %}

```js
(1+1==2) ? "Pass" : "Fail"
```

{% endtab %}
{% tab title='shell' %}

```sh
read x y w h
a=$((x<w-x?x:w-x))
b=$((y<h-y?y:h-y))
echo $((a<b?a:b))
```

{% endtab %}
{% endtabs %}

{% include '.ternary.prob' %}

### If elif

{% tabs %}
{% tab title='python' %}

```py
# 1. Classify Triangle given three angle A, B, C
if A + B + C != 180:    # same as A + B + C < 180 or A + B + C > 180:
  print("Error")
elif A == B == C:
  print("Equilateral")
elif A == B or B == C or A == C:
  print("Isosceles")
else:
  print("Scalene")

# 2. Classify score
if score >= 90:
  print('A')
elif score >= 80:
  print('B')
elif score >= 70:
  print('C')
elif score >= 60:
  print('D')
else:
  print('F')
```

{% endtab %}
{% tab title='shell' %}

```sh
if [ $a -ge 90 ]; then
  echo "A"
elif [ $a -ge 80 ]; then
  echo "B"
elif [ $a -ge 70 ]; then
  echo "C"
elif [ $a -ge 60 ]; then
  echo "D"
else
  echo "F"
fi
```

{% endtab %}
{% endtabs %}

{% include '.if-elif.prob' %}

### If and or

| a     | b     | a and b | a or b |
| ----- | ----- | ------- | ------ |
| True  | True  | True    | True   |
| True  | False | False   | True   |
| False | True  | False   | True   |
| False | False | False   | False  |

{% tabs %}
{% tab title='python' %}

```py
# 1. Classify year
if n % 4 == 0 and (n % 100 != 0 or n % 400 == 0):
  print("Leap year")
else:
  print("Regular Year")
```

{% endtab %}
{% tab title='shell' %}

```sh
# 1. Classify year
read year

if [[ $((year%4)) -eq 0 && $((year%100)) -ne 0 || $((year%400)) -eq 0 ]]; then
  echo "Leap Year"
else
  echo "Regular Year"
fi
```

{% endtab %}
{% tab title='v' %}

| Name | Symbol |
| ---- | ------ |
| AND  | a & b  |
| OR   | a \| b |
| XOR  | a ^ b  |
| NOT  | ~a     |

{% endtab %}
{% endtabs %}

{% include '.if-and-or.prob' %}

### Min Max

* [Absolute value](https://www.youtube.com/watch?v=r6hS_8nm1jM)

{% tabs %}
{% tab title='cpp' %}

* const T& max(const T& a, const T& b, Compare comp);

{% endtab %}
{% tab title='java' %}

* static T max(T `x`, T `y`): return maximum between `x`, `y`
* static T min(T `x`, T `y`): return minimum between `x`, `y`

{% endtab %}
{% tab title='javascript' %}

* Math.max(`a`, `b`, ...): Get minimum element
* Math.min(`a`, `b`, ...): Get maximum element

{% endtab %}
{% tab title='python' %}

* min(`x`, `y`): return minimum element between `x`, `y` (can be iterable)
* max(`x`, `y`): return maximum element between `x`, `y`

```py
print(min(1, 2))      # 1
print(min([5, 1, 2])) # 5
```

{% endtab %}
{% endtabs %}

{% include '.min-max.prob' %}

### Abs

{% tabs %}
{% tab title='java' %}

* static T abs(T a): return absolute value

{% endtab %}
{% tab title='python' %}

* abs(`x`): return absolute value of `x`
{% include 'abs.test' %}

```py
print(abs(-1))        # 1
```

{% endtab %}
{% endtabs %}

{% include '.abs.prob' %}

## Switch

* Use when case value should be small, sorted
* [-] Use polymorphism instead, open-closed principle

{% tabs %}
{% tab title='cpp' %}

* create jump table → optimize assembly code

```cpp
// read a, b, c
#include <stdio.h>
int main() {
  char input;
  printf("알파벳 : ");
  scanf("%c", &input);
  switch (input) {
    case 'a':
      printf("에이 \n");
      break;
    case 'b':
      printf("비 \n");
      break;
    default:
      printf("죄송해요.. 머리가 나빠서 못 읽어요  \n");
      break;
  }
  return 0;
}
```

{% endtab %}
{% tab title='javascript' %}

```js
switch(expression) {
  case x:
    // code block
    break;
  case y:
    // code block
    break;
  default:
    // code block
}
```

{% endtab %}
{% tab title='shell' %}

```sh
# 1. Case with regex
case $- in
  *i*) ;;
    *) return;;
esac
```

{% endtab %}
{% tab title='v' %}

* case
  * ends with endcase
  * set default

![case](images/20210413_145339.png)

```v
// 1. alu
module demux_1_to_4(input I, input [1:0] sel, output reg [3:0] Y);
  always @ (sel, I)
    case (sel)
      2'b00: Y = {3'b0, I};
      2'b01: Y = {2'b0, I, 1'b0};
      2'b10: Y = {1'b0, I, 2'b0};
      2'b11: Y = {I, 3'b0};
    endcase
endmodule

// 2. alu_tb
module alu_tb;
  reg[3:0]a;
  reg[3:0]b;
  reg[2:0]s;
  wire[7:0]y;
  alu a1(a,b,s,y);

  initial begin
    if (! $value$plusargs("a=%d", a)) begin
      $display("ERROR: please specify +a=<value> to start.");
      $finish;
    end
    if (! $value$plusargs("b=%d", b)) begin
      $display("ERROR: please specify +b=<value> to start.");
      $finish;
    end
    if (! $value$plusargs("s=%d", s)) begin
      $display("ERROR: please specify +s=<value> to start.");
      $finish;
    end

    wait (y) $display("y=%d", y);
    $finish;
  end // initial begin
endmodule
```

{% endtab %}
{% endtabs %}

{% include '.switch.prob' %}

## Goto

* Bad practice
* Supported language: cpp

{% tabs %}
{% tab title='cpp' %}

```cpp
int n=10;
mylabel:
cout << n << ", ";
n--;
if (n>0) goto mylabel;
```

{% endtab %}
{% endtabs %}

## Try

{% include '.try.prob' %}

## Exit

{% tabs %}
{% tab title='python' %}

```py
exit(0)
```

{% endtab %}
{% tab title='shell' %}

| Code  | Description                                                |
| ----- | ---------------------------------------------------------- |
| 1     | Catchall for general errors                                |
| 2     | Misuse of shell builtins (according to Bash documentation) |
| 126   | Command invoked cannot execute                             |
| 127   | Command not found                                          |
| 128   | Invalid argument to exit command                           |
| 128+n | Fatal error signal “n”                                     |
| 130   | Bash script terminated by Control-C                        |
| 255*  | Exit status out of range                                   |

* $?: Exit status of the last command executed
* set: change shell options, set positional parameters, display names and values of shell variables
  * -e: Exit immediately if a command exits with a non-zero status
  * -o: Set optional flag
    * errexit: if any commands fails, entire script fails, use || true for workaround (don't use &&)
    * nounset: exits if any of your variable is not set ([ex]: rm -rf /$BACKUP_FOLDER)
    * pipefail: if any pipe command fails, entire script fails

```sh
# 1. Exit when diff
diff -r test/global/before test/global/after || exit
echo $?  # See last exit code
```

{% endtab %}
{% endtabs %}

### Signal

* man 7 signal for more detail
  * apt update && apt install man-db

| Singal Name | Signal Number | Description                                                              |
| ----------- | ------------- | ------------------------------------------------------------------------ |
| SIGHUP      | 1             | Hang up detected on controlling terminal or death of controlling process |
| SIGINT      | 2             | Issued if the user sends an interrupt signal (Ctrl + C)                  |
| SIGQUIT     | 3             | Issued if the user sends a quit signal (Ctrl + D)                        |
| SIGFPE      | 8             | Issued if an illegal mathematical operation is attempted                 |
| SIGKILL     | 9             | If process gets this, quit immediately and wo any clean-up operations    |
| SIGALRM     | 14            | Alarm clock signal (used for timers)                                     |
| SIGTERM     | 15            | Software termination signal (sent by kill by default)                    |

{% tabs %}
{% tab title='cpp' %}

* sys/wait.h
  * pid_t waitpid(int *statloc, int options): return pid if success or -1 if failed
    * pid=-1: wait for arbitrary
    * pid=0: wait for same process group pid
    * pid < 0 or pid >0: waitfor process with abs(pid)

```cpp
#include <sys/wait.h>

// 1. Parent is okay even exec fails
while (1) {
  char *cmd = read_command();
  int child_pid = fork();
  if (child_pid == 0) {
    // manipulate stdin / stdout / stderr file descriptors for pipes, redirections
    exec(cmd);
    // "exec failed"
  } else {
    int rc_wait = waitpid(child_pid);
    printf("parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int)getpid());

  }
}
```

{% endtab %}
{% tab title='python' %}

* signal

```py
import sys
import signal
import os
import errno
import time
from functools import wraps
import contextlib

# 1. Timeout signal
count = 0

def handler(signum, frame):
  print(f"1 sec passed \t {count}")
  sys.exit(0)

signal.signal(signal.SIGINT, lambda sn, f: print("CTRL+C Pressed"))
signal.signal(signal.SIGALRM, handler)
signal.alarm(5)
while True:
  count += 1
print(count)

# 2. Timeout Decorator
def timeout(seconds, error_message=os.strerror(errno.ETIME)):
  def decorator(func):
    def _handle_timeout(signum, frame):
      raise Exception(f"Took longer than {seconds}s")

    def wrapper(*args, **kwargs):
      signal.signal(signal.SIGALRM, _handle_timeout)
      signal.alarm(seconds)
      try:
      result = func(*args, **kwargs)
      finally:
      signal.alarm(0)
      return result

    return wraps(func)(wrapper)
  return decorator

@timeout(1)
def fast_function():
  time.sleep(0.5)
  print("hello")

@timeout(1)
def slow_function():
  time.sleep(2)
  print("heeeeeeello")

# 3. Timeout context
class timeout(contextlib.ContextDecorator):
  def __init__(self, seconds, *, timeout_message=os.strerror(errno.ETIME), suppress_error=False):
  self.seconds = seconds
  self.timeout_message = timeout_message
  self.suppress_error = suppress_error

  def _timeout_handler(self, signum, frame):
  raise TimeoutError(self.timeout_message)

  def __enter__(self):
  signal.signal(signal.SIGALRM, self._timeout_handler)
  signal.alarm(self.seconds)

  def __exit__(self, exc_type, exc_val, exc_tb):
  signal.alarm(0)
  if self.suppress_error and exc_type is TimeoutError:
    return True

with timeout(1):
  time.sleep(0.5)
  print("hello")

with timeout(1):
  time.sleep(2)
  print("heeeello")
```

{% endtab %}
{% tab title='shell' %}

> Command

* suspend: suspend the execution of this shell until it receives a SIGCONT signal

* kill: terminate or signal a process
  * pid: kill pid process
  * -HUP "$PPID": logout, restart user
  * -l: list all signals

* pkill: find or signal processes by name

* trap: SIGKILL and SIGSTOP cannot be detected by trap
  * command signal...: execute command when signal
  * signal...: reset signal back to default

* wait: waits for completing any running process (if many, only PID of last command)

```sh
# 1. Basic usage
'myhandler' INT; myhandler() { ;}    # ignore signal if blank
trap "rm $WORKDIR/work1$$ $WORKDIR/dataout$$; exit" 1 2   # $$ defined when trap executed
trap 'rm $WORKDIR/work1$$ $WORKDIR/dataout$$; exit' 1 2   # $$ defined when signal received


# 2. grep cpu at certain second
for i in 1 2 4 8 16 32; do
  ~/measure -t $i & sleep 10;
  top -n 1 -d 1 -i -b;
  wait;
done
```

{% endtab %}
{% endtabs %}
