# Debug

{% tabs %}
{% tab title='cmake' %}

* CMAKE_BUILDT_TYPE: [ex] **DEBUG**, RELEASE, RELWITHDEBINFO, MINSIZEREL

  ```sh
  # Optional Toolchain / Build Type         # Debug Version doesn't do compiler optimization
  ├── CMakeLists.txt
  project("Hello")
  cmake_minimum_required(VERSION 3.5)
  set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
  set(CMAKE_BUILD_TYPE Debug)               # cmake -DCMAKE_BUILD_TYPE=Debug
  add_executable(Hello ${SOURCE_FILES})
  ├── main.cpp
  └── toolchain
    └── Linux-Clang.cmake
  set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE string "clang++ compiler" FORCE)    # cmake -Bbuild -Ctoolchain/Linux-Clang.cmake
  ```

{% endtab %}
{% tab title='python' %}

* rlcompleter

```py
import rlcompleter
import readline
readline.parse_and_bind("tab: complete")
```

* warnings
  * filterwarnings('ignore'): action='once'
  * warnings.filterwarnings(action="ignore", message="unclosed", category=ResourceWarning)

* dis
  * dis(): Return a formatted view of the bytecode operations

{% endtab %}
{% endtabs %}

{% tabs %}
{% tab title='vim' %}

* vscode.launch.json: used to configure the debugger in Visual Studio Code
  * args: when debugging the program
  * externalConsole: Used only when launching the debuggee
  * port: port when attaching to a running process
  * preLaunchTask: `CppBuild` as defined in task.json name
  * program: name of the program (ex: ${fileDirname}/${fileBasenameNoExtension}")
  * setupCommands:
    * {"text": "-enable-pretty-printing", "ignoreFailures": true },
    * {"description": "In this mode GDB will be attached to both processes after a call to fork() or vfork().",
      "text": "-gdb-set detach-on-fork off", "ignoreFailures": true},
    * {"description": "The new process is debugged after a fork. The parent process runs unimpeded.",
      "text": "-gdb-set follow-fork-mode child", "ignoreFailures": true}
  * stopAtEntry=`false`: whether to stop at the entry point
  * sudo=`false`: console must be externalTerminal
  * type : cppdbg
    * MIMMode: [ex]: gdb, lldb
  * type : java
    * mainClass: ${file}

```json
// launch.json
{
  "configurations": [ {
    // add environment variable
    "env": {"API_BASE":"https://"}  ,
    "envFile": "${workspaceFolder}/.env" ,
    "preLaunchTask": "myShellCommand", // run before
    "justMyCode"  // When omitted / set true (default), restricts debugging to user-written code only
  },

  // 1. Run Python (module / Flask / Django app)
  { "name": "Tests",
    "type": "python",
    "request": "launch",
    "module": "page.test",
    "cwd": "${workspaceFolder}",
    "envFile": "${workspaceFolder}/.env" },
  { "name": "Main Server",
    "type": "python",
    "request": "launch",
    "module": "flask",
    "env": { "FLASK_APP": "page.app:create_app()", "FLASK_ENV": "development",
             "FLASK_RUN_PORT": "8080", "FLASK_RUN_HOST": "localhost", },
    "args": [ "run", "--cert", "adhoc" ],
    "jinja": true },
  { "name":"Django",
    "type": "python",
    "request": "launch",
    "program": "${workspaceFolder}/manage.py",
    "args": [
      "runserver",
    ],
    "django": true },

  // 2. Java
  { "type" : "java",
    "name" : "launch machine",
    "request": "launch",
    "mainClass": "nachos.machine.Machine",
    "cwd": "PATH_TO/proj0",
    "classPaths": ["PATH_TO/proj0"] }

  // 3. Cpp Codeforce
  { "name": "C++ Launch",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/a.out",
    "args": ["arg1", "arg2"],
    "environment": [{ "name": "config", "value": "Debug" }],
    "cwd": "${workspaceFolder}" }
  ]
}
```

{% endtab %}
{% endtabs %}

## Interactive debug

{% tabs %}
{% tab title='cpp' %}

* gdb
  * must be compiled using -g flags to see
  * --args: run with parameter
  * -tui: text based GUI
  * $ stards for last value in history

> Example

* gdb (general)
  * ./a.out: start gdb
  * apropos
  * b (breakpoint)s
    * info: show all breakpoints
    * d N: Delete Nth breakpoint
    * enable / disable br: enable / disable all br
  * info
    * sharedlibrary: List all shared library
    * args: Arguments of the current stack frames
    * locals: List local variables of current stack frame
    * variables: List all global and static variable names
  * help (h)
    * aliases
    * status
  * threads
    * info threads: show all threads
    * b [LN] thread [BTNUM]: set breakpoint of thread
  * backtrace (bt): show stack trace
    * f `N`: go to `N`th frame
    * clear: remove all breakpoints
    * nexti: per instruction
    * finish: Continue until the current function returns
    * next (n): step over subroutines
    * frametf
    * continue: Continue normal execution
    * up / down `N`: go up / down `N` stacktrack [ex] **1**

* gdb (display)
  * set
    * print elements 0: Set a limit on how many elements of an array GDB will print
  * p: print data
  * x/s 0x8049988: print data in address
  * whatis `exp`: data type of `exp` [ex] **$**

* gdb (navigation)
  * q / quit: quit
  * run: start from beginning
  * set: set args [args..]
  * refresh / Ctrl L: show GUI
  * s / step: steps into subroutines
  * stepi: per instruction
  * -q: do not print introductory and copyright message
  * b facorial.c:14: breakpoint to line
  * break 'BST::add(\<TAB\>: breakpoint to function
  * i locals / break / variables: info args locals / breakpoints / variables
  * l <> / 20 / func / test.func: list files around current / line 20 / function / function in file
  * --args ./main -i ~/data: pass argument

> Error

* No symbol table info available
  * gcc and gdb version are incompatible -> install newer gdb

{% endtab %}
{% tab title='python' %}

* pdb: 3.7 <
  * set_trace()
* breakpoint(): <= 3.7

```py
import ipdb, pdb

# 1. pdb
""" pdb.set_trace() """
breakpoint()

# 2. ipdb
ipdb.set_trace()
```

{% endtab %}
{% endtabs %}

## Logging

* never concerns itself with routing or storage of its output stream, use stdout
* Use Open-source log routers are available for production ([ex] Logplex, Fluentd)
* Stream can be sent to a log indexing and analysis system ([ex] Splunk), general-purpose warehouse ([ex] Hadoop, Hive)

{% tabs %}
{% tab title='cpp' %}

* \_\_LINE\_\_: Print linenumber
* \_\_func\_\_: Function name (in c++11)

{% endtab %}
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

* winston

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

* logging.config
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
import logging
import logging.config

# NOTSET | 0 < DEBUG | 10 < INFOR | 20 < WARNING | 30 < ERROR | 40 < CRITICAL | 50
basicConfig(filename="newfile.log", level=logging.DEBUG)
log(level, msg, *args, **kwargs)  # Logs a message with integer level level on this logger
logging.getLogger("imported_module").setLevel(logging.WARNING)    # disable imported logger
(format='%(asctime)s,%(msecs)d %(levelname)-8s [%(filename)s:%(lineno)d] %(message)s', datefmt='%Y-%m-%d:%H:%M:%S')

# 1. Simple logging
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s, %(levelname)-8s [%(filename)s:%(lineno)d] %(message)s')

# 2. Disable unexpected logging in python interactive
logging.getLogger('parso.python.diff').disabled = True

# 3. logger class

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

* LINENO: line number in script or shell function currently executing
* set -o xtrace: traces commands before executing them

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

* cprofile
  * python -m cProfile [-o output_file] [-s sort_order] (-m module | myscript.py)

  ```py
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

* pstats
  * statistics browser for reading and examining profile dumps
  * ncalls (actual calls / primitive calls)
    * if not recurse, two values are the same

  ```py
  import pstats

  p = pstats.Stats("output")
  p.sort_stats("cumulative").print_stats(30)        # 30 longest in descending
  p.sort_stats("cumulative").print_stats("main.py") # functions in main.py
  ```

* line_profiler

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
