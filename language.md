# Language

* Read Merge request, Follow code histroy

![Language](images/20210304_223009.png)

> Terms

* Abstract data types vs Data Structure
* ADT is a logical description (interface) vs concrete
* List vs Linked List, ArrayList
* Map vs HashMap, TreeMap

* Backus–Naur Form
* notation technique for context-free grammars, often used to describe the syntax of languages
* name    ::=  lc_letter (lc_letter | "_")*
* lc_letter::=  "a"..."z"
* \<digit>::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

* Declarative / Functional
* Immutability → frees us from having to deal with state change
* separating functions and data → data passed as arguments, instead of self keyword as in OOP
* first-class functions → treat functions as variable, use higher-order function to maintain SRP

* Imperatives
  * How: Set x equal to zero, add the every number in list to x, divide x by length of the list
* Object Oriented
* Procedural

* Lexical analysis
  * x = a + b;
  * [(identifier, x), (operator, =), (identifier, a), (operator, +), (identifier, b), (separator, ;)]

* Declarative: What: X is the sum of all the numbers in the list, divided by the length of the list

* Currying: translating evaluation of function that takes multiple arguments into evaluating a sequence of functions

* Mixin: only exist in multiple-inheritance languages → not in java c#
  * provide a lot of optional features for a class
  * use one particular feature in a lot of different classes

* Duck Typing: don't need a type in order to invoke an existing method on an object

* Partial application: process of fixing a number of arguments to a function, producing another function of smaller arity

* Modularity: concept of making multiple modules then combining them to form a complete system

* Exception: Separating Error-Handling Code from “Regular” Code
  * A method writer can choose to handle certain exceptions and delegate others to the caller
  * An exception that occurs in a function can be handled anywhere in the function call stack

* Heisenbug: disappears or alters its behavior when an attempt to isolate it is made

```py
def fetch_data_real():    # lengthy operation
def mock_fetch_data():    # mocked version
fetch_data = fetch_data_real if ENVIRONMENT == 'prod' else fetch_data_mock

functions = [ squared, double, minus_one, math.sqrt ]
for func in functions:
num = func(num)
```

## CLI

{% tabs %}
{% tab title='cpp' %}

> gflags

```cpp
#include <gflags/gflags.h>

#include <iostream>

using namespace std;

DEFINE_bool(debug, true, "print debug info");
// DEFINE_string(languages, "english,french,german", "comma-separated list of languages to offer in the 'lang' menu");

int main() { cout << FLAGS_debug; }
```

{% endtab %}
{% tab title='python' %}

> argparse

* ArgumentParser(): create parser
  * add_help=False
  * prefix_chars='+/'
  * add_argument(): add arguments
    * [ex] '-i', '--input'
    * action: [ex] store_const, store_true, store_false, append_const
    * choices: [ex] ['rock', 'paper', 'scissors']
    * nargs='+': Accepts multiple argument(python arg.py 1234 2345)
    * nargs='?': At most one argument or default value will be consumed from the command line if possible
    * nargs=argparse.REMAINDER: parse all leftover
    * required=False: whether this argument is needed
    * type=str
  * parse_args()
  * parse_known_args(): Only parse predefined options

```py
import fire
import argparse
import pathlib

# 1. Argparse
args.myArg is not None # check argument

def get_parser():
  parser = argparse.ArgumentParser()
  parser.add_argument('count', type=int)
  parser.add_argument('distance', type=float)
  parser.add_argument('street', type=ascii)
  parser.add_argument('code_point', type=ord)
  parser.add_argument('source_file', type=open)
  parser.add_argument('dest_file', type=argparse.FileType('w', encoding='latin-1'))
  parser.add_argument('datapath', type=pathlib.Path)
  args = parser.parse_args()
  return args

# 2. Fire
class ParseClass:
  def __init__(self, offset):
    self.offset = 3

  # python fire_class.py ParseClass add 10 20 --offset=0
  def add(self, x, y):
    return self.offset + x + y

  def add_list(self, li):
    return sum(li)

if __name__ == "__main__":
  fire.Fire(ParseClass)

# python fire_class.py add --x 1 --y 2
# python fire_class.py add_list "[1,2,6,54]"
```

{% endtab %}
{% tab title='shell' %}

* unset -f: remove declared function
* Defining a function
  1. foo() { ... ;}
  2. function foo() { ... ;}
* getopt: don't use getopts or old getopt
  * -o: [ex] Vh command argument1 -V argument2 -h (--Vh command argument1 -V argument2 -h)

```sh
# 1. keep input key
valid=true
while [ $valid ]; do
  echo "press q to quit"
  read key
  if [[ $key = "q" ]] || [[ $key = "Q" ]]; then
    break
  fi
done

# 2. Input with shift params
while [[ $# -gt 0 ]]; do
  key="$1"
  case "$key" in
    -s|--source-dir)
    source_dir=$(realpath $2)
    shift
    shift ;;
    -r|--resource-dir)
    resource_dir=$(realpath $2)
    shift
    shift ;;
    -m|--mode)
    mode="$2"
    shift
    shift ;;
    *)
  esac
done

# 3. regex
case "$(uname -s)" in
  Linux*)   machine=Linux;;
  Darwin*)  machine=Mac;;
  CYGWIN*)  machine=Cygwin;;
  MINGW*)   machine=MinGw;;
  *)        machine="UNKNOWN:${unameOut}"
esac
echo ${machine}
```

{% endtab %}
{% endtabs %}

## Clipboard

{% tabs %}
{% tab title='shell' %}

* linux
  * xclip

* mac
  * pbcopy

```sh
sudo apt install xclip
cat a | xclip / pbcopy  # copy to clipboard
```

{% endtab %}
{% tab title='vscode' %}

> Paste Image

* sudo apt-get update
* sudo apt-get install -y xclip

```json
{
  "pasteImage.defaultName": "YMMDD_HHmmss",
  "pasteImage.path": "${currentFileDir}/images",
}
```

{% endtab %}
{% endtabs %}

## Convention

{% tabs %}
{% tab title='cpp' %}

* filename all lowercase
* functions, variables a lowercase + camel case
* classes, structs, and typedefsStart  a capital letter + camelcase

{% endtab %}
{% tab title='java' %}

* Class variable
* Instance variable
  * public class -> protected -> private
* Constructors
* Methods order: main -> static -> methods -> standard -> getters / setters
  * methods: public that call other class methods appear before private that call no other methods
  * standard methods: toString, equals and hashcode next
  * getters and setters have a special place reserved right at the bottom of the class

{% endtab %}
{% tab title='python' %}

* Import: a blank line group import
  * Standard library | third party | Local application/library specific

* Variable Naming
  * _single_leading: from M import * doesn’t import these objects
  * single_trailing_: avoid conflicts with Python keyword (ex. class_, id_)
  * CONSTANT_VAR: all capital letters with underscores separating words
  * ClassName: capwords
  * function_name, var_name

* @classmethod vs @staticmethod
  * cls for the first argument to class methods used for constructor overloading
  * staticmethod can have no parameters at all

```py
if foo is not None:     # Wrong: if not foo is None:
def f(x): return 2*x    # Wrong: f = lambda x: 2*x
if greeting:            # Wrong: if greeting == True:

# R1732: Consider using 'with' for resource-allocating operations (consider-using-with)
### file_handle = open("some_file.txt", "r")
with open("some_file.txt", "r") as file_handle:

# C0103: Constant name "return_code" doesn't conform to UPPER_CASE naming style (invalid-name)
### var outside a function
VAR

# Consider using a generator instead
### tuple([int(num) for num in nums]
tuple(int(num) for num in nums)
```

{% endtab %}
{% endtabs %}

{% tabs %}
{% tab title='django' %}

* docs.djangoproject.com/en/1.11/internals/contributing/writing-code/coding-style/

> General python related

| Code                             | Type              | Usage                                                         |
| -------------------------------- | ----------------- | ------------------------------------------------------------- |
| from core.views import FoodMixin | absolute import   | when importing from outside the current app                   |
| from .models import WaffleCone   | explicit relative | when importing from another, module in the current app (Best) |
| from models import WaffleCone    | implicit relative | when importing from another module in the current app (Bad)   |

* stlib import -> django import -> third-party -> own apps
* Use relative imports (from app.models -> from .models)
* Use underscores over dashes in url pattern name

> Model

| Model Style      | Pros                                                         | Cons                                |
| ---------------- | ------------------------------------------------------------ | ----------------------------------- |
| No model inherit | easiest to understand                                        | duplicated fields across models     |
| ABC              | saves typing, no overhead of joins from multi inheritance    | Can't use parent class in isolation |
| Multi inherit    | query parent / child model, get child from parent object     | query overhead                      |
| Proxy models     | allows have an alias of model with different python behavior | can't change the model's field      |

* Set up identical database with deployment server, might fail on strongly typed database
* Do not use sqlite with production -> Concurrency issue, migrating data
* the app’s name should be a plural version of the app’s main model, source control migraiton code
* Use Meta.fields instead of Meta.exclude -> know exactly what fields we are exposing

> Migration

* As soon as a new app or model is created, create the initial django.db.migrations for that new model
* If the number of migrations becomes unwieldy, use squashmigrations to bring them to heel
* Backup data before running migration
* Before deployment, check that you can rollback migrations

{% endtab %}
{% endtabs %}

{% tabs %}
{% tab title='docker' %}

* image defined by your Dockerfile should generate containers that are as ephemeral as possible
* Sort multi-line arguments
* Always combine RUN apt-get update with apt-get install

{% endtab %}
{% endtabs %}

### Directory

{% tabs %}
{% tab title='django' %}

* Directory

| File or Directory | Purpose                                                                                     |
| ----------------- | ------------------------------------------------------------------------------------------- |
| media             | development only, user-generated static media assets (or host on seperate media servers)    |
| static            | Non user generated static media assets - css, js, images (or host on seperate media server) |
| templates         | site-wide django templates                                                                  |
| profiles          | app for managing and displaying user profiles                                               |

* App

| file          | Purpose                              |
| ------------- | ------------------------------------ |
| behaviors.py  | option for locating model mixins     |
| constants.py  | app-level settings                   |
| decorators.py | app decorators                       |
| factories.py  | place our test data factories        |
| utils.py      | helper function extracted from views |
| signals.py    | providing custom signals             |

{% endtab %}
{% endtabs %}

## Module Deployment

{% tabs %}
{% tab title='python' %}

* Module: one file that only relies on the standard library
* sdist: compressed archives (.tar.gz) containing one or more packages or modules

{% endtab %}
{% endtabs %}

## Environment

{% tabs %}
{% tab title='javascript' %}

```js
process.env.GATSBY_ALGOLIA_APP_ID
```

{% endtab %}
{% tab title='python' %}

* path: a list of strings that determines the interpreter’s search path for modules

```py
# 1. Append to PYTHONPATH
sys.path.insert(0, "/home/myname/pythonfiles")
```

{% endtab %}
{% tab title='shell' %}

```sh
grep -r -- "-n"        # using '--' declare '-n' is not an option

# 1. Optional Argument
ARG1=${1:-foo}
ARG2=${2:-bar}

echo "$ARG1"
echo "$ARG2"

# 2. Check envrionment is set
if [[ -z $REPO_PATH ]]; then
  echo "REPO_PATH not set"
  exit 1
fi
```

{% endtab %}
{% endtabs %}

### Dotenv

{% tabs %}
{% tab title='python' %}

> dotenv

* pip install python-dotenv
* load_dotenv(dotenv_path=PATH.ENV)

{% endtab %}
{% endtabs %}

### Virtual Env

{% tabs %}
{% tab title='javascript' %}

> npm

* install everything in package.json
* npx: CLI tool whose purpose is to make it easy to install and manage dependencies hosted in the npm registry
* brew install npm
* npx
  * create-react-app `name`: don’t have to download create-react-app
* npm
  * nodemon: update refresh backend
  * init: create package.json
  * audit fix: Scan project install any compatible updates to vulnerable dependencies
    * --force: including breaking changes
  * run rename: change project name
  * install
    * -D: install for dev dependency

```sh
npx create-react-app my-app
cd my-app
npm start
```

> Yarn

* package manager that doubles down as project manager
* stores dependencies locally, and fetches from the disk during a yarn add

* yarn
  * install
    * --force: refetches all packages, even ones that were previously installed
    * --network-timeout `ms`: [ex] 1000: 1s

```sh
# 1. Create react app
yarn create react-app my-app
yarn start  # To start the project simply run below commands
yarn build  # To build projects
yarn eject  # eject the project with below command
```

{% endtab %}
{% tab title='python' %}

> conda

* [Cheat sheet](https://docs.conda.io/projects/conda/en/4.6.0/_downloads/52a95608c49671267e40c689e0bc00ca/conda-cheatsheet.pdf)
* -V: show conda version
* env list: get all environments (* is activated)
* list: show installed packages
* list --revision: history of each change to current environment
* info: get all the current environment details
* search PACKAGE_NAME: use conda to search for a package
* create --clone py35 name py35-2: make copy of an environment
* source /Users/sean/anaconda3/bin/activate: Activate conda
* rm -rf ~/.condarc ~/.conda ~/.continuum: Uninstall conda
* create --name py35 python=3.5: Create new environment py35 install Python 3.5
* create --clone py35 --name py35-2: Make exact copy of an environment
* source activate py35: activate environment
* deactivate: Exit from conda
* update conda: update version
* install -y -c `anaconda` bsddb: Install (change `owner` from anaconda.org)

> venv (recommended)

* If repository name is changes change VIRTUAL_ENV in bin/activate
* Prefered as it is official

> pip

* config [debug, edit, get, list, set, unset]
* --version: print version of the pip
* install
  * -e `path/url`: Install project in editable mode ([ex] setuptools "develop mode") from local path or a VCS url

> pipreqs

* Auto generate requirements.txt file for any project based on imports

* --use-local: Use ONLY local package info instead of querying PyPI
* --pypi-server `url`   Use custom PyPi server
* --proxy `url`: Use Proxy, parameter will be passed to requests library. or environments parameter in your terminal:
* --debug: Print debug information
* --ignore `dirs`: Ignore extra directories
* --encoding `charset`  Use encoding parameter for file open
* --savepath `file`: Save the list of requirements in the given file
* --print: Output the list of requirements in the standard output
* --force: Overwrite existing requirements.txt
* --diff `file`: Compare modules in requirements.txt to project imports.
* --clean `file`: Clean up requirements.txt by removing modules that are not imported in project.
* --no-pin: Omit version of output packages.

```sh
# 1. Setup
sudo apt install python-setuptools
sudo apt-get install python3-pip  # Linux
sudo easy_install pip  # Window
brew install pip  # Mac

# 2. uninstall all files
pip freeze | xargs pip uninstall -y

# 3. Install all packages
pip install -r requirements.txt  # in requirements.txt
pip install install .  # pyproject.toml

# 4. setup new environment
python -m venv env      # Create env/ folder in current directory
source env/bin/activate # Activate environmetn
pip install -r requirements.txt # download modules to env/ folder

# 5. Remove environment
deactivate  # exit from environment
rm -rf env  # delete environment
```

{% endtab %}
{% endtabs %}

## Internalization

* i18

{% tabs %}
{% tab title='django' %}

* internationalization: Preparing the software for localization. Usually done by developers.
* localization: Writing the translations and local formats. Usually done by translators

> CLI

* django-admin compilemessages: Compiles .po files to .mo files for use with builtin gettext support
  * --ignore=cache
* django-admin makemessages: Runs over entire source tree of current directory and pulls out all strings marked for translation
  * -e: [ex] html, txt
  * -l: [ex] de

> method

* ngettext(`singular`, `plural`, `n_objects`)

```py
from django.utils.translation import ugettext_lazy as _
LANGUAGES = [('ko', _('Korean')),
  ('en', _('English')),
]

# views.py
from django.http import HttpResponse
from django.utils.translation import gettext as _

# 1. translation
def my_view(request):
  output = _("Welcome to my site.")
  return HttpResponse(output)

# 2. Pluralization
from django.http import HttpResponse
from django.utils.translation import ngettext

def hello_world(request, count):
  page = ngettext('there is %(count)d object', 'there are %(count)d objects', count,) % { 'count': count, }
  return HttpResponse(page)
```

{% endtab %}
{% endtabs %}

## Package

{% tabs %}
{% tab title='java' %}

> Ant

* doesn't impose any coding conventions or project structures → write all the commands by themselves
* build XML build files that are hard to maintain

> Maven

![Maven](images/20210207_210757.png)

* project management tool that is based on POM (project object model)
* used for projects build, dependency and documentation
* provide guidelines and support migration to new features
* separate code from resources and test

> Pom

![Pom](images/20210207_210858.png)

> Archetypes

* project template using Maven
* Manages builds, dependencies + versions / documentation

* artifactId: Physical file name that contains all of the compiled Java code
* groupId: Organization who makes this application
* version: version
* packaging: built into a jar
* parent: inherit most elements, except for artifactId, name, prerequisites
* profiles: allow override configuration and provide default behavior for common tasks
* repositories: point to Maven repositories for artifacts
* plugin repositories: point to the plugins used by Maven itself

```sh
setx JAVA_HOME "C:\Program Files\Java\jdk1.8.0_231"
mvn clean package      # Remove issues with other maven operation
```

{% endtab %}
{% tab title='python' %}

{% endtab %}
{% endtabs %}

### Dependency

* Must not relies on implicit existence of system-wide packages ([ex] curl must be vendered together)
* Bundler: [ex] python pip, c autoconf
* Isolation: [ex] python venv, c static linking

{% tabs %}
{% tab title='javascript' %}

* npm audit: address issues that do not require attention
  * --force: address all issues possible including breaking changes

{% endtab %}
{% tab title='python' %}

```sh
# requirements.txt
# for comment
-r base.txt  # extend from other
```

{% endtab %}
{% endtabs %}

### Publish

{% tabs %}
{% tab title='python' %}

```sh
# 1. Generating distribution archives
python3 -m pip install --upgrade build
python3 -m build

# 2. Uploading the distribution archives
python3 -m pip install --upgrade twine
python3 -m twine upload --repository testpypi dist/*
```

{% include 'setup.py' %}

{% endtab %}
{% endtabs %}

## Path

{% tabs %}
{% tab title='python' %}

> pathlib

![Class Diagram](images/20210219_123346.png)

* Path
  * Class method
    * cwd(): current working directory
    * home()
  * parents
    * MODEL_ROOT = Path(\_\_file__).resolve().parents[2] / 'models'
  * chmod(0o444)
  * name -> str: [ex] 'my/setup.py.zip' -> 'setup.py.zip'
  * stem -> str: [ex] setup
  * suffix -> str: [ex] .py
  * suffixes -> list: [ex] ['.py', '.zip']
  * as_posix()
  * as_uri(): win → linux / uri
  * rglob(pattern): eqiuvalent to glob() with “**/” added in front
  * glob(`*.py`) -> Generator[PosixPath]: get all matched files
  * match(`patterns`): `patterns`
  * resolve(strict=False) -> PosixPath:: make absolute
  * relative_to(`path`): path relative to `path`
  * stat(): information about this path (st_size, st_mtime)
  * is_dir(): Check if directory
  * is_file(): check if file
  * is_absolute() / is_relative_to(*other)
  * rmdir(): remove directory (must be empty)
  * mkdir(mode=0o777, parents=F, exist_ok=F)
  * read_bytes()
  * read_text(encoding=None): Return decoded contents
  * write_text(data, encoding=None, errors=None)

{% endtab %}
{% endtabs %}

### Taskbar

{% tabs %}
{% tab title='cpp' %}

```cpp
// 1. Progress bar
cout << "ABC\n" << '\b' << "D" << endl;
float progress = 0.0;
while (progress < 1.0) {
  int barWidth = 70;

  cout << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) {
    if (i < pos)
      cout << "=";
    else if (i == pos)
      cout << ">";
    else
      cout << " ";
  }
  cout << "] " << int(progress * 100.0) << " %\r";
  cout.flush();

  progress += 0.16;
}
```

{% endtab %}
{% tab title='javascript' %}

```js
<!DOCTYPE html>
<html>
<style>
  #myProgress {
    width: 100%;
    background-color: #ddd;
  }

  #myBar {
    width: 10%;
    height: 30px;
    background-color: #4CAF50;
    text-align: center;
    line-height: 30px;
    color: white;
  }
</style>

<body>
  <h1>JavaScript Progress Bar</h1>

  <div id="myProgress">
    <div id="myBar">10%</div>
  </div>

  <br>
  <button onclick="move()">Click Me</button>

  <script>
    var i = 0;
    function move() {
      if (i == 0) {
        i = 1;
        var elem = document.getElementById("myBar");
        var width = 10;
        var id = setInterval(frame, 10);
        function frame() {
          if (width >= 100) {
            clearInterval(id);
            i = 0;
          } else {
            width++;
            elem.style.width = width + "%";
            elem.innerHTML = width + "%";
          }
        }
      }
    }
  </script>

</body>

</html>
```

{% endtab %}
{% tab title='python' %}

> tqdm

```py
from tqdm import tqdm_notebook as tqdm

text = ""
bar = tqdm(total=4)
for i, char in enumerate(["a", "b", "c", "d"]):
  time.sleep(0.5)
  bar.update(1)

for i in tqdm.tqdm(range(10000)):
  time.sleep(0.5)
```

{% endtab %}
{% endtabs %}

## Run

![cpp process](images/20210214_023508.png)

{% tabs %}
{% tab title='cpp' %}

> Why learn this process?

* Optimizing program performance
  * is a switch statement always more efficient than a sequence of if-else statements?
  * How much overhead is incurred by a function call?
  * Is a while loop more efficient than a for loop?
  * Are pointer references more efficient than array indexes?
  * Why does our loop run so much faster if we sum into a local variable instead of an argument that is passed by reference?
  * How can a function run faster when we simply rearrange the parentheses in an arithmetic expression?

* Understanding link-time errors
  * what does it mean when the linker reports that it cannot resolve a reference?
  * What is the difference between a static variable and a global variable?
  * What happens if you define two global variables in different C files with the same name?
  * What is the difference between a static library and a dynamic library?
  * Why does it matter what order we list libraries on the command line?
  * why do some linker-related errors not appear until run time?

* Avoiding security holes
  * Buffer overflow vulnerabilities have accounted for many of the security holes in network and Internet servers
  * few programmers understand the need to carefully restrict the quantity and forms of data they accept from untrusted sources
  * understand consequences of way data and control info are stored on program stack

{% endtab %}
{% tab title='python' %}

> CLI

* [Online Editor - leetcode](https://leetcode.com/playground/new/empty)
* [Online Editor - codechef](https://leetcode.com/playground/new/empty)

* python a.py
  * -c `command`: Execute python code in `command` (; for line delimiter)
  * -m `module-name`: Search sys.path for `module-name` / execute as the \_\_main__ module
  * -u: Force stdin, stdout and stderr to be totally unbuffered (= set PYTHONUNBUFFERED to non zero)
  * -O / -OO: removes assert statements / assert statements + \_\_doc__ strings

> Interactive

* Ipython
  * ipython3 -i file_name.py

```sh
# 1. Setup
sudo apt update
sudo apt install software-properties-common
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt install python3.9
```

{% endtab %}
{% endtabs %}

{% tabs %}
{% tab title='vscode' %}

> code runner

* Shortcut to run different codes

![run](images/20210410_031114.png)

```json
"code-runner.ignoreSelection": true,       // don't create tempCodeRunnerFile
"code-runner.saveAllFilesBeforeRun": true,
"code-runner.runInTerminal": true,
// Competitive programming
"code-runner.executorMapByGlob": {
  "z.py": "cat z.txt | python3 z.py",
  "z.cpp": "g++ --std=c++11 z.cpp && cat z.txt | ./a.out",
},
```

{% endtab %}
{% endtabs %}

### Interactive

{% tabs %}
{% tab title='python' %}

> Juypter

* jupyter notebook .: Open
* python3 -m notebook
* from IPython.display import display: print in nicer form
* _ih[-5:]: code of the 5 most recently run cells
* from IPython.core.debugger import set_trace
* c: continue until the next breakpoint
* n: next line of code (→ shows current position)
* q: quits

> shortcut

* ctrl + enter: Run cell
* shift + enter: Run cell and move
* alt + enter: Create cell below
* dd: Delete current cell
* command + shift + C: command palette

> magic

* %load_ext autoreload
* %autoreload 2: Reload modules (except %aimport) automatically
* %debug: Run pdb
* %reset_selective <regular_expression>
* %reset -f
* %who: List all variable
* %whos: Some extra information about each variable
* %matplotlib: Set up matplotlib to work interactively
* %%time: Information about a single run of the code
* %%bash: Run bash script (bash, HTML, latex, markdown)
* %%writefile name: Write the contents of the cell to a fill

{% endtab %}
{% endtabs %}

## OTA

* Over the air programming
