# File

{% tabs %}
{% tab title='c' %}

> cstdio

* C Standard Input and Output Library

* rename, remove(): Rename / Remove file
* tmpfile(): Open a temporary file
* tmpnam(): Generate temporary filename
* fopen() / fclose(): Open / Close file
* fflush(): Flush stream
* freopen(): Reopen stream with different file or mode
* setbuf(): Set stream buffer
* setvbuf(): Change stream buffering
* fprintf(): Write formatted data to stream
* scanf(): fscanf()     // Read formatted data from stdin / stream
* snprintf(): sprintf() // Write formatted data to sized buffer / string
* sscanf(): Read formatted data from string
* vfprintf(): Write formatted data from variable argument list to stream
* vfscanf(): Read formatted data from stream into variable argument list
* vprintf(): Print formatted data from variable argument list to stdout
* vscanf(): Read formatted data into variable argument list
* vsnprintf(): Write formatted data from variable argument list to sized buffer
* vsprintf(): Write formatted data from variable argument list to string
* vsscanf(): Read formatted data from string into variable argument list
* fgetc(): Get character from stream
* fgets(): Get string from stream
* fputc(): Write character to stream
* puts(): fputs()       // Write string to stdout / stream
* getc(): Get character from stream
* getchar(): Get character from stdin
* gets(): Get string from stdin
* putc(): Write character to stream
* putchar(): Write character to stdout
* ungetc(): Unget character from stream
* fread: Read block of data from stream
* fwrite: Write block of data to stream

{% endtab %}
{% tab title="cpp" %}

```cpp
// 1. copy file
ifstream src(src_file):
ofstream dst(dst_file):
dst << src.rdbuf();

// 2. class IO
class Human {
  string name;
  int age;

 public:
  Human(const string &name, int age) : name(name), age(age) {}
  string get_info() { return "Name :: " + name + " / Age :: " + to_string(age); }

  friend ofstream &operator<<(ofstream &o, Human &h);
};

ofstream &operator<<(ofstream &o, Human &h) {
  o << h.get_info();
  return o;
}

ofstream new_("data/fstream.txt");  // ifstream or ofstream for one
if (new_.is_open()) {
  new_ << "First\n";
  new_ << "Second\n";
} else {
  cout << "Not opened";
}
new_.close();

ofstream out("data/fstream.txt", ios::app);

Human h("Sean", 15);
out << h;  //  First
out.close();

ifstream in("data/fstream.txt");
string line;
char buf[100];
while (in) {
  in.getline(buf, 100);
  cout << buf << endl;  // First \n Second \n Name :: Sean / Age :: 15
}

in.close();

// 3. go to the beginning of the file
file.clear();
file.seekg(0, ios::beg);

ofstream ofs;
ofs.open("test.txt", ofstream::out / ofstream::trunc);  // delete
ofs.open("test.txt", ios_base::app);    // append
ofs.close()

// 4. File read : number of line count
file.unsetf(ios_base::skipws);
unsigned line_count = count(istream_iterator<char>(file), istream_iterator<char>(), '\n');
char ch;

fstream fin("file", fstream::in);
while (fin >> noskipws >> ch)
  cout << ch; // Or whatever

// 5. write and read law integer
ofstream numFile;
int num = 12345;
numFile.open( "numfile" );
numFile.write( (char*)&num, sizeof(num) ) ;
numFile.close();

ifstream numFileIn;
numFileIn.open( "numfile" );
int readN;
numFileIn.read((char*)&readN, sizeof(readN));
cout << readN << endl;
numFileIn.close();
```

{% endtab %}
{% tab title='javscript' %}

```js
{
  resolve: 'gatsby-source-filesystem',
  options: {
    name: 'blog',
    path: `${__dirname}/blog`,
    patterns: '**/*.md',
  },
},
```

{% endtab %}
{% tab title='python' %}

> fileinput

* FileInput
  * inplace: whether to overwrite the file

> shutil

| Function    | Copies metadata | Copies permissions | Uses file object | Dest can be dir |
| ----------- | --------------- | ------------------ | ---------------- | --------------- |
| copy        | No              | Yes                | No               | Yes             |
| copyfile    | No              | No                 | No               | No              |
| copy2       | Yes             | Yes                | No               | Yes             |
| copyfileobj | No              | No                 | Yes              | No              |

* copyfile(src)
* copy2(src)
  * dst: can be a directory, then basename of src is used for creating new file
  * it preserves the mtime and atime in the file metadata

```py
import fileinput
import pathlib
import shutil

# 1. fileinput
with fileinput.FileInput(filename, inplace=True, backup='.bak') as file:
  for line in file:
    print(line.replace(text_to_search, replacement_text), end='')

# 2. File IO
""" BAD """
file = open('some_file', 'w') # with open('some_file', 'w') as file: # (Context manager)
try:
  file.write('Hola!')
finally:
  file.close()

""" GOOD """
with open(filename, 'r+') as f: # prepend
  content = f.read()
  f.seek(0, 0)
  f.write(line.rstrip('\r\n') + '\n' + content)

with open('a', 'w') as a, open('b', 'w') as b: # Multiple file
  do_something()

# 3. Copy file
my_file = pathlib.Path('/etc/hosts')
to_file = pathlib.Path('/tmp/foo')

shutil.copy(str(my_file), str(to_file))  # For older Python.
shutil.copy(my_file, to_file)  # For newer Python.

# 4. subtract in glob
files = glob.glob('files_path/[!_]*')
set(glob("*")) - set(glob("eph*"))
```

{% endtab %}
{% tab title='shell' %}

* dd
  * -bs=`BYTES`: read and write up BYTES at a time [ex] **512**
  * -if=`FILE` : read from FILE instead of stdin ([ex] /dev/zero)
* head
  * `n`: print first / last `n` lines of each FILE to standard output ([ex] +1: entire file)
* tail
  * -f: wait for new strings, show dynamically

* more: additional development on “more” had stopped
  * uses same functions as vi editor
  * spacebar to go to the next page
* less: faster because it does not load the entire file at once
  * allows navigation though file using page up/down keys

* cat: reads files sequentially, writing them to the standard output
  * `filename`: [ex] < - : dashed file, /etc/*-release: linux distribution, file\ space
  * -T: print new line as ^IO
  * file | grep -vi "the": Print files with line the
  * file1.txt file2.txt > file3.txt: Merge two files into one

* Open (mac): Open in finder ([ex] .: current folder)

```sh
# 1. show multiple files, concat with filename
tail -n +1 *.txt
head -n +2 "$FILE": except first line

# 2. Delete all files with size 0
find /tmp -size  0 -print -delete
```

{% endtab %}
{% endtabs %}

{% include '.file.prob' %}

## Descriptor

{% tabs %}
{% tab title='cpp' %}

> fcntl.h

* int open(const char *pathname, int flags);
* int open(const char *pathname, int flags, mode_t mode);
  * -1 if error occurred, else new file descriptor
  * [errors]
  * EACCESS: permission denied
  * EFAULT: outside your accessible address space
  * ENOMEM: Insufficient kernel memory was available
  * ENOTDIR: specified path was not a directory

{% endtab %}
{% endtabs %}

## Glob

* {a, b}: multiple glob pattern

{% tabs %}
{% tab title='cmake' %}

```sh
# 1. search directory tree when cmake is invoked and put all files that match the pattern in `sources` and `data`.
file(GLOB_RECURSE sources      src/main/*.cpp src/main/*.h)
file(GLOB_RECURSE sources_test src/test/*.cpp)
file(GLOB_RECURSE data resources/*)
```

{% endtab %}
{% tab title='python' %}

```py
# 1. print all text files
import glob, os
os.chdir("/mydir")
for file in glob.glob("*.txt"):
  print(file)

# 2. Remove all empty files
indir="/Users/fzf058/IAMRoleRemovalfolder/IAMRoleRemovalFiles/iamroleremovalfiles/42618files/implementfolder"

os.chdir(indir)
fileList=glob.glob("*.csv")

for filename in fileList:
  if os.stat(filename).st_size==0:
    os.remove(filename)
```

{% endtab %}
{% tab title='shell' %}

| Symbol                     | Meaning                                              |
| -------------------------- | ---------------------------------------------------- |
| *                          | expands to all files (except .) in cwd unless quoted |
| ?                          | matches any single characte                          |
| [abc] / [a-c]              | matches any character from a, b, or c                |
| [^abc] / [!abc]            | matches any character except a, b, or c              |
| [[:alnum:]] / [A-Za-z0-9]  | Alphanumeric                                         |
| [[:alpha:]] / [A-Za-z]     | Alphabetics                                          |
| [[:space:]] / [\t\n\v\f\r] | All whitespaces                                      |
| [[:blank:]] / [ \t]        | space and tab                                        |
| ?(`PATTERN-LIST`)          | zero or one                                          |
| *(`PATTERN-LIST`)          | zero or more                                         |
| +(`PATTERN-LIST`)          | one or more                                          |
| @(`PATTERN-LIST`)          | match only once                                      |
| !(`PATTERN-LIST`)          | Not match                                            |

```sh
# 1. Echo with glob
echo y | docker system prune    # Say yes in one line
echo Hello      World      # Hello World
echo "Hello      World"    # Hello      World
echo Hello * World         # Hello (ls) World
echo "Hello "*" World"     # Hello * World

# 2. Globbing is expanded unless single qouteed
MYGLOB=*        # No quotes around the glob
echo $MYGLOB    # Glob is interpreted
MYGLOB="*"      # Double / single quotes around the glob
echo "$MYGLOB"  # *
echo '$MYGLOB'  # $MYGLOB
echo $MYGLOB    # Glob is interpreted

# 3. File selection
echo !(*.jpg|*.gif|*.png)               # except all image files
for f in * .*[^.]*; do echo "$f"; done  # select all with hidden files
```

{% endtab %}
{% endtabs %}

## Directory

{% tabs %}
{% tab title='cpp' %}

> filesystem

```cpp
#include <filesystem>
#include <iostream>

using namespace std::filesystem;
using namespace std;
int main() {
  create_directory("d");
  create_directory("d/sample");
  for (auto& p : directory_iterator("d")) cout << p.path() << '\n';
  remove_all("d");
}
```

{% endtab %}
{% tab title='python' %}

> os

* python3 -c 'import sys; print(64 if sys.maxsize > 2 ** 32 else 32)')

* close(fd): Close file descriptor fd
* ctermid(): filename corresponding to the controlling terminal of the process
* chdir(path): change directory
* execv(`path`, `argv`): execute an executable path with arguments, replacing current process
* execl(`file`, `*args`): execute the executable file with argument list args, replacing the current process
* getlogin(): name of the user logged in on the controlling terminal of the process
* rename(`old`, `new`): rename
* system(command): Execute the command (a string) in a subshell
* times(): current global process times
* rmdir(path, *, dir_fd=None): Remove directory path
* mkdir(path, mode=0o777, exists_ok=True): Create a directory named path
* os.path.exists('/usr/local/bin/'): check if path exists

* os.path
  * basename: data/item.csv → item.csv
  * isabs(): check if absolute path
  * abspath(path): Get absolute path
  * isfile(fn) / isdir(dn): Check file / directory exists

* os.sys
  * argv: List of command line arguments passed to a Python script
  * builtin_module_names: names of all modules that are compiled into this Python interpreter
  * byteorder: big vs little endian
  * executable: absolute path of the executable binary for the Python interpreter
  * flags
  * path: All path that is being search by python
  * version_info: assert sys.version_info[0]==3 and assert sys.version_info[1] >= 5
  * exit([arg])
  * cd()

* sys: provides access to variables used, maintained by interpreter and to functions that interact with interpreter

* platform: show platform information
* setswitchinterval(): set time slice
* read(): sys.stdin Read all input at once
* write(): sys.stderr
* getsitepackages(): see sitepackages
* ps1 / ps2: used for interactive mode string

{% endtab %}
{% tab title='shell' %}

* rmdir: remove directory

* mkdir: Create directory
  * -p dir1/dir2: nested directory

{% endtab %}
{% endtabs %}

### Directory View

{% tabs %}
{% tab title='python' %}

* os
  * getcwd(): current working directory
  * listdir(path='.'): List containing the names of the entries in the directory given by path

```py
# 1. recursively calculate size
import os

def get_recur_size(path='.'):
  total = 0
  if os.path.isfile(path):
    return os.path.getsize(path)
  else:
    return sum(get_recur_size(fn) for fn in os.scandir(path))
  return total

def human(size):
  for u in ['B', 'KB', 'MB', 'GB']:
    if size < 1024 :
      return f"{size:.1f} {u}"
    size /= 1024
  return f"{size:.1f} {'TB'}"

print(f"In {os.path.abspath('.')} \t {human(get_recur_size())}")
for fn in sorted(os.listdir('.'), key = get_recur_size, reverse=True):
  print(f"{fn} \t {human(get_recur_size('./' + fn))}")

# 2. Run ls
def ls():
  commands = "ls -a"

  process = subprocess.Popen(commands.split(), stdout=subprocess.PIPE)
  out, err = process.communicate()

  print(out)
  print(err)

```

{% endtab %}
{% tab title='shell' %}

* ls: lists contents in the directory
  * -a: show hidden file
  * -d: list directories as plain files
  * -h: human readable
  * -i: Lists IP sockets
  * -l: file mod, # links, owner, group, bytes, modified path
  * -R: recursively
  * -S / t: by size, date
  * -1 "$PWD/"*: get all absolute path

* pwd: print current working directory
* OLDPWD: previous working directory

* tree: (apt-get / brew) install tree (ubuntu / mac)
  * -d: Directory only
  * -f: Full path prefix for each file
  * -L `level`: specify recurse `level`
  * -I `pattern`: Do not list those files that match the wild-card `pattern`

{% endtab %}
{% endtabs %}

### Directory Navigation

{% tabs %}
{% tab title='shell' %}

* pushd: saves the cwd in memory

* popd: change directory that was most recently stored by pushd
* cd: change directory
  * `dir`: [ex] -: last directory, .. : parent directory, ~: home directory, "dir with_space": directory with space
  * -L: Follow symbolic links (default)
  * -P: Follow physical directory
  * $(dirname a/b/file.cpp): cd into file's located folder

{% endtab %}
{% endtabs %}

## Link

{% tabs %}
{% tab title='shell' %}

> Too many levels of symbolic links

* circular reference where a link is pointing back onto itself

> ln

* make links
* -f: remove existing destination files
* -lnf: overwrite existing symbolic link
* -n LINK: treat LINK as a normal file if it is a link to dir
* -s `orig` `linked`: Create Symbolic link

> unlink `linked`

* unlink linked files

{% endtab %}
{% endtabs %}

### Live Reload

* watchman: watch files and record when they changes
  * Recursively watch, without follow symlink
  * Wait for a root to settle down before it start to trigger notifications, can subscribe to file changes in a root

{% tabs %}
{% tab title='python' %}

* gh repo clone nathanwright1242/flask_livereload_example

{% endtab %}
{% tab title='shell' %}

* watchman
  * watch `file`: [ex] ~/src

```sh
brew update && brew install watchman  # Mac
```

{% endtab %}
{% endtabs %}

## Mount

{% tabs %}
{% tab title='shell' %}

* mount: attach filesystem found on device (type) at the directory dir
* umount

```sh
# 1. Mount unmount
sudo mount system.img temp_system
sudo umount temp_system

# 2. Show all mounted files
cat /proc/mounts
```

{% endtab %}
{% endtabs %}

## Object

{% tabs %}
{% tab title='shell' %}

* file: determine file type ([ex] dll, object, txt)

* objdump: prints contents of object files and final linked images
  * -a / -h a.o: information in archive's headers / headers
  * -s (-j section / -b) a.o: full contents  (in sections / in binary)
  * -d (-j section) a.o: show file disassembled codes (in section)
  * -p /lib/libutil.so | grep dep: check dependency

* hexdum
  * -C a.cpp: See original file with it

* string: print printable strings in a object, or other binary, file

* readelf: Display information about ELF files
  * when build type or cmake is changed, it becomes new binary

* binutils (mac)
  * -s libutil.so.1.5.4  | grep FILE: Which file contained in binary
  * -S program.so | grep debug_line

* ldd: print shared object required by each program (linux only) ([ex] $(which python), /bin/ls)
  * should not ldd on untrusted executable → objdump
  * doesn’t work on a.out shared libraries

* otool (mac)
  * -L a.out

* nm: display name list (symbol table) ([ex] `/module.so`: check for symbol)
  * -A: display fn
  * -C: decode low-level symbol names
  * -D: only display dynamic symbols
  * <> `object`: lists symbols from `object`

```sh
# 1. find location of function in binary (libutil.so.0.8.2 ! func@0x17 + 0x94c - [unknown source file])
-l -S libutil.so > a

# 2. od
od -i binary.out
# 0000000           0           1           2           3
# 0000020           4           5           6           7
# 0000040           8           9          10          11
```

{% endtab %}
{% endtabs %}

## Operation

{% tabs %}
{% tab title='shell' %}

* cp: copy file
  * -f: if destination file cannot be opened, remove and try
  * -T: if target already existed as a directory, then cp will fail
  * -r [directory]: copy all of the files including files inside of subfolders

* mv
  * -t `dest` `srcs...`: multiple files
  * `ls -1 | grep -v no_move.jpg` `folder`: move everything except one
  * ~/Linux/Old/!(Tux.png) ~/Linux/New/

* rm
  * `file`: ([ex] **/.git: Remove all nested .git file)
  * -r `dir`: Remove `dir` and contents recursively
  * !(`file`): Remove all except `file` ([ex] a.txt|b.txt)

* touch: Create or update modified date on file

* rename
  * "s/py/md/" *.pyj: rename all py to js

```sh
# 1. diff
diff ssh user@remote_host "cat foo" | diff - foo       # diff over remote
diff <(ssh server1 'cat foo') <(ssh server2 'cat foo') # diff two remote file
```

{% endtab %}
{% endtabs %}

## Patch

* diff: Check whether two files are equal
  * `a` `b`: Diff over two files ([ex] <(echo a) <(echo b): Print diff of two output command)
  * -y: Display side by side

## Redirection

* processed left to right

{% tabs %}
{% tab title='shell' %}

* Xargs
  * -E: (for mac)
  * -0: Change xargs to expect NUL
  * -t: prints command that will be executed to terminal

* |: pipe ([ex] `cmd1` | `cmd2`: takes standard output of cmd1 as standard input to cmd2)
* `n`<: takes standard input from file ([ex] **0**: can be omitted)
* \>: directs standard output to file
* \>|file: forces standard output to file even if noclobber is set
* \>\> file: directs standard output to file, append to file if it already exists

```sh
# 1. Pipe examples
n>|file    # forces output to file from file descriptor n even if noclobber is set
<> file    # uses file as both standard input and standard output
n<>file    # uses file as both input and output for file descriptor n
n>file     # directs file descriptor n to file
n<file     # takes file descriptor n from file
n>>file    # directs file description n to file; append to file if it already exists
n>&        # duplicates standard output to file descriptor n
n<&        # duplicates standard input from file descriptor n
n>&m       # file descriptor n is made to be a copy of the output file descriptor
n<&m       # file descriptor n is made to be a copy of the input file descriptor
&>file     # directs standard output and standard error to file
<&-        # closes the standard input
>&-        # closes the standard output
n>&-       # closes the ouput from file descriptor n
n<&-       # closes the input from file descripor n

# 2. read .env
eval $(grep -v -e '^#' .env | xargs -I {} echo export \'{}\')

# 3. Preserve whitespaces
echo ' A     B' xargs -I {} echo "{}"

# 4. Run all video
find . -regex ".*mp4" -print0 | xargs -0 -L 1 python3 scripts.py open_video
seq 10 | xargs ls "video{}.mp4" | xargs -0 -L 1 python3 scripts.py open_video

# 4. xargs
find . -name "to_move*" | xargs -I{} mv {} ./class/book/images/ # find and move
ls problem/*/ | grep -v ":" | xargs -I {} sh -c "ag "filter/{}.md" > /dev/null || echo {}" # Xargs multiple command
git log --diff-filter=D --summary | grep images | cut -b 20- | xargs -I {} git checkout HEAD^ {}  # Restore all removed files
```

{% endtab %}
{% endtabs %}

{% include '.awk.prob' %}

### Paste

{% include '.paste.prob' %}

### Grep

{% tabs %}
{% tab title='shell' %}

* grep: global regular expression print
  * key * \c
  * -A num: how many lines after the match
  * -B num: how many lines before the match
  * -c `pattern`: How many patterns appear on file
  * -C `num`: how many lines `num` before, after the match
  * -E `epattern`: as an extended regular expression [ex] =+, ab*
  * -h: remove file name
  * -i: Case-insensitive search
  * -l / L: Lists the files which do / do not include the search term
  * -n: Show matching line numbers
  * -v: Reversing the meaning of a grep search
  * -o: Output only matched substrings
  * -r: Recursively search subdirectories listed
  * -rL "print" .: all files without print
  * -w: specifying word boundary

* fgrep: file pattern searcher

* egrep: extended grep
  * '19|20|25' calendar: grep multiple patterns

```sh
# 1. grep example
grep -c "^##" *.md       # Count number of heading on markdown
grep "patern1\|pattern2" # multiple pattern
grep -rnw '/path/to/somewhere/' -e 'pattern'  # Search on file (use ag)
grep -rL "\[\/\/\]" * | cut -d\/ -f-2 | uniq -c | sort # Count number of markdowns that doesn't contain comments
grep -how "images/.*.png" *.md | xargs -I{} mv "../theory/math/{}" images/ # move files
```

{% endtab %}
{% endtabs %}

{% include '.grep.prob' %}

### Sed

* stream editor for filtering and transforming text
* invalid command code
* for OS use empty argument -i ''

* s/: Replace
* /p: print
* -n: suppress line echoed to stdout after commands
* -i.bak: In place
  * backup is requiremnt in BST (blank for no backup ' ')

```sh
sed 's/.$//'              # remove last character
sed '0,/pattern/ d' file  # remove first line if pattern
sed '/^#[^!]/d' `file`    # remove all comments except shebang
sed "s/hello/hi/" file    # Replace hello to hi in file.txt
sed -n  :nclude/p;q file  # (p)rints all cpp files, then (q)uits
sed -i '1d' file          # delete first line
sed -i ':BJ/d' file       # delete first line if match
sed -i '1s :h1\n/' file   # append to beginning of file

# 4. Replace file in-place
sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/g' /etc/ssh/sshd_config;
```

{% include '.sed.prob' %}

### Seq

{% include '.seq.prob' %}

### Comm

{% tabs %}
{% tab title='shell' %}

```sh
# 1. See union contents in file1, 2
comm -12 < (cat file1 | sort) < (cat file2 | sort)
```

{% endtab %}
{% endtabs %}

### Modify File

{% tabs %}
{% tab title='shell' %}

* awk: (Aho, Weinberger & Kernighan)
  * gsub(regexp, replacement [, targ]): Global replacement of string
  * FS: File separator
  * OFS: Output file separator
  * NF: The number of fields in the current input record
  * NR: The total number of input records seen so far
  * -F: Specify the input field separator
  * '_[$0]++' *.csv: Find duplicate line
  * '{print}' input.txt: Prints every line of data from the specified file
  * '/PAT1/,/PAT2/' file: Lines between inclusive

```sh
# 1. AWK example
awk '{print NR,$0}' input.txt             # NR prints line number, $0 prints entire string
awk '/abc/ {print}' input.txt             # Prints every line containing abc
awk 'NR==n {print $0}' input.txt          # Prints n th line
awk -F 'pattern' 'NF{print NF-1}' b4      # Count number of pattern in each line
awk '/ptn/ {c++} END {print c}' input.txt           # Count pattern in the string
awk '{ t = $1; $1 = $2; $2 = t; print; }' file      # Swap first two column
awk '/PAT1/{flag=1; next} /PAT2/{flag=0} flag' file # lines between exclude PAT1, PAT2
```

{% endtab %}
{% endtabs %}

### Inspect File

{% tabs %}
{% tab title='shell' %}

* wc: [ex] tr -cd ',' | wc: Count specific character
  * -l: Counter number of lines

```sh
# 1. find
find . ! -empty -type f -exec md5usm {} + | sort | uniq -d # Print all duplciate files (md5 in mac)
fgrep "*" *     # List all files with aesterisk

# 2. Count
find . -name '*.py' -type f | xargs wc -l | sort # Counte number of line for each python files
du -a | cut -d/ -f2 | sort | uniq -c | sort -nr  # the number of files in each directory
```

{% endtab %}
{% endtabs %}

## Search

{% tabs %}
{% tab title='python' %}

* algolia
  * full-text search
  * client
    * SearchClient.create('key', 'cred'): create client
  * index
    * client.init_index('page'): create index
    * clear_objects(): remove all objects
    * save_objects()

{% endtab %}
{% tab title='shell' %}

* ag: multithreading / case-insensitive like ack
  * apt install silversearcher-ag (linux) / brew install the_silver_searcher (mac)
  * `pattern`: [ex] '\b8000\b'
  * -u: Search everything
  * -C `n`: `nc` lines around
  * --hidden: find hidden file, except ~/.agignore
  * -G `file` `pattern`: specific python ([ex] '\.py' 'import')

* find: walk a file hierarchy
  * -empty: True if file or directory is empty
  * -exec: [ex] ls -l {} \;: pipe with ls -l
  * -group: [ex] `group`
  * -L: Follow symlink
  * -maxdepth: search upto level ([ex] 4)
  * -mmin -`n`: modified in last `n` minutes
  * -name: file with name ([ex] `name`)
  * -path '*/nested/folder/\*': Find nested folder
  * -print: print matching file
  * -printf '%TY-%Tm-%Td %TT %p\n' | sort -r
  * -regex `regex`: Find file with name / regex
  * -size `size`: [ex] 1033c for 1033 bytes
  * -type: [ex] d: Directory, f: file, l: symbolic link
  * -user: [ex] `user`

```sh
# 1. find
find . -type d -empty -print/-delete  # print / remove all empty directory
find . -type f -execdir mv "{}" .. \; # Move to its parrent folder
find / -name art 2>/dev/null          # Ignore all errors when find
find / -name file | grep -v "Permission denied" # Ignore Permission denied
find . -path "*migrations*" -name "*.py" -not -path "*__init__*" # all django migration files
find * . -not -iwholename '.git' -type f -exec sed -i '' 's/ *$//' '{}' ';' # remove trailng spaces recursively
```

{% endtab %}
{% endtabs %}

## Shell

![History](images/20210323_002858.png)

* Environment is set at login and are valid for the duration of the session

> Terms

* Shell: a program which processes commands and returns output, like bash in Linux
* Terminal: program that run a shell

| Application             | sh  | csh | ksh | bash | tcsh |
| ----------------------- | --- | --- | --- | ---- | ---- |
| Job control             | N   | Y   | Y   | Y    | Y    |
| Alias                   | N   | Y   | Y   | Y    | Y    |
| I/O redirection         | Y   | N   | Y   | Y    | N    |
| Command history         | N   | Y   | Y   | Y    | Y    |
| Command line editing    | N   | N   | Y   | Y    | Y    |
| vi Command Line editing | N   | N   | Y   | Y    | Y    |
| Underlying Syntax       | sh  | csh | ksh | sh   | csh  |

* bash (born again shell)
  * -c string: commands are read from string. Arguments after string are assigned to positional parameters, from $0

* csh (c shell)

* zsh
  * Recursive path expansion → For example “/u/lo/b” expands to “/usr/local/bin”
  * Spelling correction and approximate completion: will fix minor mistake typing a directory name
  * Plugin and theme support: ZSH includes many different plugin frameworks

* Linux
  * Developed originally by Bell Laboratorie
  * Kernel interacts with computer hardwares to allow software / hardware to exchange information
  * Tries to make the distribution more user-friendly with more convenient features
  * Four categories based on original distribution - Arch, Debian, Red Hat, and Slackware

* Red Hat: CentOS, Fedora, and Red Hat Enterprise Linux are derived

* BSD
  * Linux: MacOS

* Ubuntu: Desktop based Linux distribution

* type: like cat in linux

{% tabs %}
{% tab title='sql' %}

* sqlite
  * .headers on: turn on headers
  * .tables: list all tables
    * 'a%': list variables starts with a

{% endtab %}
{% endtabs %}

{% tabs %}
{% tab title='window' %}

* WSL: compatibility layer for running Linux binary executables natively on Windows 10

* Win+R shell:startup \(current user\) shell:common \(all user\)
* systeminfo: checks 32, 64 bitness
* new-alias vi notepad: use vi to replace notepad

```text
C:\>echo hi > a.txt
C:\>echo bye > b.txt
C:\>type a.txt b.txt > c.txt
C:\>type c.txt
```

{% endtab %}
{% endtabs %}

> Broken pipe

* IP changed or server can't guarantee security

> Connection to _ closed by remote host

* Administrator Disconnect

> getcwd() failed: No such file or directory

* execute a command from a path that doesn't exists (deleted by other terminal)

> The System is going down for reboot NOW!

* Remote server shuts down

> Unable to fetch some archives, maybe run apt-get update or try with --fix-missing?

* -> run apt update
* apt install tftp

> Problem with update-manager: No module named 'apt_pkg' in Ubuntu 13.10, having installed Python 3.4 on /usr/local/lib

* sudo apt-get install --reinstall python3-apt

> device or resource busy (when rm file)

* lsof +D /path and kill
* umount /path

> ~ doesn't give correct value

* Tilda must be first character of word and not quoted

> Pseudo-terminal will not be allocated because stdin is note a terminal

* ssh -tt

> You have a new mail

* /var/mail/$USER or /var/spool/mail/$USER
* django cronjob has failed

> Reference

<https://mug896.github.io/bash-shell/>

## Shebang

* \#! used in the first line of the script allowing text file to be read as executable

{% tabs %}
{% tab title='shell' %}

```sh
#!/bin/sh -                         # - prevents file argument not interpreted as argument for sh
#!/usr/bin/env python               # env search for PATH when executing
#!/usr/bin/env -S gawk -v AA=100 -f # -S allow shebang to use multiple options
```

{% endtab %}
{% endtabs %}

* \#!/bin/bash -e: set which shell to run
* /etc/skel/.bashrc: reset rc files to original

* dconf
  * reset -f `path`

* dscl (mac)
  * sudo scutil --set HostName mac: Change host Display name gyuseung@mac
  * read /Groups/admin GroupMembership: Reading the membership of the admin group:
  * append /Groups/admin GroupMembership usershortname: Adding a user
  * delete /Groups/admin GroupMembership usershortname: Removing a user: (from the group not the system)

* getent: get entries from Name Service Switch libraries
  * group: show all groups (also show groups obtained through LDAP or Yellow Pages)

* shopt `zsh`: shell builtin command to set and unset (remove) various Bash shell options
  * -s: Set options
    * dotglob nullglob: also glob hidden file
    * extglob: allows bang
    * globstar: allow glob-operator (\*\*) to be recursive (ex: \*\*/\*.py)
  * -q: Suppresses normal output

* setxkbmap
  * -option: remove all options ([ex] caps:escae: swap capslock with esc)

* ubuntu-drivers
  * devices: show drivers

### Alias

* disabled in non-interactive shell, child process
* enabled in subshell
* set shortcut to command
* \aliased_command: temporaily disable aliased command using backslash
* alias untar='tar -zxvf '

* alias
* declare: set variabele values and attributes, make pipeline fails if error
  * -f `foo`: Show all defined functions named `foo`

* unalias `cmd`: remove alias for `cmd`

* type `cmd`: print out what `cmd` the alias will run

### Boot

* grub: GRand Unified Bootloader

* update-grub

* /etc/init.d: The directory containing System V init scripts
* /etc/default/grub: [ex] GRUB_CMDLINE_LINUX_DEFAULT="quiet splash nouveau.modeset=0"

{% tabs %}
{% tab title='ubuntu' %}

* service: run a System V init script
* systemctl: control systemd system and service manager

```sh
service --status-all | grep +
```

{% endtab %}
{% endtabs %}

### Kernel

{% tabs %}
{% tab title='ubuntu' %}

* used to override default kernel parameter values, only a small number of parameters is predefined

* sysctl: modify kernel parameters at runtime
  * -a: Display all values currently available
  * -p: load in sysctl settings from file epecified ([ex] **/etc/sysctl.conf**)

```sh
# /etc/sysctl.conf
```

> ENOSPC: System limit for number of file watchers reached

* fs.inotify.max_user_watches=524288 | sudo tee -a /etc/sysctl.conf

{% endtab %}
{% endtabs %}

### User

> Terms

* root: aka superuser, administrator, admin or supervisor who can do everything
  * Unix-like systems, for example, the user with a user identifier (UID) of zero
* Owner: the assigned owner of the file or directory
* Group: members of the group that owns the file or directory
* Other: all other users that owns the file or the directory

* History from file
  * /var/log/secure: Red Hat
  * /var/log/auth.log: Debian

* chmod: change mod
  * -R: change files and directories recursively

* chown: change owner
  * -R `whoami` `/usr/local`: change user / group ID for file hierarchies
  * user:group filename: transfer filename to user, group

* groups: display all groups
  * user: list of all groups a user belongs to (first group is primary)

* id: print real and effective user and group IDs
  * -u: print only effective user ID

* usermod
  * -a: Add the user to the supplementary group
  * -g: List of supplementary groups which the user is also a member of
  * -l new old: change username

* restart: restart computer

* last: check login history
  * -15: all logged user
  * `user`: history of `user`
  * pts/2: terminal conncted

* lastlog: reports user's last login information from /var/log/last/log

* lastb: check user's bad login history

* w: Show who is logged on and what they are doing

* who: show who is logged on

* su: switch user
  * `user`: Change to `user`
  * -c `cmd`: Pass single `cmd` to user

* passwd: change password of current user
  * `user`: change password for other `user`
  * -d: delete password
  * -e: make passwd expired
  * -l: locking account
  * -u: unlocking account

* adduser: non-interactive, and not distro-specific (preferred)
* useradd: native binary compiled with the system
  * -m: create the home directory

* userdel
  * -r: removes files in the user's home directory along with the home directory itself

```sh
# 1. Add group
sudo usermod -aG docker ${USER}

# 2. OS Info
cat /etc/os-release

# 3. List User and Groups
cut -d: -f1 /etc/passwd
cut -d: -f1 /etc/group | sort

# 4. Add User
vi /etc/default/useradd
HOME=/home/sean
useradd vivek
passwd sean
finger sean
```

### Super user

* sudo: run in previleged mode
  * -g `group`: Run with primary group set to `group` instead of specified by target user's password database entry

* visudo: edit sudoer file, locks the sudoers file against simultaneous edits
  * add to sudo group
  * usermod -aG sudo id

```sh
# 1. /etc/sudoers
Defaults:chris timestamp_timeout=20  # in minute, negative for infinite timeout
Defaults:ravi      !authenticate     # Totally disable
root  ALL=(ALL)   ALL                # Do not prompt password

# 2. Dockerfile
local result=1
which sudo 2>&1 1>/dev/null
[ $? -eq 0 ] && result=0        # 0 - ok/ 1 - nok
sudo -Hiu $user env | grep $var # grep other person’s env

Add user (default id: 1000)
ARG USER_ID=1002

RUN useradd -ms /bin/bash ${USER_NAME} && usermod -aG wheel ${USER_NAME} \
  && echo "${USER_NAME} ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/${USER_NAME} \
  && echo 'Defaults env_keep = "http_proxy https_proxy"' >> /etc/sudoers.d/${USER_NAME}
```

> Error sudo: command not found

* apt install sudo

## Process Command

* exec
  * `shell`: redefine the current shell to `shell`
  * `cmd` `args`: run `cmd` name remaining as arguments
    * if `cmd` doesn't exists, exits on error

* pgrep: find or signal processes by name

* fuser: show which processes are using a specified computer file, file system, or Unix socket
  * -v -n tcp 80: check what processes are using a network port:

* ltrace: intercepts library calls and system calls made by your application to C libraries such as glibc
  * analyze the performance of libraries when they are used by applications

* strace: intercepts system calls make by glibc and other libraries directly into Linux Kernel
  * uses ptrace to inspect system calls by the process and how long each took
  * -f

* ps
  * <>: PPID PID PGID SID TTY TPGID STAT UID TIME COMMAND
  * a: show processes for all users
  * u: display the process's user/owner
  * x: show processes not attached to a terminal
  * -e: show the environment after the command
  * -f: ASCII art process hierarchy
  * -L pid: Prints all thread used by pid
  * -o thcount= pid: Total thread in pid

* sleep: default is seconds, m, h, d

* top: show cpu usage (use htop)
  * current time | uptime | users sessions logged in | average load on the system (1, 5, 15 min)
  * Processes totals (73 total) | running | sleeping | stopped | waiting to be stop from parent
  * user | system | priority nice |  I/O operations | hardware interrupts | software interrupts | hypervisor
  * PID: PID of the process(4522)
  * USER: The user that is the owner of the process (root)
  * PR: priority of the process (15)
  * NI: The “NICE” value of the process (0)
  * VIRT: virtual memory used by the process (132m)
  * RES: physical memory used from the process (14m)
  * SHR: shared memory of the process (3204)
  * S: S=sleep R=running Z=zombie D=uninterruptible sleep, IO (S)
  * %: percentage of CPU used by this process (0.3)
  * %: RAM used by the process (0.7)
  * TIME: total time of activity of this process (0:17.75)
  * COMMAND: name of the process (bb_monitor.pl)
  * -o key: Order process display by sorting on key in descending order
  * -n nprocs: Only display up to nprocs processes
  * -user user: Only display processes owned by user
  * k: Kill Process (PID and signal-9)
  * c: display full command
  * u: Specify process of user
  * shift + t: Sort by longest uptime
  * shift + m: Sort by largest memory usage
  * shift + p: Sort by largest CPU usages
  * space: refresh

* vm_stat (mac): show Mach virtual memory statistics

```sh
# 1. Thread
cat /proc/sys/kernel/threads-max # possible thread count
ps ax -L --no-headers | wc -l    # currently running thread count
ps -o thcount= 19783             # number of thread used by process

# 2. ps
ps axjf           # display the process tree on Linux
ps aux | grep apt # see all downloading files
ps ax -L --no-headers | wc -l           # Total thread now
ps /proc/sys/kernel/threads-max         # Total possible thread
ps ax -o pid,nlwp,cmd  | sort -nr -k2,2 # Ordered by number of threads
```

### Cron

* [Check cron syntax](https://crontab.guru/)
* sudo service cron reload: CentOS7
* sudo /etc/init.d/crond reload: CentOS with cPanel
* Setup ![Cron setup on mac](images/20210510_220511.png)

{% tabs %}
{% tab title='javscript' %}

> Nodecron

![nodecron](images/20210217_201302.png)

* Node.js is in practice single-threaded
* Communication methods
* priority queue (Kue is a common queue library)

* expression string: Cron expression
* function Function: Task to be executed
* options Object: Optional configuration for job scheduling
* Options
  * scheduled: A boolean to set if the created task is schaduled. Default true;
  * timezone: The timezone that is used for job scheduling

```js
// 1. Node schdule
const j = schedule.scheduleJob('00 30 11 * * 1-5', () => {
  console.log('Cron-style Scheduling')
})

/* Recurrence Rule Scheduling
   Sun ~ Sat 0 ~ 6
   월 ~ 일 17시 45분 실행 */
const rule = new schedule.RecurrenceRule();
rule.dayOfWeek = [0, new schedule.Range(0, 6)];
rule.hour = 17;
rule.minute = 45;
const k = schedule.scheduleJob(rule, () => {
  console.log('Recurrence Rule Scheduling');
})

// 2. Node cron
var cron = require('node-cron');    // Starts the scheduled task.
var task = cron.schedule('* * * * *', () =>  {
  console.log('stoped task');
}, {
  scheduled: false
  timezone: "America/Sao_Paulo"
});

task.start();         // The task won't be executed unless re-started.
var cron = require('node-cron');
var task = cron.schedule('* * * * *', () =>  {
  console.log('will execute every minute until stopped');
});

task.stop();          // The task will be stopped and completely destroyed.
var cron = require('node-cron');
var task = cron.schedule('* * * * *', () =>  {
  console.log('will not execute anymore, nor be able to restart');
});

task.destroy();       // Validate that the given string is a valid cron expression.
var cron = require('node-cron');
var valid = cron.validate('59 * * * *');
var invalid = cron.validate('60 * * * *');
```

> Reference

[Comparison](https://velog.io/@filoscoder/%EC%8A%A4%EC%BC%80%EC%A4%84-%EC%97%85%EB%AC%B4-%EC%9E%90%EB%8F%99%ED%99%94-Node-cron-vs-Node-schedule-%EB%B9%84%EA%B5%90-clk4dyynve)

{% endtab %}
{% tab title='python' %}

> django-crontab

* pip install django-crontab
* Doesn't work on window

* Put 'django_crontab' in settings.py

> django-admin crontab cli

* add
* remove
* show
* run `job_hash`: test crontab (put hash returned by add)

{% endtab %}
{% tab title='shell' %}

* cron: daemon to execute scheduled commands

* crontab
  * -l: list all cron
  * -e: open cron file

```sh
# ┌────────────── second (optional)
# │ ┌──────────── minute
# │ │ ┌────────── hour
# │ │ │ ┌──────── day of month
# │ │ │ │ ┌────── month
# │ │ │ │ │ ┌──── day of week
# │ │ │ │ │ │
# │ │ │ │ │ │
# * * * * * *

0 * * * *           # Every hour
*/10 * * * * *      # Every ten seconds.
0 0 6,19 * * *      # 6:00 AM and 7:00 PM every day.
0 0/30 8-10 * * *   # 8:00, 8:30, 9:00, 9:30, 10:00 and 10:30 every day.
```

{% endtab %}
{% tab title='jenkins' %}

```sh
@overnight @hourly @midnight @daily
pipeline {
  agent any
  parameters {
    string(name: 'Greeting', defaultValue: 'Hello', description: 'How should I greet the world?')
  }
  stages {
    stage('Example') {
      steps {
        echo "${params.Greeting} World!"
      }
    }
  }
}
```

{% endtab %}
{% tab title='github' %}

* on
  * schedule
    * cron: [ex] "0 17 \* \* \*"

{% endtab %}
{% endtabs %}

## Util Command

* htop: visualize memory usage in top

### Multiplexing

* tmux: Terminal multiplexer
  * new -s: create session with name
  * ls: list all sessions
  * kill-session -t 0: kill with session name 0
  * attach-session -t 0: attach with session name 0
  * C-b d: Detach from session
  * C-b [: Scroll Up and down
  * C-b PgUp

* code: open file in vscode
  * -n: Create a new window
  * -r .: Open current directory in most recently used window
  * -diff f1 f2: Open diff editor

### Media

* pdfseparate: brew install poppler
  * -f `int`: first page to extract (inclusive)
  * -l `int`: last page to extract (inclusive)
  * -v: print copyright and version info
  * -h: print usage information

* convert
  * `*.jpg` `output.pdf`: convert jpg to pdf
  * `a.pdf` -flatten output-%02d.jpg: convert pdf to jpg
  * -quality 100
  * -density 200
  * -colorspace sRGB

* imagemagick: displaying, converting, and editing raster image and vector image file
  * brew install imagemagick
  * --with-fontconfig --with-ghostscript --with-openjpeg --with-webp

* ffmpeg
  * -i video.mp4 2>&1 | grep Duration: get duration of video

* apropos `description`: search the whatis database for strings

* compgen: Not avaiable in zsh
  * -c: lis all available command you can run
  * -k: list all the keywords you could run

### Terminal

* clear: clear terminal

* chsh
  * -s /bin/bash user: change user’s shell to bash

* env (printenv): Print all local variables

* export: a new shell is spawned to run the script
  * & pass environment values to a child process
  * export LC_ALL=C: Change shell language to english
  * export name=sean: Set name variable to sean
  * /etc/environment: sets variable system wide for every user on boot
  * /etc/bash.bashrc: executed if the bash shell is opened
  * ~/.`shell_name`rc: to make it run when start an interactive shell
  * ~/.`shell_name`profile: to make when log in

* locale: print enabled language
  * -e: any trap on ERR is inherited by shell functions (bash -e)
  * -o `pipefail`: return value of a pipeline is value of last (rightmost) command to exit

* locale-gen : en_US.UTF-8: Create UTF-8

* set: change shell options, set positional parameters, display names and values of shell variables
  * use - to set and + to unset (ex. set -e)
  * Set | unset values of shell options and positional parameters
  * -a: automatically export all variables
  * -P: If set, follow symbolic links when executing commands

* source: run command in current shell (useful for setting env variable)
  * When script run (with ./myscript.sh), it creates own process context (a new process environment)

* stty: change and print terminal line settings
  * -g, --save: print all current settings in a stty-readable form

* unset: remove exported variable

* lsb_release: LSB (Linux Standard Base) and distribution-specific information on the CLI
  * -a: Display all information
  * [ex]

    LSB Version : core-4.1-amd64:core-4.1-noarch
    Distributor ID: : CentOS
    Description: [ex] CentOS Linux release 7.7.1908 (Core)
    Release: [ex] 7.7.1908
    Codename: [ex] Core

* uname: Print operating system name
  * -a: Behave as though all of the options -mnrsv were specified
  * -m: machine hardware name
  * -n: nodename (name that system is known by to communication network)
  * -p: machine processor architecture name
  * -r / s / v: operating system release / name / version
* screen (consider tmux)

```sh
# 1. os name check
if command -v lsb_release >/dev/null 2>&1; then
  OS_NAME=$(lsb_release -i -s)
fi

case "$(uname -s)" in
  Darwin)
    export ARCHDIR=$PWD/mips-mac/bin
    ;;
  Linux)
    export ARCHDIR=$PWD/mips-x86.linux-xgcc/
    ;;
esac

# 2. Load env
if [ -f .env ]; then
  export $(cat .env | sed 's/#.*//g' | xargs)
fi

can_escalate_privileges()  # by default (e.g. on Linux) user can do so
{
  local result=0
  if [ "$(uname)" = "FreeBSD" ]; then
    if ! groups $USER | grep wheel 2>&1 1>/dev/null; then
      result=1
    fi
  fi
  return $result
}

system_cpu=`uname -m`
```

## File Command

> Terms

* Ubuntu
  * /bin: Executables needed in single user mode and to bring system up or repair
  * /etc: System related configuration file (local static file to control program operation)
  * /sbin: holds commands needed to boot the system for sudo user
  * /issue: Check Linux Version
  * /etc/paths: look for commands
  * /etc/hosts: Static table lookup for hostnames
  * /etc/init.d: start/stop scripts used to control daemon while system is running boot
  * /etc/services: Internet network service list
  * /opt: Install unbundled packages, each in its own subdirectory
  * /proc: interface to kernel data structures
  * /proc/pid: exe a copy of the binary image of the running process
  * /proc/sys: Info about system, allows system admin  to enable, disable kernel features
  * /usr: Files under it are shareable between OS instances
  * /usr/local: Install files built by administrator (make), not managed by system packager
  * /var: Variable data files (spool dir | files, administrative, log, transient | temp files)

* mac
  * /boot: /System/Library/Kernels
  * /home: /Users
  * /root: /var/root

* chattr
  * `+ / -`: Adds / removes attribute to existing attribute of files
  * =: Keep the existing attributes that the files have
  * i: immutable

* basename
* dirname

| orig         | dir      | bas  |
| ------------ | -------- | ---- |
| /usr/lib/log | /usr/lib | /log |
| /usr/        | /        | usr  |
| usr          | .        | usr  |
| /            | /        | /    |

* lsattr: lists the file attributes on a second extended file system
* stat: displays the size and other stats of a file/directory or a filesystem
* patch: apply a diff file to an original
* locate: fast but less accurate
* whereis: locate the binary, source, and manual page files for a command

* which: returns the pathnames of the files which would be executed in the current environment

* dirs: display the list of currently remembered directories
  * -p: Causes dirs to print the directory stack with one entry per line

* readlink
  * -f: show full path

```sh
# 1. check if file is binary
if [ -f "$filename" -a "$(file -b --mime-encoding "$filename")" = binary ]; then
  echo It\'s a binary file
fi
```

{% tabs %}
{% tab title='mac' %}

```sh
brew install coreutils
alias readlink=greadlink
```

{% endtab %}
{% endtabs %}

### Disk

* df: disk free, report file system disk space usage
  * -a: file system's complete disk usage even if the Available field is 0
  * -h: human readable format

* du, disk usage
  * [-H | -L | -P] [-a | -s | -d depth] [-c] [-h | -k | -m | -g] [-x] [-I mask] [file ...]
  * -a: all files and folders
  * -s: display only a total for each argument
  * -d: max-depth
  * -h: human readable
  * -h -d1

* fdisk: show disk size along with disk partitioning info
  * -l: List partition tables for specified devices and exit

* dmidecode (DMI / SMBIOS table decoder)
  * sudo dmidecode | egrep "Socket Designation: Proc|((Thread|Core) Count)"

* ulimit
  * -c unlimited: dump core to current directory

* sysctl: Read and set values in /etc/sysctl.conf (kernel parameters)
  * sysctl kernel.core_pattern: get segfault location
  * sysctl -a | grep machdep.cpu / swap: show cpu / swap info in mac

* lsblk: lists information about all or the specified block devices

* getconf: retrieve standard configuration variables

* systemd: system daemon

* systemctl: Control the systemd system and service manager
  * disable Unit
  * removes all symlinks to the unit files backing the specified units from the unit configuration directory
  * undoes any changes made by enable or link
  * get-default: get default target
  * list-units --type target: get all target (--all to print unactivated)
  * set-default name.target: change default target
  * isolate graphical.target: change target without reboot
  * enable: hook specified unit into relevant places → start on boot
  * list-units PATTERN: List units that systemd currently has in memory
  * list-sockets PATTERN: List socket units currently in memory
  * start PATTERN: Start (activate) one or more units specified on the command line
  * disable deviceservie:
  * status / / ssh: check status of root mount / ssh

* quota: display disk usage and limits
  * -g: Print group quotas for the group of which the user is a member

```sh
# 1. du
du  * -hs * | sort -h # order by size
du -a | cut -d/ -f2 | sort | uniq -c | sort -nr # count # of files each dir : -a | cut -d/ -f2 | sort | uniq -c | sort -nr

# 2. Change max number of watcher
echo fs.inotify.max_user_watches=524288 | sudo tee -a /etc/sysctl.conf && sudo sysctl -p
```

### Linux

* add-apt-repository: ([ex] ppa:deadsnakes/ppa)

* apt: native Ubuntu system-wide package manager (apt-get is one of apt parts → mostly can be ignored)
  * packages are usually updated for each separate Ubuntu release
  * used with the Debian family distributions and handles deb software packages
  * autoremove: remove installed dependencies with applications and are no longer used by anything else on the system
  * update: update apt
  * upgrade: upgrade packages
  * full-upgrade: if needed previously installed packages are removed to make the upgrade happen
  * list --installed: List installed packages
  * /var/lib/apt/lists: Storage area for state information for each package resource
  * /var/lib/apt/lists/partial/: Storage area for state information in transit
  * install
    * -y `package`: accept all while downloading

* apt-show: explain repository ([ex] software-properties-common)

> Waiting for cache lock: Could not get lock /var/lib/dpkg/lock-frontend” while installing applications in Ubuntu

```sh
sudo lsof /var/lib/dpkg/lock
### COMMAND PID USER FD TYPE DEVICE SIZE/OFF NODE NAME
### xxxxxx 5383 root 7aC REG 6,3 0 210001 /var/lib/dpkg/lock-frontend

sudo kill -9 5383  # Kill the process
sudo rm /var/lib/dpkg/lock  # Remove/Delete the lock file
sudo rm /var/cache/apt/archives/lock  # Remove the lock from the cache folder
sudo dpkg --configure -a  # Check and correct the interrupted dpkg process if any (So we do no end up with broken packages)
```

> Package 'python3.7' has no installation candidate

```sh
apt update
apt install python3 python3-pip software-properties-common
add-apt-repository ppa:deadsnakes/ppa
apt install python3.7
```

{% tabs %}
{% tab title='window' %}

* choco install `package` ([ex] python)
* [Install](https://chocolatey.org/docs/installation)
* Debian: open source community, stability and security
* freeze and scrutinize all packages → packages can be a little old
* Linux Mint, Ubuntu, Elementary OS, and Kali Linux

{% endtab %}
{% tab title='mac' %}

* packages compiled to version-specific subdirectories → multiple versions can be in machine
* Homebrew is a 3rd party addition – on both macOS and Ubuntu
* cask is extension to brew that allows management of graphical applications through Cask project

* casks
* cleanup: run occasionally to avoid running out of disk
* install adoptopenjdk8: 9, 10, 11
  * --cask
* link: creates symlinks to installations you performed
  * --overwrite: overwrite existing symlink
* list: list all available formula
* services
  * start postgres
  * stop postgres
* tap adoptopenjdk/openjdk: install old java
* uninstall `formula`: Uninstall formula

{% endtab %}
{% endtabs %}

### Yum

* usually used with the RHEL family OS's and handles RPM software packages

* /etc/yum.conf: configuration file and related utilities
* /etc/yum.repos.d/: options
* install `package`: [ex] git
* remove `package`
* autoremove `package`: remove unneeded dependencies
* list: list all packages

{% tabs %}
{% tab title='shell' %}

* !, %, .,:, @, {, }

```sh
# ls
echo `ls` wolrd     # print inside

# shift.sh a b c d
echo "Total arguments passed are: $#"
echo "The arguments are: $*"      # $* is used to show the command line arguments
echo "The First Argument is: $1"  # a

echo "The First Argument After Shift 2 is: $1"  # c
shift
echo "The First Argument After Shift is: $1"    # d
```

{% endtab %}
{% endtabs %}

## Expansion

> Arithmetics

* $(( )): $(( 1 + 2 )) ..

> brace

* echo a{d,c,b}e: ade ace abe
* mkdir /usr/local/{old,new}: create multiple
* *(patternlist): matches zero or more occurrences of the given patterns
* +(patternlist): matches one or more occurrences of the given patterns
* ?(patternlist): matches zero or one occurrence of the given patterns
* @(patternlist): matches exactly one of the given patterns
* !(patternlist): matches anything except one of the given patterns

> Tilde

* ~ is expanded ONLY if it is the first character of a word AND it is unquoted
* ~-: old pwd
* ~-/+ n: same as dirs -/+ n
* -fred: home directory of the user fred

> Parameter

{% tabs %}
{% tab title='shell' %}

* ${`var`:-word}: if `var` exists and isn't null, return its value; otherwise return word
* ${`var`:word}: if `var` exists and isn't null, return its value; otherwise return word
* ${`var`:=word}: if `var` exists and isn't null, return its value; otherwise set it word and then return its value
* ${`var`:?message}: if `var` exists and isn't null, return its value
  * otherwise print `var`, followed by message and abort current command or script
* ${`var`:+word}: if `var` exists and isn't null, return word; otherwise return null
* ${`var`:offset:length}: performs substring expansion
  * returns the substring of $`var` starting at offset and up to length characters

* ${`var`#`pat`}: if `pat` matches beginning of the `var`, delete shortest / loogest(##) part that matches and return rest
* ${`var`%`pat`}: if `pat` matches end of `var`, delete shortest / longest(%%) part that matches and return rest
* ${`var`/`pat`/string}: longest match to `pat` in `var` is replaced by string. Only first match is replaced
* ${`var`//`pat`/string}: longest match to `pat` in `var` is replaced by string. All matches are replaced

```sh
# 1. Parameter expansion
echo "${PATH//:/$'\n'}"
```

{% endtab %}
{% endtabs %}
