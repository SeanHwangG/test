# Web

> Term

* API (Application Programming Interface): a software intermediary that enables two apps to communicate with each other
  * All Web services are APIs but not all APIs are Web services
  * All Web services need a network to operate while APIs don’t need a network for operation
  * First estimate your usage and understand how that will impact the overall cost of the offering
  * Many protocols are now available to be used in API testing (ex JMS, REST, HTTP, UDDI and SOAP)
* Cross-site request forgeries (csrf): POST, PUT, PATCH, DELETE request for secret session value that malicious app
  * a type of malicious exploit whereby unauthorized commands are performed on behalf of an authenticated user
* HTML: Hyper Text Markup Language where W3 Consortium is main international standards organization
  * request and response protocol, media independent protocol, stateless protocol
* Framework: piece of code that dictates the architecture of your project and aids in programs
* Library: pre-written JavaScript which allows for easier development of JavaScript-based applications
* Websocket: two way communication between the clients and the servers
  * Four main events: Open / Close / Error / Message
* Same Origin Policy: When using XMLHttpRequest or Fetch API → local files origin is null
* SPA: Single Page Application ([ex] React, Vue)
  * [+] Only single server request mode for initial HTML page, everything else is handled by SPA
  * [-] SEO friendly
* Server Side Rendered: pages rendered on the server after every request, sources data & uses templates
  * [+] SEO, easy to update
  * [-] Slow, Fresh request needs to be made for every page
* Service worker: script that your browser runs in the background, separate from a web page
  * Programmable network proxy, allowing you to control how network requests from your page are handled
  * Can't access DOM directly, communicate with the pages it controls by responding to messages sent via postMessage interface
  * opening door to features that don't need a web page or user interaction
  * [ex] push notifications, background sync
* Static website: Uses static HTML, js, css
  * [+] SEO
  * [-] Fresh request to server for every page, hard to maintain
* Static site generator: build HTML combining Templates, Component, Data during build time ([ex] nextjs, gatsby)
  * [+] SEO, easy to update, speed
* URI (Uniform Resource Identifier): string designed for identification of resources and extensibility via URI scheme
* xss (Cross Site Scripting): users executed malicious scripts (payloads) unintentionally by clicking on untrusted links
  * these scripts pass cookies information to attackers

{% tabs %}
{% tab title='javascript' %}

* interpreted, dynamic typing, prototype-based programming language
* Speed Optimization
  * [Google page speed](https://developers.google.com/speed/pagespeed/insights/)
  * [image optimization](https://tinyjpg.com)

* ES5
  * developed in 2009
  * Fully supported in all modern browsers

* ES6: ECMAScript 2015
  * Internet Explorer does not support ECMAScript 2015
  * let and const, default parameter values, Array.find(), Array.findIndex()

> Terms

* React
  * Create-react-app → Need node > 6
  * Webpack development environment → run live server and a development environment
  * babel → manage your code, make it write a version compatible with older browsers

> React Terms

* JSX: React DOM escapes any values embedded in JSX before rendering them → Prevents Injection Attacks
  * Babel compiles JSX down to React.createElement() calls

* Element: React elements are immutable → can’t change its children or attributes
  * ReactDOM.render() every second from a setInterval() callback → usually called once

* Key: special string attribute you need to include when creating lists of elements
  * key only has to be unique among its siblings, not globally unique

* Props: props are read only

```js
function NumberList(props) {
  return (
    <ul>{props.numbers.map((number) => <li>{number}</li>);}</ul>
  );
}

const numbers = [1, 2, 3, 4, 5];
ReactDOM.render(
  <NumberList numbers={numbers} />,
  document.getElementById('root')
);

const uuid = require('uuid/v1');
const todoItems = todos.map((todo, index) =>
  <li key={uuid()}> {todo.text} </li>
);
```

> Maximum update depth exceeded error

```jsx
// pass function or use arrow function instead of calling it
{<td><span onClick={this.toggle()}>Details</span></td>}
{<td><span onClick={this.toggle}>Details</span></td>}
```

> Refused to apply style from 'https://cdn.jsdelivr.net/npm/instantsearch.js'
  because its MIME type ('application/javascript') is'nt supported stylesheet MIME type, and strict MIME checking is enabled

```html
<link rel="stylesheet" href="styles.css"\>
```

> Uncaught SyntaxError: Cannot use import statement outside a module`

```html
<script type="module" src="../src/main.js"></script>
```

> (node:32660) UnhandledPromiseRejectionWarning: Unhandled promise rejection. This error originated either by throwing
  inside of an async function without a catch block, or by rejecting a promise which was not handled with .catch().
  To terminate the node process on unhandled promise rejection, use the CLI flag `--unhandled-rejections=strict`
  ([See also](https://nodejs.org/api/cli.html#cli_unhandled_rejections_mode)). (rejection id: 1)
  (node:32660) [DEP0018] DeprecationWarning: Unhandled promise rejections are deprecated.
  In the future, promise rejections that are not handled will terminate the Node.js process with a non-zero exit code.

* Do not throw again in catch which is uncaught
* Do not trust auto import, from sequelize.types -> from sequelize
* await async function that throws an error

{% endtab %}
{% endtabs %}

## Crawling

* robot.txt: give rules on how site can be crawled
  * links to sitemap

{% tabs %}
{% tab title='python' %}

* bs4
  * name: tagname
  * text, attrs: inside text, attribute object
  * next / previous_elements: next / previous tags generator
  * next / previous_siblings: next sibling tags generator
  * original_encoding
  * bs4.element.Tag
    * string
    * text
    * clear(): removes the contents of a tag:
    * decompose(): remove tag
    * extract(): hide element
    * find_all(tag, href=None, limit=None) → [Tags]: find all matching tags
    * find("span"): find tags inside
    * get_text():
    * insert(pos, tag): insert tag to position
    * insert_before() / after(): immediately before
    * prettify()
    * wrap(soup.new_tag("b")): wrap around new tags
    * new_button = soup.new_tag('a')
    * new_button.attrs["onclick"] = "toggle()"
    * new_button.append('This is a new button!')

* selenium.WebElement
  * tag_name
  * text
  * parent
  * find_element_by_css_selector()
    * .id,.name: get multiple selctor
  * get_property(`property`): get property of tag (ex: href)

* urllib
  * Request
    * urllib2.Request("www.example.com")
    * add_header('Referer', 'http://www.python.org/')
    * urlopen(url): string / Request object.  For HTTP, returns http.client.HTTPResponse object
  * parse
    * unquote(str): decode urlencoded bytes
  * HTTPResponse
    * content = resp.read()

```py
# 1. Download Coco dataset
import sys, getopt
import fire
import json
import requests

def download_factory(all = False, *, coco2014 = None, coco2017 = None):
  if all or coco2014:
    url = "http://images.cocodataset.org/annotations/annotations_trainval2014.zip"
    download(url)

  if all or coco2017:
    url = "http://images.cocodataset.org/annotations/annotations_trainval2017.zip"
    download(url)

def download(url):
  response = requests.get(url, stream=True)
  total_bytes = int(response.headers.get('content-length', 0))
  with open('test.dat', 'wb') as file:
    with tqdm(total=total_bytes / (32*1024.0), unit='B', unit_scale=True, unit_divisor=1024) as pbar:
      for data in response.iter_content(1024):
        pbar.update(len(data))
        file.write(data)
```

> Error DevToolsActivePort file doesn't exist

* chrome_options.add_argument("--single-process")

{% endtab %}
{% endtabs %}

## DOM

{% tabs %}
{% tab title='javascript' %}

* children
* classList: list of class
* .add / remove('MyClass'): add / remove to class

* getElementById(id): get all elements with id
* getElementByClassName(cls): get all elements with className

* querySelector
* 'tag.class#id': using query selector
* '.class1, .class2': class1 or class2
* '.class1.class2': class1 and class2
* [style="display: none;"]: display is

* setAttribute(name, value)

```js
// 1. toggle division
<script>
function toggle(id){
  for (let element of document.getElementsByClassName("hideable")){
   element.style.display="none";
  }
  document.getElementById(id).style.display = "block";
}
</script>
<a href="#" onclick="toggle('div1');">div1</a>
<a href="#" onclick="toggle('div2');">div2</a>
<a href="#" onclick="toggle('div3');">div3</a>

<div class="hideable" id="div1" style="display:block">Div 1</div>
<div class="hideable" id="div2" style="display:none">Div 2</div>
<div class="hideable" id="div3" style="display:none">Div 3</div>

// 2. Add foods
const foods = ["pizza"];

function getFoods() {
  setTimeout(() => {
    let output = "";
    foods.forEach(food => {
      output += `<li>${food}</li>`;
    });
    document.body.innerHTML = output;
  }, 1000);
}

function addFood(food) {
  setTimeout(() => {
    foods.push(food);
    resolve();
  }, 1000);
}

async function init() {
  await addFood("hotdog");
  getFoods();
}

init();

// 3. Hide all
.querySelectorAll('.hideable').forEach(function(el) {
   el.style.display = 'none';
});
```

{% endtab %}
{% endtabs %}

### Page redirection

{% tabs %}
{% tab title='markdown' %}

```md
<!-- 1. .gitbook.yaml -->
redirects:
  help/contact: ./contact.md
  help: ./support.md
```

{% endtab %}
{% endtabs %}

## Structure

{% tabs %}
{% tab title='javascript' %}

![HTML](images/20210210_182233.png)

![static vs relative](images/20210219_215909.png)

![html structure](images/20210218_233924.png)

* Structure css
  * vh: scaled accordingly when the initial containing block is changed

* Structure Tags
  * html: { display: block; }
  * style: put css  { display: none; }
  * div: defines a division or a section in an HTML document
  * span: wrap small portions of text, images
  * article: make sense on its own, possible to read it independently from the rest of the web site
  * div: Content Division element, the generic container for flow content
  * span: a section in a document
  * header: a header for a document or section
  * footer: { display: block; }
  * main: the main content of a document
  * body: display: block; margin: 8px; }
  * data: Links the given content with a machine-readable translation
  * details: additional details that the user can view or hide
  * dialog: a dialog box or window
  * summary: a visible heading for a `<details>` element

```js
<style>
  html, body { height: 100%; margin: 0; }
  .screen { height: 100%; background-color: black; display: flex; }
  .left { background-color: red; width: 300px; }
  .right { background-color: blue; width: 100%; }
  .right-top { background-color: green; height: 200px; }
  .right-bottom { background-color: yellow; margin-top: 50px; height: 100%; }
</style>
<div class="screen">
  <div class="left"></div>
  <div class="right">
    <div class="right-top"></div>
    <div class="right-bottom"></div>
  </div>
</div>
```

{% endtab %}
{% endtabs %}

## Window

{% tabs %}
{% tab title='javascript' %}

* href: entire URL
* protocol: protocol of the URL
* host: hostname and port of the URL
* hostname: hostname of the URL
* port: port number the server uses for the URL
* pathname: path name of the URL
* search: query portion of the URL
* hash: anchor portion of the URL

```js
class LoggingButton extends React.Component {
  handleClick = () => { console.log('this is:', this); }
  render() { return (<button onClick={this.handleClick}> CLIck me </button>); }
}
```

{% endtab %}
{% endtabs %}

```html
<!-- 1. Add script -->
<body>
  <script src="index.js"> </script>
</body>
```

## CSS

* describes how HTML elements should be displayed
* id: must start with letters only have one id
* Pseudo-Elements: style specified parts of an element. (ex, Style first letter, or line, of an element)

```js
<link rel="stylesheet" type="text/css" href="theme.css">
```

* Rules given in later classes (or which are more specific) override

```js
a.abc, a.xyz {     /* apply to multiple css */
  width: 100px;
  height: 100px;
}
```

* display
  * none: completely removed
  * block: as a block element `<p>`. starts on a new line, takes up whole width
  * inline: as an inline element `<span>`. height, width properties have no effect
  * list-item: Let the element behave like a `<li>` element
  * inline-table: The element is displayed as an inline-level table
  * contents: remove container, make childs children of element next level up in DOM
  * flex / grid: element as a block-level flex / grid container
  * inline-flex / grid: Displays an element as an inline-level flex / grid container

![display](images/20210219_220013.png)

* Flex

![flex](images/20210219_220045.png)

* parent

```css
display: flex;
justify-content: center;

flex-direction         #  how flex items are placed in flex container defining main axis and direction
flex-direction: row;
```

* Selector
  * \*: all elements
  * div: all div tags
  * div, p: all divs and paragraphs
  * div p: paragraphs inside divs
  * .classname: all elements with class
  * \#idname: element with ID
  * div.classname: divs with certain classname
  * div#idname: div with certain ID
  * \#idname *: all elements inside #idname
  * [attribute="value"]: used to select elements with a specified attribute
  * [attribute~="value"]: used to select elements with an attribute value containing a specified word

* Combinators: something that explains the relationship between the selectors
  * div p: all elements that are descendants of a specified element
  * div > p: all p tags, one level deep in div
  * div + p: p tags immediately after div
  * div ~ p: p tags preceded by div

* unit
  * cm, mm, in: centimeters / millimeters / inches (1in = 96px = 2.54cm)
  * p: relative to the viewing device. For high res, 1px = 1+ device pixel
  * %: Relative to the parent element
  * em: Relative to font-size of element (2em = x2 of current font)
  * ex: Relative to x-height of current font (rarely used)
  * ch: Relative to width of the "0" (zero)
  * rem: Relative to font-size of the root element
  * pt, pc: points (1pt = 1/72 of 1in), picas (1pc = 12 pt)
  * vw, vh: Relative to 1% of the width / height of the viewport*
  * vmin, vmax: Relative to 1% of viewport* smaller / larger  dimension

* z-index: only works on positioned elements (position: absolute, relative, fixed, sticky)
  * z-index: auto|number|initial|inherit;
  * number: stack order of the element. Negative numbers are allowed
  * auto (default): stack order equal to its parents

* visibility
  * visible: visible, defaul>
  * hidden: hidden (but still takes up space)
  * collapse: Only for `<tr>`, `<tbody>`, `<col>`, `<colgroup>`. removes a row or column

> Position

![position](images/20210219_221142.png)

* reltive vs fixed
  * px for constant spacing rem for text size
  * elative: positioned relative to its normal position
  * bsolute: positioned absolutely to its first positioned parent
  * ixed: positioned related to the browser window
  * ticky: positioned based on the user's scroll position
  * min-width: content is smaller than the minimum width, the minimum width will be applied

* margin

```js
default 0
margin: one / two / three / four  // tdlr / td, rl / t, rl, d / t, r, b, l
```

{% tabs %}
{% tab title='javascript' %}

```js
// 1. Check hidden
child.offsetWidth > 0 && child.offsetHeight > 0 // also check if parent is hidden
object.style['display'] != 'none'               // only checks the element
```

{% endtab %}
{% tab title='google' %}

* stylish: Customize css for any website

```css
/* 1. Stylish for gitbook */
/* Increase Center */
.reset-3c756112--pageContainer-544d6e9c {
  max-width: 1800px;
}

/* Hide left navigation */
.reset-3c756112--body-324a5898 {
  margin: 0;
}

.reset-3c756112--contentNavigation-dd3370a4 {
  min-width: 0px;
}

/* Hide except edit on github */
.reset-3c756112--menuItem-aa02f6ec--menuItemLight-757d5235--menuItemInline-173bdf97--pageSideMenuItem-22949732:
not(:first-child) {
  display: none;
}

/* reduce right navigation */
.reset-3c756112--contentNavigation-dd3370a4 {
  padding-left: 0;
  width: calc((100% - 1448px) / 5);
}

.reset-3c756112--pageSide-ad9fed26 {
  width: 180px;
}

/* Hide admin option */
.reset-3c756112--sidebarNav-1270f224 {
  display: none;
}

.reset-3c756112--body-324a5898 {
  width: 100%;
}
```

{% endtab %}
{% endtabs %}

## Text

{% tabs %}
{% tab title='javascript' %}

* css
  * enter:Centers the text
  * ustify:Stretches lines so that each line has equal width (ex. newspapers, magazines)
  * text-align: Align text
  * eft: Aligns the text to the left / right
  * ext: controls the capitalization of text
  * verflow: [ex] normal | anywhere | break-all | break-word | keep-all
  * ext: [ex] none | line-through | overline | underline | initial | inherit

![align](images/20210219_220216.png)
![word wrap](images/20210219_220237.png)

* tags
  * h1: {display: block; font-size: 2em; margin: 0.67em 0; font-weight: bold;}
  * h2: {display: block; font-size: 1.5em; margin: 0.83em 0; font-weight: bold;}
  * h3: {display: block; font-size: 1.17em; margin: 1em 0; font-weight: bold;}
  * h4: {display: block; margin-top: 1.33em 0; font-weight: bold;}
  * h5: {display: block; font-size: .83em; margin: 1.67em 0; font-weight: bold;}
  * h6: {display: block; font-size: .67em; margin: 2.33em 0; font-weight: bold;}
  * hr: {display: block; margin: 0.5em auto; border-style: inset; border-width: 1px; }
  * p: {display: block; margin-top: 1em 0}
  * pre: preformatted text
  * abbr: an abbreviation or an acronym
  * address: contact information address, { display: block; font-style: italic; }
  * b: bold text, {font-weight: bold;}
  * br: A line break in text (carriage-return)
  * del: text that has been deleted from a document
  * em: emphasized text
  * mark: marked/highlighted text
  * q:a short quotation
  * strong: important text
  * sub: subscripted text
  * sup: superscripted text
  * template: a template
  * time: a date/time
  * u:text that should be stylistically different from normal text
  * var: a variable

```js
// 1. align text
<style>
#parent { text-align:center; background-color:blue; height:400px; width:600px; }
.block { height:100px; width:200px; text-align:left; }
.center { margin:auto; background-color:green; }
.left { margin:auto auto auto 0; background-color:red; }
.right { margin:auto 0 auto auto; background-color:yellow; }
</style>
<div id="parent">
    <div id="child1" class="block center"> a block to align center and with text aligned left </div>
    <div id="child2" class="block left"> a block to align left and with text aligned left </div>
    <div id="child3" class="block right"> a block to align right and with text aligned left </div>
</div>
```

{% endtab %}
{% tab title='markdown' %}

* \~\~: ~~strikethrough~~

{% endtab %}
{% endtabs %}

### Text Scroll

{% tabs %}
{% tab title='javascript' %}

* overflow: specifies what should happen if content overflows an element's box
  * auto: clipped, a scroll-bar is added when content doesn’t fit
  * hidden: clipped, rest of content will be invisible
  * scroll: clipped, scroll will always show scrollbar even if content fits
  * initial / inherit: default / inherit from parent
  * overflow: visible|hidden|scroll|auto|initial|inherit;
  * visible (default): is not clipped. It renders outside the element's box

![overflow](images/20210219_221044.png)

{% endtab %}
{% endtabs %}

### Web Link

{% tabs %}
{% tab title='javascript' %}

* a:link: a normal, unvisited link
* a:visited: a link the user has visited
* a:hover: a link when the user mouses over it
* a:active: a link the moment it is clicked
* color: red / #00ff00
* letter-spacing: 3px
* line-height: 0.8
* padding: 10px 20px
* text-align: center
* text-decoration: line-through / overline / underline
* text-transform: uppercase / undercase / capitalize
* text-indent: 50px

* Link tags
* a: onclick
  * a:link: { color: (internal value); text-decoration: underline; cursor: auto; }
* download: Specifies that the target will be downloaded when a user clicks on the hyperlink
* href: Specifies the URL of the page the link goes to
* target: Specifies where to open the linked document
* script
  * async / defer: script is executed asynchronously /page has finished parsing (only external)
  * crossorigin: Sets request mode to an HTTP CORS Request (anonymous / use-credentials)
  * integrity filehash: browser checks script to ensure that code is not manipulated
  * nomodule T/F       // shouldn’t be executed in browsers supporting ES2015 modules
  * referrerpolicy     // Specifies which referrer information to send when fetching a script
  * src URL            // Specifies the URL of an external script file
  * type scripttype    // Specifies the media type of the script

{% endtab %}
{% endtabs %}

## Node

* Node.js single thread -> PM2 for multithreading
* uses Chrome's V8 engine used in Chrome browser to compile javascript functions to machine code

> Node CLI

* -v: Check version

```js
var stuff = require('./test.js');
document.write(stuff.counter(['df']));


var counter = function(arr) {
    return 'there are' + arr.length;
}
module.exports = {
    counter: counter;
};
module.exports.counter = counter
```

> Cannot find module './components/Navigation' or its corresponding type declarations

```ts
import HomeComponent from "components/HomeComponent";
import HomeComponent from "./components/HomeComponent";
```

> ReferenceError: algoliasearch is not defined

* add [cdn](https://cdnjs.com/libraries/algoliasearch)

> Error in loader, shutting down process Invalid default value for 'category'

* defaultValue: "None" not specified in ENUM values

> SequelizeDatabaseError: Unknown column 'Order.userID' in 'where clause'

* userId not present in Order, update db if udpated

> SequelizeDatabaseError: Column 'shippingFee' cannot be null

* update Table, migrate if not development server

> sequelize message: Column createdAt in where clause is ambiguous

* models.sequelize.col('User.createdAt'))

* Cluster

```js
var cluster = require('cluster'),
    app = require('./express-app');

var workers = {},
    count = require('os').cpus().length;

function spawn(){
  var worker = cluster.fork();
  workers[worker.pid] = worker;
  return worker;
}

if (cluster.isMaster) {
  for (var i = 0; i < count; i++) {
    spawn();
  }
  cluster.on('death', function(worker) {
    console.log('worker ' + worker.pid + ' died. spawning a new process...');
    delete workers[worker.pid];
    spawn();
  });
} else {
  app.listen(process.env.PORT || 5000);
}
```

* config

```js
// default.json
const require(‘config’);
const db = config.get("mongoURI")
```

* Events

```js
const EventEmitter = require('events');
const eventEmitter = new EventEmitter();

eventEmitter.on('tutorial', (num1, num2)=>{
  console.log(num1 + num2);
});

eventEmitter.emit('tutorial', 1,2)

class Person extends EventEmitter{
  constructor(name){
    super();
    this._name =  name;
  }
  get name(){
    return this._name;
  }
}

let pedro = new Person('Pedro');
let christina = new Person('Christina');
christina.on('name',()=>{
  console.log('my name is' + christina.name);
});
pedro.on('name', ()=>{
  console.log('my name is' + pedro.name);
});

pedro.emit('name');
christina.emit('name');
```

* Nodemon: constantly update UI
* markdownlint-cli2
  * markdownlint-cli2 "**/*.md"

* elastic beanstalk
  * eb init --platform node.js --region us-east-2

* Input Type
* Request body: almost any kind of HTTP request
  * body editor is divided into 4 areas and has different controls depending on the body type
* form-data: simulates filling a form on a website
  * can attach files to a key as well
* urlencoded (default)
* key/value pairs and Postman will encode the keys and values properly
* raw: doesn't touch string entered in raw editor except replacing environment variables
* binary: allows you to send things which you can not enter in Postman
  * image, audio or video files, text files

* paypal: request, backend, create payment with id, transaction successful, capture ID

* cheerio: parses markup and provides an API for traversing/manipulating the resulting data structure
  * It does not interpret the result as a web browser does
  * Specifically, it does not produce a visual rendering, apply CSS, load external resources, or execute JavaScript

## Component

{% tabs %}
{% tab title='javascript' %}

> Term

* Class Component: functions accept inputs (props) and return elements
  * must have only one div
  * starts with upper-cass
* Functional: Hook allows you to use functional component
  * Only call Hooks at the top level. Don’t call Hooks inside loops, conditions, or nested functions
  * Only call Hooks from React function components. Don’t call Hooks from regular JavaScript functions

```ts
// 1. class component
class Movie extends React.Component{
  constructor(props) {
    super(props);
    this.state = {date: new Date()};
  }
  render () {
    return (<div>
              <h1> {this.props.title} </h1>
              <h2> {this.props.genre} </h2>
           </div>)
  }
}

// 2. Functional component
const [count, setCount] = useState(0);

/* Similar to componentDidMount and componentDidUpdate: */
useEffect(() => {
  /* Update the document title using the browser API */
  document.title = `You clicked ${count} times`;
});

return (
  <div>
    <p>You clicked {count} times</p>
    <button onClick={() => setCount(count + 1)}>
      Click me
    </button>
  </div>
);
```

{% endtab %}
{% endtabs %}

## Context

* provides a way to pass data through the component tree without having to pass props down manually at every level

```ts
// Create a context for the current theme (with "light" as the default), without explicitly threading it through every component.
const ThemeContext = React.createContext('light');

class App extends React.Component {
  render() {
    // Use a Provider to pass the current theme to the tree even far below. ([ex] passing "dark" as the current value)
    return (
      <ThemeContext.Provider value="dark"> <Toolbar />
      </ThemeContext.Provider>
    );
  }
}

// A component in the middle doesn't have to pass the theme down explicitly anymore.
function Toolbar() {
  return (
    <div> <ThemedButton /> </div>
  );
}

class ThemedButton extends React.Component {
  // Assign a contextType to read current theme context, find closest theme Provider above and use its value ([ex] dark)
  static contextType = ThemeContext;
  render() { return <Button theme={this.context} />; }
}
```

## Dom

* Update real DOM for only those objects which are changed in Virtual DOM
* To allow React to create a Virtual DOM, you will need React’s Components
* Replace class attribute name to className, because it is reserved in javascript

```js
// tick_update.js
function tick() {
  const element = (<div>
    <h1>Hello, world!</h1>
    <h2>It is {new Date().toLocaleTimeString()}.</h2></div>
  );
  ReactDOM.render(element, document.getElementById('root'));
}
setInterval(tick, 1000);

import {BrowserRouter as Router, Switch, Route} from 'react-router-dom'
export default class App extends Component {
  render() {
    return (<Router>
        <div>
          <Nav />
          <Switch>
            <Route exact path="/" component={Home} />
            <Route exact path="/about" component={About} />
            <Route exact path="/shop" component={Shop} />
          </Switch>
        </div>
      </Router>
    );
  }
}
```

## Router

{% tabs %}
{% tab title='javascript' %}

```js
// Router
const express = require("express"); // Simple 3000 hosting
const app = express();              // set up view engine
app.set("view engine", "ejs");
app.get("/", (req, res) => {res.render("home");}); // create home route

app.listen(3000, () => {
  console.log("app now listening for requests on port 3000");
});
```

> Error

* (16,8): error TS2322: Type '{ children: Element; }' is not assignable to type 'IntrinsicAttributes & ...
  Type '{ children: Element; }' is not assignable to type 'Readonly\<RouterProps\>'.
  Property 'history' is missing in type '{ children: Element; }'.

```js
// import { Router } from 'react-router-dom';
import { BrowserRouter as Router } from 'react-router-dom';
```

{% endtab %}
{% tab title='python' %}

* rest_framework.renderers
  * JSONRenderer
    * render(`serializer`.data)
  * LimitOffsetPagination

```py
from .models import Article
from .serializers import ArticleSerializer
from rest_framework import viewsets
from rest_framework.response import Response
from rest_framework import status
from django.shortcuts import get_object_or_404
from django.urls import path, include
from .views import ArticleViewSet
from rest_framework.routers import DefaultRouter


# 1. views.py
class ArticleViewSet(viewsets.ViewSet):
  def list(self, request):
    articles = Article.objects.all()
    serializer = ArticleSerializer(articles, many=True)
    return Response(serializer.data)

  def create(self, request):
    serializer = ArticleSerializer(data=request.data)
    if serializer.is_valid():
      serializer.save()
      return Response(serializer.data, status=status.HTTP_201_CREATED)
    return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

  def retrieve(self, request, pk=None):
    queryset = Article.objects.all()
    article = get_object_or_404(queryset, pk=pk)
    serializer = ArticleSerializer(article)
    return Response(serializer.data)

# 2. urls.py
router = DefaultRouter()
router.register('article', ArticleViewSet, basename='article')

urlpatterns = [
  path('viewset/', include(router.urls))
]
```

{% endtab %}
{% endtabs %}

## State

{% tabs %}
{% tab title='javascript' %}

* Read-only
* share state by moving to closest common ancestor of the components that need it → lifting state up
* State is reserved only for interactivity, that is, data that changes over time
* [`state`, `setter`] useState(`initial`): create react state with setter

```js
// 1. Sample Constructor
constructor(props) {
  super(props);
  this.state = {
    brand: "Ford",
    model: "Mustang",
    color: "red",
    year: 1964
  };
}

state = {
  brand: "Ford",
  model: "Mustang",
  color: "red",
  year: 1964
};

/* Put into HTML */
<div>
  {this.state.todos.map(todo => (
    <Todo key={todo.key} content={todo.content} />
  ))}
</div>

// 2. CRUD
this.setState(prev => ({  v: [...prev.v, added]}))
this.setState(prev => ({ v: prev.v.filter(n => n !== e.target.value) }));
this.setState({ v: update(this.state.v, {1: {name: {$set: 'updated field name'}}})})

// 3. Mobx Domain state
import { makeAutoObservable, autorun, runInAction } from "mobx"
import uuid from "node-uuid"

export class TodoStore {
  authorStore
  transportLayer
  todos = []
  isLoading = true

  constructor(transportLayer, authorStore) {
    makeAutoObservable(this)
    this.authorStore = authorStore // Store that can resolve authors.
    this.transportLayer = transportLayer // Thing that can make server requests.
    this.transportLayer.onReceiveTodoUpdate(updatedTodo => this.updateTodoFromServer(updatedTodo))
    this.loadTodos()
  }

  // Fetches all Todos from the server.
  loadTodos() {
    this.isLoading = true
    this.transportLayer.fetchTodos().then(fetchedTodos => {
      runInAction(() => {
        fetchedTodos.forEach(json => this.updateTodoFromServer(json))
        this.isLoading = false
      })
    })
  }

  // Update a Todo with information from the server. Guarantees a Todo only exists once.
  // Might either construct a new Todo, update an existing one, or remove a Todo if it has been deleted on the server.
  updateTodoFromServer(json) {
    let todo = this.todos.find(todo => todo.id === json.id)
    if (!todo) {
      todo = new Todo(this, json.id)
      this.todos.push(todo)
    }
    if (json.isDeleted) this.removeTodo(todo)
    else todo.updateFromJson(json)
  }

  // Creates a fresh Todo on the client and the server.
  createTodo() {
    const todo = new Todo(this)
    this.todos.push(todo)
    return todo
  }

  // A Todo was somehow deleted, clean it from the client memory.
  removeTodo(todo) {
    this.todos.splice(this.todos.indexOf(todo), 1)
    todo.dispose()
  }
}

// Domain object Todo.
export class Todo {
  id = null  // Unique id of this Todo, immutable.
  completed = false
  task = ""
  author = null  // Reference to an Author object (from the authorStore).
  store = null
  autoSave = true  // Indicator for submitting changes in this Todo to the server.
  saveHandler = null  // Disposer of the side effect auto-saving this Todo (dispose).

  constructor(store, id = uuid.v4()) {
    makeAutoObservable(this, { id: false, store: false, autoSave: false, saveHandler: false, dispose: false })
    this.store = store
    this.id = id

    this.saveHandler = reaction(
      () => this.asJson, // Observe everything that is used in the JSON.
      json => {
        // If autoSave is true, send JSON to the server.
        if (this.autoSave) this.store.transportLayer.saveTodo(json)
      }
    )
  }

  // Remove this Todo from the client and the server.
  delete() {
    this.store.transportLayer.deleteTodo(this.id)
    this.store.removeTodo(this)
  }

  get asJson() {
    return { id: this.id, completed: this.completed, task: this.task, authorId: this.author ? this.author.id : null }
  }

  // Update this Todo with information from the server.
  updateFromJson(json) {
    this.autoSave = false // Prevent sending of our changes back to the server.
    this.completed = json.completed
    this.task = json.task
    this.author = this.store.authorStore.resolveAuthor(json.authorId)
    this.autoSave = true
  }

  dispose() {
    this.saveHandler()  // Clean up the observer.
  }
}

// 4. UI State
import { makeAutoObservable, observable, computed, asStructure } from "mobx"

export class UiState {
  language = "en_US"
  pendingRequestCount = 0

  // .struct makes sure observer won't be signaled unless dimensions object changed in a deepEqual manner.
  windowDimensions = {
    width: window.innerWidth,
    height: window.innerHeight
  }

  constructor() {
    makeAutoObservable(this, { windowDimensions: observable.struct })
    window.onresize = () => { this.windowDimensions = getWindowDimensions() }
  }

  get appIsInSync() { return this.pendingRequestCount === 0 }
}
```

{% endtab %}
{% endtabs %}

{% repo 'button-counter' %}

### State Management

{% tabs %}
{% tab title='javascript' %}

![Mobx](images/20210615_211557.png)

* [Mobx tutorial](https://mobxjs.github.io/mobx/getting-started.html)

* Store: similar to controller in MVC pattern
  * move logic and state out of components into testable unit
* domain state: store the data your application is all about
  * should be expressed using its own class or constructor function
* UI state: often very specific for your application, but usually very simple without logic
  * loosely coupled pieces of information about the UI
  * [ex] Session information, how far your application loaded, data not stored in the backend, data affects the UI globally

* Mobx react
  * observe: intercept changes after they have been made
  * intercept: detect and modify mutations before they are applied to the observable (validating, normalizing or cancelling)
  * observer(): HoC automatically subscribes React components to any observables that are used during rendering
  * useObserver(): Low level implementation used internally by observer HOC and Observer component
    * allows you to use an observer like behaviour

```ts
import { observer } from "mobx-react-lite"

const myTimer = new Timer() // See the Timer definition above.
const TimerView = observer(({ timer }) => <span>Seconds passed: {timer.secondsPassed}</span>)

// Pass myTimer as a prop.
ReactDOM.render(<TimerView timer={myTimer} />, document.body)
```

{% endtab %}
{% endtabs %}

{% repo 'mobx-react' %}

## Nav

{% tabs %}
{% tab title='javascript' %}

```jsx
import React, { Component } from "react";
import ReactDOM from "react-dom";
import {
  BrowserRouter as Router,
  Link,
  Switch,
  useLocation
} from "react-router-dom";


// 1. Router nav bar
export default class Nav extends Component {
  render() {
    const navStyle = { color: "white" };
    return (
      <nav>
        <h3>logo</h3>
        <ul className="nav-links">
          <Link style={navStyle} to="/about">
            <li>About</li>
          </Link>
        </ul>
      </nav>
    );
  }
}

// 2. useParams (similar to dynamic segments matching in other frameworks like Rails and Express)
// Params are placeholders in the URL that begin with a colon, like the `:id` param defined in the route in this example
export default function ParamsExample() {
  return (
    <Router>
      <div>
        <h2>Accounts</h2>

        <ul>
          <li>
            <Link to="/netflix">Netflix</Link>
          </li>
          <li>
            <Link to="/zillow-group">Zillow Group</Link>
          </li>
          <li>
            <Link to="/yahoo">Yahoo</Link>
          </li>
          <li>
            <Link to="/modus-create">Modus Create</Link>
          </li>
        </ul>

        <Switch>
          <Route path="/:id" children={<Child />} />
        </Switch>
      </div>
    </Router>
  );
}

function Child() {
  // use the `useParams` hook here to access the dynamic pieces of the URL.
  let { id } = useParams();

  return (
    <div>
      <h3>ID: {id}</h3>
    </div>
  );
}
```

{% endtab %}
{% endtabs %}

## Login

{% tabs %}
{% tab title='python' %}

```py
from flask_login import UserMixin
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from selenium import webdriver
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
from itertools import islice
from ..common import get_chrome_driver, PATH, logger
import json
import re
import os
import time

# 1. Flask login
class Member(UserMixin):
  def __init__(self, member_id, baekjoon_id, team_id, en_name, kr_name="", solved_problem_ids=None, is_admin=False, id=""):
    self.id = member_id  # for flask_login mixin
    self.member_id = member_id
    self.baekjoon_id = baekjoon_id
    self.team_id = team_id
    self.en_name = en_name
    self.kr_name = kr_name
    self.solved_problem_ids = set(solved_problem_ids) if solved_problem_ids else set()
    self.is_admin = is_admin

  def __repr__(self):
    return f"{self.id}"

  @staticmethod
  def update_baekjoon_solved(member):
    from ..database import remote_db
    driver = get_chrome_driver()
    try:
      driver.get(f"https://www.acmicpc.net/user/{member.baekjoon_id}")
      WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CLASS_NAME, 'panel-body')))
      member.solved_problem_ids = list(f'BJ_{prob_id}' for prob_id in driver.find_element_by_class_name('panel-body').text.split())
      remote_db.add("member", member)
      return True
    except Exception as e:
      logger.warning(f"{e}")
      logger.warning(f"{member}")
      return False
    finally:
      driver.quit()

  @staticmethod
  def update_all_baekjoon_solved(members, limit=10000):
    logger.debug(f"update_all_baekjoon_solved({members})")

    with ThreadPoolExecutor() as ex:
      futures = [ex.submit(Member.update_baekjoon_solved, member) for member in islice(members, limit)]
      return all(future.result() for future in as_completed(futures))
```

{% endtab %}
{% endtabs %}

## Heartbeat

* server periodically sends heartbeat message to a central monitoring server to show that it is still alive
* Without central server randomly choose a set of servers and send them a heartbeat message

{% tabs %}
{% tab title='djagno' %}

* health_check
  * pip install django-health-check

```py
# urls.py
urlpatterns = [
  url(r'^ht/', include('health_check.urls')),
]

# settings.py
INSTALLED_APPS = [
    # ...
    'health_check',                             # required
    'health_check.db',                          # stock Django health checkers
    'health_check.cache',
    'health_check.storage',
    'health_check.contrib.migrations',
    'health_check.contrib.celery',              # requires celery
    'health_check.contrib.celery_ping',         # requires celery
    'health_check.contrib.psutil',              # disk and memory utilization; requires psutil
    'health_check.contrib.s3boto3_storage',     # requires boto3 and S3BotoStorage backend
    'health_check.contrib.rabbitmq',            # requires RabbitMQ broker
    'health_check.contrib.redis',               # requires Redis broker
]

HEALTH_CHECK = {
    'DISK_USAGE_MAX': 90, # percent
    'MEMORY_MIN': 100,    # in MB
}
```

{% endtab %}
{% endtabs %}

## Icons

{% tabs %}
{% tab title='javascript' %}

* Material UI: Explicitly built for react
  * Flexibility, customize than bootstrap and semantic UI
  * Active development, hooks

{% endtab %}
{% endtabs %}

{% repo 'material' %}

## MIME

* two-part identifier for file formats and format contents transmitted on the Internet
* [ex] image/png, text/html, text/plain

> Reference

<https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types>

## Media

{% tabs %}
{% tab title='javascript' %}

* border: 1px solid #ddd
* border-radius: 4px
* opacity: 0.5

```js
background-image: url("photographer.jpg");
background-repeat: no-repeat, repeat
background-size: cover, contain
display: none;
position: absolute;
top, left: 25px;
z-index: 2;
padding        # space between border and content
margin         # space between border and surrounding content
```

{% endtab %}
{% endtabs %}

### Media Devices

{% tabs %}
{% tab title='javascript' %}

* navigator
  * mediaDevices
* MediaDevices
  * getUserMedia(): trigger permissions request
  * enumerateDevices(): return promise that resolves to MediaDevicesInfo[] that describe each known media device
* MediaDevicesInfo
* MediaStream

```js
/* 1. open the default microphone and camera */
const constraints = {
  'video': true,
  'audio': true
}
navigator.mediaDevices.getUserMedia(constraints)
  .then(stream => {
    console.log('Got MediaStream:', stream);
  })
  .catch(error => {
    console.error('Error accessing media devices.', error);
  });

/* 2. Listen for device change */
// Updates the select element with the provided set of cameras
function updateCameraList(cameras) {
  const listElement = document.querySelector('select#availableCameras');
  listElement.innerHTML = '';
  cameras.map(camera => {
      const cameraOption = document.createElement('option');
      cameraOption.label = camera.label;
      cameraOption.value = camera.deviceId;
  }).forEach(cameraOption => listElement.add(cameraOption));
}

// Fetch an array of devices of a certain type
async function getConnectedDevices(type) {
  const devices = await navigator.mediaDevices.enumerateDevices();
  return devices.filter(device => device.kind === type)
}

// Get the initial set of cameras connected
const videoCameras = getConnectedDevices('videoinput');
updateCameraList(videoCameras);

// Listen for changes to media devices and update the list accordingly
navigator.mediaDevices.addEventListener('devicechange', event => {
  const newCameraList = getConnectedDevices('video');
  updateCameraList(newCameraList);
});

async function getConnectedDevices(type) {
    const devices = await navigator.mediaDevices.enumerateDevices();
    return devices.filter(device => device.kind === type)
}

/* 3. Media Constraint */
// Open camera with at least minWidth and minHeight capabilities
async function openCamera(cameraId, minWidth, minHeight) {
  const constraints = {
    'audio': {'echoCancellation': true},
    'video': {
      'deviceId': cameraId,
      'width': {'min': minWidth},
      'height': {'min': minHeight}
      }
    }

  return await navigator.mediaDevices.getUserMedia(constraints);
}

const cameras = getConnectedDevices('videoinput');
if (cameras && cameras.length > 0) {
  // Open first available video camera with a resolution of 1280x720 pixels
  const stream = openCamera(cameras[0].deviceId, 1280, 720);
}

/* 4. Local Playback */
async function playVideoFromCamera() {
  try {
    const constraints = {'video': true, 'audio': true};
    const stream = await navigator.mediaDevices.getUserMedia(constraints);
    const videoElement = document.querySelector('video#localVideo');
    videoElement.srcObject = stream;
  } catch(error) {
    console.error('Error opening video camera.', error);
  }
}

<html>
<head><title>Local video playback</video></head>
<body>
    <video id="localVideo" autoplay playsinline controls="false"/>
</body>
</html>
```

{% endtab %}
{% endtabs %}

### Media Channel

![Web RTC](images/20210726_235130.png)

> Term

* webrtc: web real-time communications
* [NAT](../computer-science/security.md#NAT)
* Master: peer that initiates connection and is connected to signaling channel with the ability to discover
  * exchange media with any of the signaling channel's connected viewers
* Session Description Protocol (SDP): standard for describing multimedia content of connection
  * So that both peers can understand each other once the data is transferring
  * [ex] resolution, formats, codecs, encryption
* SDP Offer: SDP message sent by an agent which generates a session description in order to create or modify a session
  * Describes aspects of desired media communication
* SDP Answer: SDP message sent by an answerer in response to an offer received from an offerer
  * Answer indicates the aspects that are accepted ([ex] if all the audio and video streams in the offer are accepted)

{% tabs %}
{% tab title='javascript' %}

> Term

* Control pane: Responsible for creating and maintaining the Kinesis Video Streams with WebRTC signaling channels
* RTC PeerConnection: API for sending arbitrary data over
  * createDataChannel()
* Server: provides functionality required for proper connection of WebRTC sessions in cloud or self-hosting
  * Application servers: application and website hosting servers
  * Signaling server: a server that manages connections between devices
    * It's not concerned with media traffic itself, its focus is on signaling
    * enabling one user to find another in network, negotiating connection itself, resetting connection, and closing
* Topologies
  ![WebRTC](images/20210728_125822.png)
  * MCU: Multipoint Control Unit handles mixing of video / audio streams in a central server
    * controls a composited layout of that video for everyone, but introduces latency
    * [+] Client only requires basic webRTC Implementation
    * [+] Each participant has only one uplink downloink
    * [-] Since the MCU server makes decoding and encoding each participant’s media, it requires high processing power
  * SFU: Selective Forwarding Unit, each only connects to SFU but receives unique streams for each participant
    * [+] More powerful but complicated implementation, end2end encryption
    * [+] Requires less processing power than MCU, each participant has one uplink and four downlinks
    * [-] More complex design and implementation in server-side

```js
const messageBox = document.querySelector('#messageBox');
const sendButton = document.querySelector('#sendButton');
const peerConnection = new RTCPeerConnection(configuration);
const dataChannel = peerConnection.createDataChannel();

/* 1. Open and close events */
// Enable textarea and button when opened
dataChannel.addEventListener('open', event => {
  messageBox.disabled = false;
  messageBox.focus();
  sendButton.disabled = false;
});

// Disable input when closed
dataChannel.addEventListener('close', event => {
  messageBox.disabled = false;
  sendButton.disabled = false;
});

/* 2. Messages */
const messageBox = document.querySelector('#messageBox');
const sendButton = document.querySelector('#sendButton');

// Send a simple text message when we click the button
sendButton.addEventListener('click', event => {
  const message = messageBox.textContent;
  dataChannel.send(message);
})

const incomingMessages = document.querySelector('#incomingMessages');

const peerConnection = new RTCPeerConnection(configuration);
const dataChannel = peerConnection.createDataChannel();

// Append new messages to the box of incoming messages
dataChannel.addEventListener('message', event => {
  const message = event.data;
  incomingMessages.textContent += message + '\n';
});
```

{% endtab %}
{% endtabs %}

> Reference

<https://developer.mozilla.org/en-US/docs/Web/API/RTCIceCandidate>
<https://developer.mozilla.org/en-US/docs/Web/API/WebRTC_API/Connectivity>
<https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-how-it-works.html>
<https://antmedia.io/webrtc-servers/>
