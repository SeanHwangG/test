# Extensions

## Text extension

* Avro: row-oriented remote procedure call and data serialization framework developed within Apache's Hadoop project
* Parquet: free and open-source column-oriented data storage format of the Apache Hadoop ecosystem
* ini: text-based content config file a structure and syntax comprising key-value pairs for properties
* ORC: Optimized Row Columnar file format provides a highly efficient way to store Hive data

* mime: two-part identifier for file formats and format contents transmitted on the Internet
  * image/png, text/html, text/plain

* tar: collecting several files into one archive file, including videos and images, for easier distribution
  * contain useful information about files contain, user permissions, dates, directory structures

* xml: Extensible Markup Language, load to dom → everything into memory
  * markup language that defines a set of rules for encoding documents both human and machine-readable
  * SAX → Simple API for XML
  * &apos;: '
  * &quot;: "
  * &lt:: <
  * &gt;: >
  * &amp;: &

### csv

* [+] easy import / export
* [-] No type information / No standard / No unicode support

{% tabs %}
{% tab title='python' %}

```py
import csv

data = ['4', '5', '6']

with open('data1d.csv', 'w') as csvFile:
  writer = csv.writer(csvFile)
  writer.writerow(data)

csvFile.close()

with open('data1d.csv') as csvFile:
  csvReader = csv.reader(csvFile, delimiter=',')
  for row in csvReader:
    print(row)

# write | read 2d file
data = [['height','weight','age'],
    [155,66,27],
    [177,82,34],
    [155,66,27],
    [175,70,32],
    [195,99,21],
    [157,52,17],
    ["",52,17]]

with open("data2d.csv","w") as my_csv:
  writer = csv.writer(my_csv, delimiter=',')
  writer.writerows(data)

with open('data2d.csv') as csvFile:
  csvReader = csv.reader(csvFile, delimiter=',')
  for row in csvReader:
    print(row)
```

{% endtab %}
{% endtabs %}

### json

* Keys are unique Strings that cannot be null
* Values can be anything from a String, Boolean, Number, list, or even null
* [+] serialization format or serving up data for your APIs
* [-] lacking features to support editing, comment

{% tabs %}
{% tab title='python' %}

* encoding Python Objects into JSON is called Serialization
* python -m json.tool file.json: pretty json file

* dumps(): encode JSON Data into native Python String
* dump(): encode and store JSON Data into a file
* load(`fp`): read from `fp`
  * object_hook: optional function that will be called with the result of any object literal decoded
  * parse_int: if specified, will be called with the string of every JSON int to be decoded
  * parse_constant: if specified, will be called with one of the following strings: '-Infinity', 'Infinity', 'NaN'
* loads(`json_str`): Deserialize `json_str` (str, bytes or bytearray)
* dumps(parsed): pretty print json
  * indent=4
  * sort_keys=True

{% endtab %}
{% tab title='shell' %}

```sh
# 1. Parse single column
echo '{"json":"obj"}' | python -m json.tool  # Validate and pretty print
curl -s http://example.com | python -c 'import sys, json; print(json.load(sys.stdin)["country"])'
wget 'http://127.0.0.1:8000/swagger/?format=openapi' -O - -q | python -m json.tool --indent 2 > api.json

# 2. print keys
sudo apt-get update
sudo apt-get install jq
cat a.json | jq -r 'keys[]'
```

{% endtab %}
{% tab title='python' %}

```py
import json
import os
import pathlib
import functools

# 1. basic crud
data = [{ 'name' : 'saen', 'age' : 16 }]  # read write
with open("data_file.json", "w") as write_file:
  json.dump(data, write_file, indent=4, ensure_ascii=False)  # ensure_ascii for korean character

with open("data_file.json", "r") as read_file:
  data = json.load(read_file)
print(data)

""" Recursive print """
def pprint(obj):          # recursively decode all lists
  import json
  if isinstance(obj, list):
    return repr(obj).decode('string-escape')
  elif isinstance(obj, dict):
    return json.dumps(self.__dict__, indent=4, ensure_ascii=False)

# 2. json db
class JsonDB():
  def add(self, collection_id, documents, overwrite=True):
    if not isinstance(documents, list):
      documents = [documents]

    pathlib.Path(f"{PATH.DB}/{collection_id}").mkdir(parents=True, exist_ok=True)
    for document in documents:
      document_id = document.__dict__[collection_id + "_id"]
      document_path = PATH.DB / collection_id / f"{document_id}.json"
      if os.path.exists(document_path) and not overwrite:
        return False
      with open(document_path, "w") as f:
        json.dump(document.__dict__, f, ensure_ascii=False)
    return True

  def delete(self, collection_id, document_id, ignore_missing=True):
    logger.debug(f"delete({collection_id}, {document_id})")
    document_path = PATH.DB / collection_id / f"{document_id}.json"
    if document_path.exists:
      os.remove(document_path)
    elif not ignore_missing:
      return False
    return True

  @functools.lru_cache
  def get_all(self, collection_id):
    logger.debug(f"get_all({collection_id})")
    collection_path = PATH.DB / collection_id
    document_id2obj = {}
    for document_path in collection_path.iterdir():
      with open(document_path, "r") as f:
        document_id2obj[document_path.name[:-5]] = dict2class(collection_id, json.load(f))
    return document_id2obj

  def get(self, collection_id, document_ids):
    document_id2obj = self.get_all(collection_id)
    if not isinstance(document_ids, list):
      document_ids = [document_ids]
    documents = []
    for document_id in document_ids:
      documents.append(document_id2obj[document_id])
    return documents[0] if len(documents) == 1 else documents

local_db = JsonDB()
```

{% endtab %}
{% endtabs %}

### yaml

* YAML is a superset of JSON, which means you can parse JSON with a YAML parser
* suited for configuration, readable and editable by humans
* ability to self reference, support for complex types, embedded block literals, comments
* [-] YAML parsers are younger and have been known to be less secure

* y|Y|yes|Yes|YES|n|N|no|No|NO|true|True|TRUE|false|False|FALSE|on|On|ON|off|Off|OFF
* list: - disktype=ssd
* map: - disktype: ssd

{% tabs %}
{% tab title='python' %}

> yaml

* safe_load()

```py
import yaml
import io

# 1. IO YAML file
data = {
  'a list': [1, 42, 3.141, 1337, 'help', u'€'],
  'a string': 'bla',
  'another dict': {
      'foo': 'bar',
      'key': 'value',
      'the answer': 42
  }
}

with io.open('data.yaml', 'w', encoding='utf8') as outfile:
  yaml.dump(data, outfile, default_flow_style=False, allow_unicode=True)

with open("data.yaml", 'r') as stream:
  data_loaded = yaml.safe_load(stream)

print(data == data_loaded)

# 2. Parse gitbook.yaml
with open(f"{options['gitbook_conf_dir']}/.gitbook.yaml", 'r') as stream:
  gitbook_yaml = yaml.safe_load(stream)
  book_path = f"{options['gitbook_conf_dir']}/{gitbook_yaml['root']}"
  summary_path = f"{book_path}/{gitbook_yaml['structure']['summary']}"
```

{% endtab %}
{% endtabs %}

### toml

* parser is ~300 lines of pure Python code

## Ext Image

* Bitmap Picture (BMP): Does not support effective image compression
  * easily created from existing pixel data stored in an array
  * Images that will be sent to print

* Graphics Interchange Format (GIF): have fewer colors, smaller file size, 256 colors → quality deterioration
  * Very small Icon, animation, simple drawing → animated files

* Joint Photographic Experts Group (JPEG): 24bit color with up to 16million colors
  * Lossy compression, standard format for most digital cameras
  * Great for making smaller sizes
  * Compatible across MAC, PC, mobile, web browser

* portable network graphics (PNG): lossless compression
  * Portable Network Graphics
  * Background images without jagged edges
  * PNG 8: smaller than GIF, 256 colors and 1 bit transparency
  * PNG 24: larger than JPEG
  * Use for text images, Images while editing process

* obj: a geometry definition file format

* svg (Scalable Vector Graphics): responsive

* tiff: Tagged Image Format File
  * Can be viewed and edited in nearly every photo editing software

{% tabs %}
{% tab title='python' %}

```py
from PIL import Image

def getSize(size) :
  return str(size[0]) + ' columns x ' + str(size[1]) + ' rows'

def getMode(mode) :
  if(mode == 'RGB'):
    return '3x8-bit pixels, true colour'
  elif(mode == 'RGBA') :
    return '4x8-bit pixels, true colour with transparency mask'
  elif(mode == 'CMYK') :
    return '4x8-bit pixels, colour separation'
  elif(mode == 'L') :
    return '8-bit pixels, black and white'
  elif(mode == 'P') :
    return '8-bit pixels, mapped to any other mode using a colour palette'
  elif(mode == 'YCbCr') :
    return '3x8-bit pixels, colour video format'
  elif(mode == 'RGBA') :
    return '1-bit pixels, black and white, stored with one pixel per byte'
  elif(mode == 'I') :
    return '32-bit signed integer pixels'
  elif(mode == 'F') :
    return '32-bit floating point pixels'
  else :
    return 'Unknown'

im = Image.open("/Users/sean/github/data/images/dining_table.jpg")
pix = im.load()
print(f'color at [w, h] \t {pix[10, 20]}')          # color at [w, h]    (140, 141, 133)
print(f'size \t {getSize(im.size)}')                # size    500 columns x 500 rows
print(f'mode \t {str(im.mode)} {getMode(im.mode)}') # mode    RGB 3x8-bit pixels, true colour
```

{% endtab %}
{% endtabs %}

## Latex

![Latex](images/20210214_175128.png)

* [Resume Ltex](https://www.overleaf.com/articles/anon-resume/bwtbvhrstvdh)

{% tabs %}
{% tab title='latex.sh' %}

```sh
# 1. Starts From 0
\setcounter{section}{-1}

# 2. Put string before section
\usepackage{titlesec}
\titleformat{\subsection}{\normalfont\large\bfseries}{Task \thesubsection}{1em}{}

# 3. Change sub sections to arabic
\renewcommand{\thesubsection}{\thesection.\alph{subsection}}
\renewcommand\thesubsection{\thesection.\arabic{subsection}}

\arabic (1, 2, 3, ...)
\alph (a, b, c, ...)
\Alph (A, B, C, ...)
\roman (i, ii, iii, ...)
\Roman (I, II, III, ...)
\fnsymbol (∗, †, ‡, §, ¶, ...)
```

{% endtab %}
{% endtabs %}

> Number

* Fraction
  * \over{1}{2}

> Figure

{% tabs %}
{% tab title='figure.latex' %}

```sh
# Multiple Figures
\begin{figure}[H]
  \centering
  \begin{minipage}[b]{0.45\textwidth}
  \includegraphics[width=\textwidth]{images_new/d1.png}
  \caption{Loss for 0.0001 L2}
  \label{pca_vectors}
  \end{minipage}
  \hfill
  \centering
  \begin{minipage}[b]{0.45\textwidth}
  \includegraphics[width=\textwidth]{images_new/d1_2.png}
  \caption{Accuracy for 0.0001 L2}
  \label{pca_vectors}
  \end{minipage}
\end{figure}

# ordered vs unordered
\begin{itemize/enumerate}
  \item One entry in the list
  \item Another entry in the list
\end{itemize/enumerate}
```

{% endtab %}
{% endtabs %}

* Spacing
  * \!: -3 mu
  * \quad: 18 mu
  * \qquad: 36 mu

### Latex Table

{% tabs %}
{% tab title='matrix.latex' %}

```sh
# 1. Vector
\left[\begin{array}{c} 1\\0\\1\end{array}\right]

# 2. Every Grid
\begin{center}
\begin{tabular}{ | m{5em} | m{1cm}| m{1cm} | }
\hline
cell1 dummy text dummy text dummy text & cell2 & cell3 \\
\hline
cell1 dummy text dummy text dummy text & cell5 & cell6 \\
\hline
cell7 & cell8 & cell9 \\
\hline
\end{tabular}
\end{center}

\begin{table}[]
\begin{tabular}{lllll}
 &  &  &  &  \\
 &  &  &  &  \\
 &  &  &  &  \\
 &  &  &  &
\end{tabular}
\end{table}

# 3. Matrix
\documentclass{article}
\usepackage{amsmath}
\begin{document}
\[
\begin{bmatrix}
  x_{11}       & x_{12} & x_{13} & \dots & x_{1n} \\
  x_{21}       & x_{22} & x_{23} & \dots & x_{2n} \\
  \hdotsfor{5} \\
  x_{d1}       & x_{d2} & x_{d3} & \dots & x_{dn}
\end{bmatrix}
=
\begin{bmatrix}
  x_{11} & x_{12} & x_{13} & \dots  & x_{1n} \\
  x_{21} & x_{22} & x_{23} & \dots  & x_{2n} \\
  \vdots & \vdots & \vdots & \ddots & \vdots \\
  x_{d1} & x_{d2} & x_{d3} & \dots  & x_{dn}
\end{bmatrix}
\]
\end{document}
```

{% endtab %}
{% endtabs %}

## Markdown

* a lightweight markup language for creating formatted text using a plain-text editor
* [Syntax Highlight](https://support.codebasehq.com/articles/tips-tricks/syntax-highlighting-in-markdown)
* `![sample](/assets/tux.png)`: images

* Distribution
  * Rmarkdown: Datavisualization in R

{% tabs %}
{% tab title='python' %}

* panflute + pypandoc
  * make pandoc filters

```py
import io
import pypandoc
import panflute

# 1. serialize markdown
def action(elem, doc):
  if isinstance(elem, panflute.Header):
    doc.header.append(elem)

if __name__ == '__main__':
  raw_doc = pypandoc.convert_file('book/cpp/cpp.md', 'json')
  doc = panflute.load(io.StringIO(raw_doc))
  doc.header = []
  doc = panflute.run_filter(action, doc=doc)

  for image in doc.header:
    print(image)
```

{% endtab %}
{% endtabs %}

{% tabs %}
{% tab title='markdown' %}

* \#n: headers
* \> backquote
* \* / + / -: unordered list (add spaces to make sublist)
* \1. ...: ordered list
* \*Italic\*: *Italic*
* \*\*Bold\*\*: **Bold**
* \~\~ line through~~: ~~line through~~

```sh
# Latex
$$
\int_{-\infty}^\infty g(x) dx
$$
```

{% endtab %}
{% endtabs %}

### Pandoc

* the most comprehensive one to our knowledge
* general markup converter using Haskell library

* pandoc CLI
  * mystyles.css input.md -o output.pdf
  * -t `format`: (ex: html, markdown, beamer)
  * --css mystyles.css: Add custom css
  * -o output.pdf: Set output file
  * --pdfengine `engine`: (ex: html, pdflatex, lualatex, xelatex, latexmk, tectonic, wkhtmltopdf, weasyprint, prince, context)

{% tabs %}
{% tab title='presentation.sh' %}

```sh
pandoc -t pdflatext input.md -o output.pdf
```

```css
/* main.css */
h2 {
  break-before: page;
}
```

{% endtab %}
{% endtabs %}

### Structure

* Here's a simple footnote,[^1] and here's a longer one.[^bignote]

* [^1]: This is the first footnote
* [^bignote]: Here's one with multiple paragraphs and code
  * Indent paragraphs to include them in the footnote
  * `{ my code }`
  * Add as many paragraphs as you like

### Figure

> Table

* \<br \/\>: line break in table

{% tabs %}
{% tab title='tool.md' %}

```txt
|     | name | score | rank |
| --- | ---- | ----- | ---- |
| A   |      |       |      |
| B   |      |       |      |
```

{% endtab %}
{% endtabs %}

> Image

* Images: \!\[test\]\(a.png\)
* \!\[test\](a.png=192x102): Set size (Not supported in gitbook)
* \<img src="a.png" width="640" height=360 /\>: set size

### Presentation

* \<div style="page-break-after: always;"></div\>: page break

```md
<!-- 1. presentation -->
% Title of talk
% Speaker Name
% Date of Talk

# Title of Slide 1

* Item of list

$$ \sum..{a,b} + x y \infty $$
```
