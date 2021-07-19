# Debug

{% tabs %}
{% tab title='cpp' %}

* must be compiled using -g flags to see

> CLI

* --args: run with parameter
* -tui: text based GUI

> Help

* apropos

* b (breakpoint)s
  * info: show all breakpoints
  * d N: Delete Nth breakpoint
  * enable / disable br: enable / disable all br

* info
  * sharedlibrary
  * variables: show all variables

* threads
  * info threads: show all threads
  * b [LN] thread [BTNUM]: set breakpoint of thread

* bt / backtrace: show stack trace
  * f N: go to Nth frame
  * clear: remove all breakpoints
  * nexti: per instruction
  * finish: Continue until the current function returns
  * n / next: step over subroutines
  * frametf
  * continue: Continue normal execution
  * up / down N: go up / down stacktrack default 1

* display
  * set print elements 0: Set a limit on how many elements of an array GDB will print
  * p: print data
  * x/s 0x8049988: print data in address

* navigation
  * q / quit: quit
  * run: start from beginning
  * set: set args [args..]
  * refresh / Ctrl L: show GUI
  * s / step: steps into subroutines
  * stepi: per instruction
  * -q: do not print introductory and copyright message
  * gdb ./a.out: start gdb
  * b facorial.c:14: breakpoint to line
  * break 'BST::add(\<TAB\>: breakpoint to function
  * i locals / break / variables: info args locals / breakpoints / variables
  * l <> / 20 / func / test.func: list files around current / line 20 / function / function in file
  * --args ./main -i ~/data: pass argument

{% endtab %}
{% tab title='python' %}

> rlcompleter

```py
import rlcompleter
import readline
readline.parse_and_bind("tab: complete")
```

> warnings

* filterwarnings('ignore'): action='once'
* warnings.filterwarnings(action="ignore", message="unclosed", category=ResourceWarning)

> dis

* dis(): Return a formatted view of the bytecode operations

{% endtab %}
{% endtabs %}

## Interactive debug

{% tabs %}
{% tab title='python' %}

> pdb

* set_trace()
* Breakpoint()

```py
import ipdb, pdb

# 1. pdb
pdb.set_trace()
python -m pdb

# 2. ipdb
ipdb.set_trace()
```

{% endtab %}
{% endtabs %}

## Logging

{% tabs %}
{% tab title='java' %}

* log4j.appender.A1.layout.ConversionPattern=%d{HH:mm:ss,SSS} %-5p %c{1}.%M %L %x - %m%n

* %c: Class name ([ex] %20/-20c: Left/right pad if less than 20 char)
* %M: Method name
* %L: Line number
* %p: debug strength
* StackTraceElement

```java
// 1. get filename and line number
public static void debug(String message) {
  StackTraceElement curStack = Thread.currentThread().getStackTrace()[2];
  System.out.println("[" + curStack.getFileName() + ":" + curStack.getLineNumber() + "] " + message);
}
```

{% endtab %}
{% tab title='javascript' %}

> winston

```js
// 1. log_object
import * as winston from "winston"
const { combine, timestamp, label, prettyPrint } = winston.format

const logger = winston.createLogger({
  level: 'info',
  format: combine(timestamp(), prettyPrint()),
  transport: [
    new winston.transport.File({ filename: 'error.log', level: 'error' }),
    new winston.transport.File({ filename: 'combined.log' }),
  ]
})

export default logger

// 2. fileno
var winston = require("winston");
var path = require("path");
var PROJECT_ROOT = path.join(__dirname, "../../");

var transports = [];

if (process.env.NODE_ENV !== "development") {
  transports.push(new winston.transports.Console());
} else {
  transports.push(
    new winston.transports.Console({
      format: winston.format.combine(winston.format.cli(), winston.format.splat()),
    }),
  );
}
var logger = winston.createLogger({ transports: transports });
logger.stream = { write: function (message) { logger.info(message); } };
module.exports.debug = module.exports.log = function () { logger.debug.apply(logger, formatLogArguments(arguments)); };
module.exports.info = function () { logger.info.apply(logger, formatLogArguments(arguments)); };
module.exports.warn = function () { logger.warn.apply(logger, formatLogArguments(arguments)); };
module.exports.error = function () { logger.error.apply(logger, formatLogArguments(arguments)); };
module.exports.stream = logger.stream;

function formatLogArguments(args) {
  args = Array.prototype.slice.call(args);
  var stackInfo = getStackInfo(1);
  if (stackInfo) {
    // get file path relative to project root
    var calleeStr = "(" + stackInfo.relativePath + ":" + stackInfo.line + ")";

    if (typeof args[0] === "string") {
      args[0] = calleeStr + " " + args[0];
    } else {
      args.unshift(calleeStr);
    }
  }
  return args;
}

/* Parses and returns info about the call stack at the given index */
function getStackInfo(stackIndex) {
  var stacklist = new Error().stack.split("\n").slice(3);

  var stackReg = /at\s+(.*)\s+\((.*):(\d*):(\d*)\)/gi;
  var stackReg2 = /at\s+()(.*):(\d*):(\d*)/gi;

  var s = stacklist[stackIndex] || stacklist[0];
  var sp = stackReg.exec(s) || stackReg2.exec(s);

  if (sp && sp.length === 5) {
    return {
      method: sp[1],
      relativePath: path.relative(PROJECT_ROOT, sp[2]),
      line: sp[3],
      pos: sp[4],
      file: path.basename(sp[2]),
      stack: stacklist.join("\n"),
    };
  }
}
```

{% endtab %}
{% tab title='python' %}

* Use Lazy string inside logging: ("detect mimetypes faild because %s", e)

* DEBUG, INFO, `WARNING`, ERROR, CRITICAL: 10, 20, 30, 40, 50
  * default level is WARNING
* debug()
* info()
* warning(): if there is nothing the client application can do about the situation, but the event should still be noted
* error()
* exception(): ERROR + Exception info is added to the logging message
* critical(msg)
* StreamHandler()
* FileHandler(`filename`): create handler that writes to file
* getLogger(): returns logging.Logger

> logging.config

* basicConfig()
  * filename=`file`: log to `file`
  * level=`LEVEL`: set `LEVEL`
  * format
    * asctime: 2010-12-12 11:41:42,612
    * message
  * datefmt
    * %m/%d/%Y
    * %I:%M:%S %p'

* logging.Logger
  * propage = `True`: set whether to propagte when import
  * setLevel(logging.INFO): Messages less severe than level will be ignored
  * add / removeFilter(filter): Adds / remove specified filter filter to this handler
  filter(record)
  * lineno, funcName, message: line number, function name, message
  * relativeCreated: relative time

```py
# NOTSET | 0 < DEBUG | 10 < INFOR | 20 < WARNING | 30 < ERROR | 40 < CRITICAL | 50
basicConfig(filename="newfile.log", level=logging.DEBUG)
log(level, msg, *args, **kwargs)  # Logs a message with integer level level on this logger
logging.getLogger("imported_module").setLevel(logging.WARNING)    # disable imported logger
(format='%(asctime)s,%(msecs)d %(levelname)-8s [%(filename)s:%(lineno)d] %(message)s', datefmt='%Y-%m-%d:%H:%M:%S')

# Simple logging
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s, %(levelname)-8s [%(filename)s:%(lineno)d] %(message)s')

# Disable unexpected logging in python interactive
logging.getLogger('parso.python.diff').disabled = True

# logger class
import logging
import logging.config

def get_logger(name, level=logging.DEBUG):
  # ignore warning from other module
  logging.config.dictConfig({
    'version': 1,
    'disable_existing_loggers': True
  })

  logger = logging.getLogger(name)

  # remove exsiting handlers -> prevents logged twice
  for hdlr in logger.handlers[:]:
  logger.removeHandler(hdlr)

  # set output to file
  sh = logging.StreamHandler()
  sh.setFormatter(logging.Formatter('%(asctime)s, %(levelname)-8s [%(filename)s:%(lineno)d] %(message)s'))
  logger.addHandler(sh)
  logger.setLevel(level)


  return logger

log = get_logger(__name__)
log.info("hi")
```

{% endtab %}
{% tab title='shell' %}

```sh
function err() {
  echo "ERROR: ${1 - Unknown Error}" >&2
}
```

{% endtab %}
{% endtabs %}

## Profiler

{% tabs %}
{% tab title='python' %}

> cprofile

* python -m cProfile [-o output_file] [-s sort_order] (-m module | myscript.py)

> pstats

* statistics browser for reading and examining profile dumps

* ncalls (actual calls / primitive calls)
  * if not recurse, two values are the same

```py
import pstats

# 1. After running python3 -m cprofile -o output main.py
p = pstats.Stats("output")
p.sort_stats("cumulative").print_stats(30)        # 30 longest in descending
p.sort_stats("cumulative").print_stats("main.py") # functions in main.py

# 2. C Profiler
def create_array():
  arr=[]
  for i in range(0,400000):
  arr.append(i)

def print_statement():
  print('Array created successfully')

def main():
  create_array()
  print_statement()

if __name__ == '__main__':
  import cProfile, pstats
  profiler = cProfile.Profile()
  profiler.enable()
  main()
  profiler.disable()
  stats = pstats.Stats(profiler).sort_stats('ncalls')
  stats.print_stats()
```

> line_profiler

```py
from line_profiler import LineProfiler
import random

def do_other_stuff(numbers):
  s = sum(numbers)


def do_stuff(numbers):
  do_other_stuff(numbers)
  l = [numbers[i]/43 for i in range(len(numbers))]
  m = ['hello'+str(numbers[i]) for i in range(len(numbers))]

numbers = [random.randint(1, 100) for i in range(1000)]

lp = LineProfiler()
lp_wrapper = lp(do_stuff)
lp_wrapper(numbers)
lp.print_stats()
"""
Timer unit: 1e-06 s

Total time: 0.000768 s
File: <ipython-input-1-d026e2ddfa6e>
Function: do_stuff at line 9

Line #      Hits         Time  Per Hit   % Time  Line Contents
==============================================================
   9                                           def do_stuff(numbers):
  10         1         16.0     16.0      2.1    do_other_stuff(numbers)
  11         1        228.0    228.0     29.7    l = [numbers[i]/43 for i in range(len(numbers))]
  12         1        524.0    524.0     68.2    m = ['hello'+str(numbers[i]) for i in range(len(numbers))]
"""
```

{% endtab %}
{% endtabs %}
