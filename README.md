# README

This repository is for transferring knowledge and save snippets with unified syntax

Any comments, contributions are welcome.

```sh
# Fix wrong images
make fix_include
```

## Tags

* Sometimes, multiple language or tool support same feature
* I combined them using [Gitbook Syntax](https://docs.gitbook.com/) ([ex] \{\% tabs %} \{\% tab title='' \%\})
  * This prevents to create too much header ([ex] cpp.md#list, java.md#list, python.md#list)

> Example

* Available tabs that goes into the same \{% tabs %}
* Language tabs: C, cmake, C++, html (jinja), java, javascript, python, shell, sql, sv, vim
* Tool tabs: git, vscode, linux, window, jenkins, docker, apple, google, amazon

## Convention

1. Break if current tags are more than 1~20 ([ex] list (*) -> Angle bracket (>) -> h3 -> h2 -> file -> repo -> file)
1. Use hyphen (-) for embed and file name (gitbook generates hypen when url encodes)
1. Always follow linting rules with pre-commit
1. Problem language is ordered alphabetically ([ex] c -> cpp -> java -> python -> shell)
1. Using [include_file](https://github.com/SeanHwangG/include_file) syntax
1. Put Reference in corresponding header so that others can also see additional contents

## Block Quote

* Content in each header is further devided into section with following block quote (>)

> Example

* Available Block quotes in order
* Terms
* Question / Solution: Only for Programming questions
* Example
* Error
* Reference: Enclosed with angular bracket

## Programming Sites

* [Problem information, difficulty is handled using following django project](https://github.com/SeanHwangG/classroom)
* Site: baekjoon (BJ_*), codechef (CC_*), codeforce (CF_*), hackerrank (HR_*), kattis (KT_*), leetcode (LC_*)

* Planning to make these API publicly in graphQL
