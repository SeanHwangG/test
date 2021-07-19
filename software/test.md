# Test

* refactoring, work on either the code or the tests, but not both at once

![Test](images/20210209_183727.png)

> Terms

* Acceptance (Functional Test, End-to-End Test, Blackbox test)
  * human-readable story that we can follow
* Capacity: application be checked against the expected load
* Coverage: seek to execute all possibility
* System: External libraries of a system
* Component: Library, compiled binary
* Bottom-up testing: when testing if something works, its parts should already be tested
* Performance
* Sub-system, system levels to verify timing / resource usages
* Equivalence classes: no need to write two tests that expose the same bug
* Unit Testing: Functional level, Explorative

* TDD: Kent Beck in 1990's part of Extreme programming software development process (created Sunit, Junit)
  * unit tests are written before production code
  ![TDD Cycle](images/20210209_183747.png)

* Test fixture, context
* fixed environment in which tests are run so that results are repeatable
* Loading a database with a specific, known set of data
* Erasing a hard disk and installing a known clean operating system installation
* Copying a specific known set of files
* Preparation of input data and set-up/creation of fake or mock objects

* Mocking
* Stub: A stub adds simplistic logic to a dummy, providing different outputs
* Mocks: fake object that helps to verify whether an interaction with an object occurred
* Fakes: anything that is not real, which, based on their usage, can be either stubs or mocks
* Non-deterministic result, Difficult to create or reproduce, slow (complete database)
* Doesn't yet exist or may change behavior
* same interface as the real objects they mimic
* [-] increased maintenance on the tests themselves during system evolution (refactoring)

{% tabs %}
{% tab title='python' %}

* django
  * placed in app/tests
  * app/fixtures/fixture.json
* pylint-django
  * pip install pylint-django

* test
  * assertNumQueries(`num`): check if `num` query has called
  * TestCase
    * assertEqual / True / In
    * assertTemplateUsed

* pytest CLI
  * --ds=DS: Set DJANGO_SETTINGS_MODULE.
  * --no-migrations: Disable Django migrations on test setup
  * --migrations: Enable Django migrations on test setup

```py
# 1. Test call command
from django.core.management import call_command
from django.test import TestCase
from io import StringIO

class SmokeTest(TestCase):
  def test_root_url_resolves_to_home_page_view(self):
    found = resolve('/')
    self.assertEqual(found.func, home_page)

# 2. Assert not raises
args = []
opts = {}
out = StringIO()
try:
  call_command('update_md', {"directory": "cs", "suffix": ".delete"}, stdout=out)
  self.assertContains(out.getvalue(), "SUCCESS")
except ExceptionType:
  self.fail("myFunc() raised ExceptionType unexpectedly!")
```

{% endtab %}
{% endtabs %}

## Assert

* For a portion of code to work correctly, certain conditions or values must be true
* Exception is better when classified need to be handled

{% tabs %}
{% tab title='cpp' %}

> cassert (assert.h)

* cassert are preferred same as assert.h except static_assert is not defined

```cpp
#include <stdio.h>
#include <assert.h>

int main() {
  int i;

  for (i=0; i<=9; i++) {
      assert(i <= 4);
      printf("i = %d\n", i);
  }

  return 0;
}
```

{% endtab %}
{% tab title='python' %}

* python -O: ignore all assert

```py
# 1. Custom exception
def getExpenseLimit(self):
  # Should have either expense limit or a primary project.
  assert (self.expenseLimit != NULL_EXPENSE) or (self.primaryProject != None)

  return self.expenseLimit if (self.expenseLimit != NULL_EXPENSE) else \
    self.primaryProject.getMemberExpenseLimit()
```

{% endtab %}
{% endtabs %}

> Reference

<https://refactoring.guru/introduce-assertion>

## Format

{% repo 'yapf' %}

{% tabs %}
{% tab title='python' %}

* autopep8: automatically formats Python code to conform to the PEP 8 style guide
  * -i: modify file in-place
  * -j: num of parallel jobs, match CPU count if value is less than 1 ([ex] 2)

* isort: import sorting
  * .: sort current directory

```py
# 1. inside code
import autopep8
autopep8.fix_code('x.has_key(y)\n', options={'aggressive': 1})
autopep8.fix_code('print( 123 )\n', options={'ignore': ['E']})
```

{% endtab %}
{% tab title='shell' %}

```sh
# 1. Install ubuntu / mac
apt-get install shellcheck
brew install shellcheck

# 2. yapf Trailing comma
golomb3 = [0, 1, 3]    """ Without Comma """
golomb3 = [            """ With Comma """
  0,
  1,
  3,
]
```

> Reference

<https://google.github.io/styleguide/pyguide.html#341-trailing-commas-in-sequences-of-items>

{% endtab %}
{% endtabs %}

## Linting

{% tabs %}
{% tab title='cpp' %}

* cppcheck
  * --enable=all
  * --suppress=missingIncludeSystem 00_pointer.cpp

```sh
# .clang-format
## sudo apt install -y clang-format-7
## sudo ln -s /usr/bin/clang-format-7 /usr/bin/clang-format

BasedOnStyle: google
UseTab: Never
IndentWidth: 4
CompactNamespaces: true   # doesn't indent after namespace {
ColumnLimit: 100          # break line after 100 char
```

{% endtab %}
{% tab title='python' %}

* Styles PEP Python Enhancement Proposals
* A code linter is a program that analyses your source code for potential errors → pylint

* pylint: Python static code analysis tool which looks for programming errors
  * inline disable pylint # pylint: disable=broad-except
  * `file/glob`: run linting on file/glob
  * --help
  * -v: verbose, print non-checker related info
  * --rcfile=`file`: specify path to .pylintrc file
  * --ignore=`file`: Ignore files
  * --ignore-patterns=`*.py`: Ignore patterns
  * --generate-rcfile: Create rcfile
  * --generated-members=`objects`

* .pylintrc
  * indent-string='  '
  * jobs=1: Use multprocess to speed up (0 will auto-detect the number of processors available to use)
  * load-plugins: (ex: pylint_django)

> pycodestyle

* check PEP8

* --version: show program version
* --exclude=`patterns`: exclude files which match these comma separated `patterns` (default: .svn,CVS,.bzr,.hg,.git,__pycache__,.tox)
* --indent-size=n: set how many spaces make up an indent

```sh
# 1. Setup
pip install pylint
pylint --generate-rcfile > .pylintrc

# 2. django
pylint --rcfile .pylintrc --ignore env **/*.py # All python file

# 3. .pylintrc
[MASTER]
#ignore=CVS                    # Add files or directories to the blacklist. They should be base names, not paths.
indent-string='  '
unsafe-load-any-extension=yes  # Allow loading of any C extensions. Imported into active interpreter and run arbitrary code

# A comma-separated packages, module names from where C extensions may be loaded.
# Extensions loads into  active Python interpreter and may run arbitrary code.
extension-pkg-whitelist=cv2

max-line-length=1024  # single line.
# run only  classes checker, but have no Warning level messages displayed
# --disable=all --enable=classes --disable=W
disable=
    C0114, # missing-module-docstring
    C0115, # missing-class-docstring
    C0116, # missing-function-docstring
    W0703, # Catching too general exception Exception (broad-except)
    R0801, # Similar lines in 2 files (duplicate-code)
    R1705, # Unnecessary "elif" after "return" (no-else-return)
    E0401, # (import-error)
    W0401, # (wildcard-import)

argument-naming-style=any    # Naming style matching correct argument names.
variable-naming-style=any    # snake_case, camelCase, PascalCase, UPPER_CASE
#argument-rgx=               # Regular expression matching correct variable names. Overrides variable-naming-style.
const-naming-style=camelCase # Naming style matching correct constant names.
```

{% endtab %}
{% endtabs %}

## Unit Test

{% tabs %}
{% tab title='cpp' %}

> gtest

* test fixtures allows for common setup and teardown between tests (::testing::Test)

* ASSERT_TRUE: break test if not true
* EXPECT_TRUE
* EXPENCT_EQ/NE/LT/LE/GT(A, B); # A and B should be same

{% endtab %}
{% tab title='python' %}

> unittest

* @skip

* setUp(self): Executed before each test
* tearDown(self): Executed after each test method
* test_name(self): test_* will run sequentially

* assertIn: Check string in string
* fail: Fails test

```py
from selenium import webdriver
import unittest

# 1. Basic Test
import unittest

class TestAll(unittest.TestCase):
  def setUp(self):
    pass

  def test_doc(self):
    self.assertIsNotNone("1")

  def tearDown(cls):
    pass  # use line_profile

if __name__ == "__main__":
  # run single test
  suite = unittest.TestSuite()
  suite.addTest(PageTester("test_doc"))
  runner = unittest.TextTestRunner()
  runner.run(suite)

  # run whole test
  unittest.main()

# 2. web Connection
class NewVisitorTest(unittest.TestCase):

  def setUp(self):
    self.browser = webdriver.Firefox()

  def tearDown(self):
    self.browser.quit()

  def test_can_start_a_list_and_retrieve_it_later(self):
    self.browser.get('http://localhost:8000')
    self.assertIn('To-Do', self.browser.title)
    self.fail('Finish the test!')

    # She is invited to enter a to-do item straight away
    # [...rest of comments as before]

if __name__ == '__main__':
  unittest.main()

# 3. Flaky
def get_latency(ping=None):
  if ping is None:
    ping = lambda: subprocess.check_output('ping -c 2 -i 0.2 -q 8.8.8.8')
  return ping()
```

{% endtab %}
{% endtabs %}

### coverage

{% tabs %}
{% tab title='python' %}

* [Coverage](https://coverage.readthedocs.io/en/coverage-5.5/) measures code coverage of Python programs

* coverage
  * pip install coverage
  * html: create
  * omit: [ex] "venv/*"
  * run
    * --source="." manage.py test: for django
  * report: generate text report

```sh
# 1. setup
pip install coverage
coverage run -m pytest arg1 arg2 arg3
coverage report -m

# 2. Test coverage : run tests, check your test coverage, and generate an HTML coverage report
coverage run -m pytest
coverage html
open htmlcov/index.html
```

```py
import doctest
import coverage

from . import models

cov = coverage.coverage()
cov.start()
doctest.testmod(models)
cov.stop()
with open("coverage.txt", "w") as f:
  cov.report(file=f)
```

{% endtab %}
{% endtabs %}

### Parametrization

* take values or objects defined within a function, and make them parameters to that function or method
* generalize the code

{% tabs %}
{% tab title='python' %}

```py
from unittest import TestCase
import pytest

param_list = [('a', 'a'), ('a', 'b'), ('b', 'b')]

# 1. unittest
class TestDemonstrateSubtest(TestCase):
  def test_works_as_expected(self):
    for p1, p2 in param_list:
      with self.subTest():
        self.assertEqual(p1, p2)

with self.subTest(msg="Checking if p1 equals p2", p1=p1, p2=p2):

# 2. pytest
@pytest.mark.parametrize('name, left, right', [['foo', 'a', 'a'], ['bar', 'a', 'b'], ['baz', 'b', 'b']])
def test_me(name, left, right):
  assert left == right, name
```

{% endtab %}
{% endtabs %}

## Integration Test

* Integrates multiple classes instead of testing them in isolation
* Runs the code on the actual platform that the customer will run it on
* [-] Slower than unit tests
* [-] Harder to find what is broken if a test fails
* [ex] Robolectric

> Term

* Snapshot testing: make sure UI didn't change, fail if two snapshots are different
  * snapshot artifact should be committed alongside code changes

{% tabs %}
{% tab title='javascript' %}

* jest
  * it: alias to test

```js
import React from 'react';
import renderer from 'react-test-renderer';
import Link from '../Link.react';

it('renders correctly', () => {
  const tree = renderer
    .create(<Link page="http://www.facebook.com">Facebook</Link>)
    .toJSON();
  expect(tree).toMatchSnapshot()
})
```

{% endtab %}
{% endtabs %}

## UI Test

* Tests actual user interaction with your application’s UI
* Test application features instead of class methods, can translate user stories to test cases really easily
* [-] Even slower than integration tests
* [-] Are prone to being “flaky”, Harder to find what is broken if a test fails

## Mocking

{% tabs %}
{% tab title='javascript' %}

> jest

* fn()
  * mock: where data about how the function has been called and returned are kept
* userRealTimer(): switch time globally
* userFakeTimers(): reset internal counters

```js
// 1. Test foreach using mock function
function forEach(items, callback) {
  for (let index = 0; indexn < items.length; index++) {
    callback(items[index]);
  }
}

const mockCallback = jest.fn(x => 42 + x)
forEach([0, 1], mockCallback);
expect(mockCallback.mock.calls.length).toBe(2)
expect(mockCallback.mock.calls[0][0]).toBe(0)
expect(mockCallback.mock.calls[1][0]).toBe(1)
expect(mockCallback.mock.results[0].value).toBe(42)

// 2. Mocking axois modules
/* users.js */
import axios from 'axios';

class Users {
  static all() {
    return axios.get('/users.json').then(resp => resp.data);
  }
}

export default Users;

/* users.test.js */
import axios from 'axios'
import Users from './users'

jest.mock('axois')
test('should fetch users', () => {
  const users = [{name: 'bob'}]
  const resp = {data: users}
  axois.get.mockResolvedValue(resp)

  return Users.all().then(data => expect(data).toEqual(users))
})

// 3. Test asynchronous call
test('the data is peanut butter', done => {
  function callback(data) {
    try {
      expect(data).toBe('peanut butter')
      done()
    } catch (error) {
      done(error)
    }
  }

  fetchData(callback);
})

test('the data is peanut butter', async() => {
  await expect(fetchData()).rejects.toBe('peanut butter');
})

// 4. Mock Timer
/* game.js */
function timerGame(callback) {
  console.log('Ready go!')
  setTimeout(() => {
    console.log("Time is up")
    callback && callback()
  }, 1000)
}

/* game.test.js */
jest.userFakeTimers()
test('waits 1 second before ending game', () => {
  const timerGame = requre('../timerGame')
  timerGame()
  expect(setTimeout).toHaveBeenCalledTimes(1)
  expect(setTimeout).toHaveBeenLastCalledWith(expect.any(Function), 1000)
})
```

{% endtab %}
{% tab title='python' %}

> unittest

* Mock(): removing the need to create a host of stubs throughout your test suite
  * callargs: arguments that the mock was last called with ([ex] .args, kwargs)
  * side_effect: function to be called, iterable, exception ([ex] KeyError('foo'), [3, 2, 1])
  * method()
    * assert_called(): called at least once
    * assert_called_once(): called exactly once

* patch(): decorator to test function taking string naming the function will be patched as arg (if 2+: bottom first)
  * [ex] @patch(module.classA): to test from module import classA

```py
import unittest
from unittest.mock import patch
from unittest.mock import MagicMock

# 1. Method mock
thing = ProductionClass()
thing.method = MagicMock(return_value=3)
thing.method(3, 4, 5, key='value')
thing.method.assert_called_with(3, 4, 5, key='value')

# 2. Temporary field
foo = {}
@patch.dict(foo, {'newkey': 'newvalue'})
def test():
  assert foo == {'newkey': 'newvalue'}
test()
assert foo == {}
```

{% endtab %}
{% endtabs %}

### Mocking Data

{% tabs %}
{% tab title='python' %}

> faker

* name() / job() / text(): more types in below

```py
from factory.django import DjangoModelFactory
import factory

# 1. Django facotry
class CoopFactory(DjangoModelFactory):
  class Meta:
    model = models.Coop

  phone = factory.SubFactory(PhoneContactFactory)
  email = factory.SubFactory(EmailContactFactory)

# 2. sqlfaker
from faker import Faker
from sqlfaker.database import Database
from collections import defaultdict
from sqlalchemy import create_engine

""" add database """
my_db = Database(db_name="housing")

""" add tables """
my_db.add_table(table_name="User", n_rows=500)
my_db.tables["studyprogram"].add_primary_key(column_name="studyprogram_id")
my_db.tables["studyprogram"].add_column(column_name="shortname", data_type="varchar(50)", data_target="name")
my_db.tables["studyprogram"].add_column(column_name="startdate", data_type="date", data_target="date")

my_db.tables["student"].add_primary_key(column_name="student_id")
my_db.tables["student"].add_column(column_name="firstname", data_type="varchar(50)", data_target="first_name")
my_db.tables["student"].add_column(column_name="lastname", data_type="varchar(50)", data_target="last_name")
my_db.tables["student"].add_foreign_key(column_name="studiengang_id", target_table="studiengang", target_column="studiengang_id")

# 3. fake data generator
import pandas as pd
from faker import Faker
from collections import defaultdict
from sqlalchemy import create_engine
fake = Faker()
fake_data = defaultdict(list)

for _ in range(1000):
  fake_data["first_name"].append( fake.first_name() )
  fake_data["last_name"].append( fake.last_name() )
  fake_data["occupation"].append( fake.job() )
  fake_data["dob"].append( fake.date_of_birth() )
  fake_data["country"].append( fake.country() )

df_fake_data = pd.DataFrame(fake_data)
df_fake_data

fake.fact

# 4. Other language
faker = Faker('cz_CZ')  # in Czech language

for i in range(3):
  name = faker.name()
  address = faker.address()
  phone = faker.phone_number()
  print(f'{name}, {address}, {phone}')
```

{% endtab %}
{% endtabs %}
