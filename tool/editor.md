# Editor

* map
  * map / imap: normal, visual mode / insert mode
  * unmap: cancel mapping
  * inoremap: insert mode non recursive
  * n / i: normal / insert mode
  * v / s / x: visual select mode / select mode / visual mode only
  * c: command-line
  * l: lang-arg o pending
  * \<D\-: mac command
  * \<CR>: carriage return usually the Enter on your keyboard
  * :map: see current mapping
  * remap: makes mappings work recursively
  * nnoremap: one that works in normal mode
  * `<silent>`: show no message when this key sequence is used
  * `<leader>`: let mapleader = autocmd
  * `<C-l> <Esc>:w<CR>`:!clear;python %\<CR\>: run python script
  * filetype cpp nnoremap \<F5>:w \<bar> exec '!g++ -g -O2 -std=gnu++17 -static %'\<CR>: run cpp

* Copy
  * yy: yank line
  * dd: delete and copy current line
  * ggyG: yank entire file
  * :d: delete current line
  * :m0: move current line to line 0
  * :wqa: write close all
  * :%w !pbcopy: copy to clipboard
  * :r !pbpaste: paste from the clipboard
  * :w !sudo tee %: without permission

* -o *: Open with horizontal split
* -o *: Open with vertical split
* -p *: Open with each tab
* -r .swp: recover swp file
* --version: Show version

## Visual

* ctrl + v: multiple line
* U: Capitalize

```sh
ctrl + v | shift + i # enter : python multiline comment
```

## Macro

* q[a-z][command]q
* @a

* :reg: Show all current macro
* "": unnamed | default register
* “+: clipboard
* "kyy: copy current line to register k
* “kp: paste k register

## Navigation

```sh
# 1. Navigation
0 | $          # begin | end of the line
^              # first non-blank character
( | )          # begin | end of the current paragraph
zt | z. | zb   # cursor top | middle | bottom
H | M | L      # move to top | middle | low of the page
w / W          # jump by start of words (punctuation considered words / spaces separate words)
e / E          # jump to end of words (punctuation considered words / no punctuation)

]] / [[        # move the cursor a section forwards or to the next { / previous {

gg / G         # go to first / last line
ge             # jump backward to end of words
nG             # go To line n

CTRL-f | b     # scroll full screen forward | backward
CTRL-d | u     # scroll half screen forward | backward

# 2. Search
/copy\C / \c   # Case sensitive / insensitive
* / #          # Search current word forward / backward
:g/pattern/d   # delete all line matching patterns
:g!/pattern/d
:g/^\s*$/d     # delete all blank lines
:g/^$/d        # Delete empty line
\c             # ignore case
:s/sunny/(&)/  # & is matched text
:g/pattern/m$  # Move all lines matching a pattern to end of file

f/Fx           # search line forward / backward for 'x'
t/Tx           # search line forward / backward before 'x'
```

### Mark

* :marks: list all the current marks
* :delmarks a: delete mark
* ma: make a bookmark named a at the current cursor position
* `a: go to position of bookmark a
* 'a: go to the line with bookmark a
* `.: go to the line that you last edited

## Editing

* ~: Change the case of current character

```sh
# 1. Editing
r               # replace a single character (does not use insert mode)
R               # enter Insert mode, replacing characters rather than inserting
J               # join line below to the current one

g~iw            # switch case of current word
guw             # make current word lower / upper(U) case
gu$             # make lower / uppercase (U) until end of line
==              # auto-indent current line

# 2. Deleting
x               # delete current / previous character
dw              # delete the current word
dd              # delete (cut) a line
dt\'            # delete until the next ' character on the line (replace ' by any character)
D               # delete from cursor to end of line
:[range]d       # delete [range] lines

# 3. Spelling
]/[s            # next / previous misspelled word
zg              # add word to wordlist
zug             # undo last add word
z=              # suggest word

```

## Files

* .vimrc: Located in home\(~\) directory, get run every time when open vim

* expand
  * ("%"): path/file.txt
  * ("%:t"): file.txt
  * ("%:r"): path/file
  * ("%:e"): txt
  * ("%:p:h"): /home/you/path/file.txt

* split
  * :tabe file: in a new tab
  * Ctrl+w+r: vsplit swap window
  * Ctrl+w+=: vsplit resize equal dimension
  * :vs file: in a split mode
  * :Sex / Vex: split and open file explore
  * :tabnew file: open as a new tap

```vim
<!-- 1. vimrc -->
:so ~/.vimrc            # apply vimrc

set num                 # show line number
syntax on               # coloring
set tabstop=4           # Change Tab into 4 spaces
set shiftwidth=4        # Change >> length to 4
set et                  # Convert tab to space
set hlsearch            # highlight all matches in a file when perform a search,
set incsearch           # highlight next match while you're still typing search pattern
verbose                 # where setting is from

set encoding=utf-8      # Korean support
set fileencodings=utf-8,cp949

# AUTOCOMPLETE RELATED
func! AutoClose(...)
  let cur = getline(".")[col(".")]
  if cur != a:1
  if a:1 == "'" || a:1 == '"'
    execute "normal!a".a:1.a:1
  else
    execute "normal!a".a:1
  endif
  execute "normal!h"
  else
  execute "normal!l"
  endif
endfunc

inoremap ( ()<left>
inoremap [ []<left>
inoremap { {}<left>
inoremap ) <ESC>:call AutoClose(')') <CR>a
inoremap ] <ESC>:call AutoClose(']') <CR>a
inoremap } <ESC>:call AutoClose('}') <CR>a
inoremap " <ESC>:call AutoClose('"') <CR>a
inoremap ' <ESC>:call AutoClose("'") <CR>a
inoremap {<CR> {<CR>}<ESC>O
inoremap {;<CR> {<CR>};<ESC>O

" COMMAND RUN related
func! RunScript(...)
  execute ":wa"
  let fileName = a:1
  let fileType = a:2

  if fileType == 'cpp'
  execute ":!g++ -std=c++11 -o ".fileName fileName.".cpp && cat ".fileName.".txt 2> /dev/null | ./".fileName
  elseif fileType == 'py'
  execute ":!cat input.txt 2> /dev/null |" "python3" fileName.".py"
  endif
endfunc

nnoremap <C-l> :call RunScript(expand('%<'), expand('%:e')) <CR>

""autocmd *.py nnoremap <F5> :w <CR>:!cat input.txt 2> /dev/null | python % <CR>

"" SYNTAX
syntax on
colorscheme evening
se nu tabstop=4 shiftwidth=4 softtabstop=4 smarttab expandtab autoindent
set hlsearch  " highlight search and search while typing
set incsearch

"" SCREEN
noremap <Left> <C-w><Left>
noremap <Right> <C-w><Right>

:e []/file        # Reload current file | Open new file

! : ignore vimrc mapping configure
execute "normal! ihello my name is sean"

startinsert
strftime("%c")
type(var) ==   type(0) / type(function("tr")) / type([]) / type({}) / type(0.0)

%              # current file name
q:             # history
:saveas        # save file as
```

## Lastline

* :![cmd]: run terminal command
* :history: Last command
* :help key-notation: man page
* :retab: Repace tab to spaces
* :3,5y: copy from line 3 to 5

```vim
<!-- lastline -->
command Gb :normal i {% tabs %} <CR> {% tab title=""} <CR> {% endtab %} <CR> {% endtabs %} <ESC>
```

## Vimscript

```sh
# 1. Primitive
str2float("2.3")
str2nr("3")
float2nr("3.14")

# 3. Dictionary
count(dict, 'x')
empty(dict)
get(dict, "apple")
has_key(dict, 'foo')
keys(dict)
len(dict)
max(dict)
min(dict)
remove(dict, "apple")
let longlist = mylist + [5, 6]
let mylist += [7, 8]
mylist[2:]
let alist = add(mylist, 4)

# Construct
let colors = {
\ "apple": "red",
\ "banana": "yellow"
}

# Access
echo colors["a"]

for key in keys(dict)
  echo key . ': ' . dict(key)
endfor

# 4. List
let longlist = mylist + [5, 6]
let mylist += [7, 8]
mylist[2:]
let alist = add(mylist, 4)
```

### Operation

{% tabs %}
{% tab title='vim' %}

```vim
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
  " …
elseif char == "\<RightMouse>"
  " …
else
  " …
endif

# 2. For Loop
for s in list
  echo s
  continue  " jump to start of loop
  break     " breaks out of a loop
endfor

# 3. While Loop
while x < 5
endwhile
```

{% endtab %}
{% endtabs %}

### Function

* Vimscript functions must start with a capital letter if they are unscoped

{% tabs %}
{% tab title='vim' %}

```vim
<!-- function -->
let temp = @@
let @@ = temp  : prevent overwriting current register

function Varg(...)
a:000    # a list containing all the extra arguments that were passed
a:0      # number of argument
a:1      # first argument

<!-- 2. CPrototype -->
func! CPrototypeFunction()
let temp = @@
  exe "normal! mayy"
  exe "normal! /Prototypes\<CR>"
  exe "normal! )kpA;\<ESC>"
  exe "normal@ 'a"
let @@ = temp
endfunc
```

{% endtab %}
{% endtabs %}

> Terms

* Integrated development environment
