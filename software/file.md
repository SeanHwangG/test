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
{% tab title='python' %}

> fileinput

* FileInput
  * inplace: whether to overwrite the file

```py
import fileinput

# 1. fileinput
with fileinput.FileInput(filename, inplace=True, backup='.bak') as file:
  for line in file:
    print(line.replace(text_to_search, replacement_text), end='')

# 2. File IO
with open(filename, 'r+') as f: # prepend
  content = f.read()
  f.seek(0, 0)
  f.write(line.rstrip('\r\n') + '\n' + content)

# 3. with open('some_file', 'w') as file: # (Context manager)
file = open('some_file', 'w')
try:
  file.write('Hola!')
finally:
  file.close()

# 4. Open multiple file
with open('a', 'w') as a, open('b', 'w') as b:
  do_something()
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
{% tab title='shell' %}

* rmdir: remove directory

* mkdir: Create directory
  * -p dir1/dir2: nested directory

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

## Directory Navigation

{% tabs %}
{% tab title='shell' %}

* OLDPWD: previous working directory

* tree: (apt-get / brew) install tree (ubuntu / mac)
  * -d: Directory only
  * -f: Full path prefix for each file
  * -L `level`: specify recurse `level`
  * -I `pattern`: Do not list those files that match the wild-card `pattern`

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

{% tabs %}
{% tab title='shell' %}

```sh
cmd1|cmd2  # pipe; takes standard output of cmd1 as standard input to cmd2
< file     # takes standard input from file
> file     # directs standard output to file
>> file    # directs standard output to file; append to file if it already exists
>|file     # forces standard output to file even if noclobber is set
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
```

{% endtab %}
{% endtabs %}

## Search

{% tabs %}
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
