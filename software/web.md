# Web

## Html

* Hyper Text Markup Language where W3 Consortium is main international standards organization
  * request and response protocol, media independent protocol, stateless protocol

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

## Javascript

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

* Packages

* Content delivery network (CDN)
* Cross-site request forgeries (csrf)
  * a type of malicious exploit whereby unauthorized commands are performed on behalf of an authenticated user
  * POST, PUT, PATCH, or DELETE request for a secret session value that the malicious application

* xml: Extensible Markup Language
  * markup language that defines a set of rules for encoding documents both human and machine-readable

* API (Application Programming Interface): a software intermediary that enables two apps to communicate with each other
  * All Web services are APIs but not all APIs are Web services
  * All Web services need a network to operate while APIs don’t need a network for operation
  * First estimate your usage and understand how that will impact the overall cost of the offering
  * Many protocols are now available to be used in API testing (ex JMS, REST, HTTP, UDDI and SOAP)

* Websocket: two way communication between the clients and the servers
  * Four main events: Open / Close / Error / Message

* Same Origin Policy
  * When using XMLHttpRequest or Fetch API → local files origin is null

* URI (Uniform Resource Identifier)
  * a string designed for unambiguous identification of resources and extensibility via the URI scheme

* xss (Cross Site Scripting)
  * users executed malicious scripts (aka payloads) unintentionally by clicking on untrusted links and hence
  * these scripts pass cookies information to attackers

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

* robot.txt: give rules on how site can be crawled
  * links to sitemap

* sitemap.xml: Informs search engines of the site structures
  * provides some meta information about individual pages

## Jquery

* introduces css-like syntax and several visual and UI enhancements
* simplifies the use of Javascript in websites
* an abstraction of the core language

> Variable

* variable starts with $
* $('#id');
* $('.classname')
* $('element:hidden/visible'): Matches all elements that are hidden / visible
* $('#container').children(':visible');: Get visible children

* each()

> Error

* Uncaught TypeError: Cannot read property 'call' of undefined
  * each() requires a handler use on() instead

> Terms

* global atrribute
  * data-*: Used to store custom data private to the page or application
  * dir: text direction for the content in an element
  * draggable: whether an element is draggable or not
  * hidden: Specifies that an element is not yet, or is no longer, relevant
  * id: Specifies a unique id for an element
  * lang: Specifies the language of the element's content
  * spellcheck: whether element is to have its spelling and grammar checked or not
  * style: an inline CSS style for an element
  * tabindex: tabbing order of an element
  * title: extra information about an element
  * translate: whether the content of an element should be translated or not
  * class: one or more classnames for an element (refers to a class in a style sheet)
  * accesskey: a shortcut key to activate/focus an element
  * contenteditable: Specifies whether the content of an element is editable or not

* &nbsp;: to add a single space
* &ensp;: to add 2 spaces
* &emsp;: to add 4 spaces
* \<\!\-- -->: commnet

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

> parent

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

{% tabs %}
{% tab title='javascript' %}

```js
// 1. Check hidden
child.offsetWidth > 0 && child.offsetHeight > 0 // also check if parent is hidden
object.style['display'] != 'none'               // only checks the element
```

{% endtab %}
{% endtabs %}

## Input Tag

* input
  * `<input([type=])>`: an input control (text, password, number)
  * onfocus / onfocusout    // add handler function when user click / unclick form

* form
  * an HTML form for user input
  * outline: none;: hide blue outline for text input

* textarea: a multiline input control (text area)
* button
* optgroup: a group of related options in a drop-down list
* fieldset: related elements in a form
* legend: a caption for a fieldset element
* output: the result of a calculation
* datalist: a list of pre-defined options for input controls

* select: a drop-down list
* option: an option in a drop-down list

> media

* alt
  * Specifies an alternate text for an image
* src
  * Source file path

* area
* map

{% tabs %}
{% tab title='javascript' %}

```jsx
// 1. area
<area shape="rect" coords="0,0,82,126" alt="Sun" href="sun.htm">
<area shape="circle" coords="90,58,3" alt="Mercury" href="mercur.htm">

// 2. Map
<img src="planets.gif" width="145" height="126" alt="Planets" usemap="#planetmap">
<map name="planetmap">
<area shape="rect" coords="0,0,82,126" alt="Sun" href="sun.htm">
</map>
```

{% endtab %}
{% endtabs %}

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

## Text

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

* overflow: specifies what should happen if content overflows an element's box
  * auto: clipped, a scroll-bar is added when content doesn’t fit
  * hidden: clipped, rest of content will be invisible
  * scroll: clipped, scroll will always show scrollbar even if content fits
  * initial / inherit: default / inherit from parent
  * overflow: visible|hidden|scroll|auto|initial|inherit;
  * visible (default): is not clipped. It renders outside the element's box

![overflow](images/20210219_221044.png)

{% tabs %}
{% tab title='css' %}

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
{% endtabs %}

### Link

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

## Media

* border: 1px solid #ddd
* border-radius: 4px
* opacity: 0.5

{% tabs %}
{% tab title='css' %}

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

## axios

* npm install axios
* Promise based HTTP client for the browser and node.js

```js
// 1. Sample request
axios({
  method: 'post',
  url: '/login',
  data: {
    firstName: 'Finn',
    lastName: 'Williams'
  }
});

// 2. Sample return
{
  data: {},    // response data from server
  headers: {}, // `headers`
  status: 200, // server status
  statusText: 'OK', // `statusText`
  config: {},
  request: {} // Browser: XMLHttpRequest instance, Node.js: ClientRequest instance (redirect)
}
```

> Cluster

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

> config

```js
// default.json
const require(‘config’);
const db = config.get("mongoURI")
```

> Events

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

> Nodemon

* constantly update UI

### Test

> markdownlint-cli2

* markdownlint-cli2 "**/*.md"

> elastic beanstalk

* eb init --platform node.js --region us-east-2

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

// Parses and returns info about the call stack at the given index.
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

> Input Type

* Request body: almost any kind of HTTP request
  * body editor is divided into 4 areas and has different controls depending on the body type

* form-data: simulates filling a form on a website
  * can attach files to a key as well

* urlencoded (default)
* key/value pairs and Postman will encode the keys and values properly

* raw: doesn't touch string entered in raw editor except replacing environment variables

* binary: allows you to send things which you can not enter in Postman
  * image, audio or video files, text files

> paypal

![Paypal](images/20210207_161157.png)

> Error: write EPROTO 140421695491864:error:100000f7:SSL routines:OPENSSL_internal:WRONG_VERSION_NUMBER:../../third_party/boringssl/src/ssl/tls_record.cc:242:

* Use http instead https because SSL is not set up

> nodeschedule

* [Comparison](https://velog.io/@filoscoder/%EC%8A%A4%EC%BC%80%EC%A4%84-%EC%97%85%EB%AC%B4-%EC%9E%90%EB%8F%99%ED%99%94-Node-cron-vs-Node-schedule-%EB%B9%84%EA%B5%90-clk4dyynve)

```js
const j = schedule.scheduleJob('00 30 11 * * 1-5', () => {
  console.log('Cron-style Scheduling')
})

// Recurrence Rule Scheduling
// Sun ~ Sat 0 ~ 6
// 월 ~ 일 17시 45분 실행
const rule = new schedule.RecurrenceRule();
rule.dayOfWeek = [0, new schedule.Range(0, 6)];
rule.hour = 17;
rule.minute = 45;
const k = schedule.scheduleJob(rule, () => {
  console.log('Recurrence Rule Scheduling');
})
```

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

> cheerio

* Cheerio parses markup and provides an API for traversing/manipulating the resulting data structure
* It does not interpret the result as a web browser does
* Specifically, it does not produce a visual rendering, apply CSS, load external resources, or execute JavaScript

## Javascript Database

> lodb

{% repo 'lodb' %}

> Algolia

* Simple text search
* index.clearObjects()

> TypeDI

```js
import Container from "typedi"
Container.get(TypeService);
```

## Sequelize

* Request from sequelize
* SQL Driver -> SQL Query -> DB
* Answer
* SQL Driver -> Sequelize -> Javascript Object

* Options
  * RESTRICT
  * CASCADE      # defaults for ON UPDATE
  * NO ACTION
  * SET DEFAULT
  * SET NULL     # default for One-To-One

* The defaults for the associations is SET NULL for ON DELETE and CASCADE for

> Sync Options

* User.sync(): creates the table if it doesn't exist (and does nothing if it already exists)
* User.sync({ force: true }): creates the table, dropping it first if it already existed
* User.sync({ alter: true }): checks columns, data type, then performs necessary changes

> Terms

* dialect: 'mysql'|'sqlite'|'postgres'|'mssql',

> Raw query

* query()
  * logging:: logging your queries will get called for every SQL query that gets sent to the server
  * plain:: If plain is true, then sequelize will only return first record of the result set. otherwise, return all records

{% tabs %}
{% tab title='logging.js' %}

```js
sequelize.sync({ logging: console.log }) // view the table creation queries
User.find(1, { logging: console.log })   // View query
```

{% endtab %}
{% endtabs %}

* literal()

{% tabs %}
{% tab title='literal()' %}

```js
// SELECT m.* FROM Movies m WHERE NOT EXISTS(
//   SELECT NULL FROM Users_Movies sc WHERE sc.Id_Movies = m.id AND sc.Id_Users = 1)
Movie.findAll({
  where: sequelize.literal("users.id IS NULL"),
  include: { model: Users, through: { attributes: [] } } })
```

{% endtab %}
{% endtabs %}

> Constraints

* allowNull
  * an attempt is made to set null to a field that does not allow null
  * ValidationError will be thrown without any SQL query being performed
  * after sequelize.sync, column with "allowNull: false" will be defined with a NOT NULL SQL constraint
  * So, direct SQL queries that attempt to set the value to null will also fail

```js
/* ... */ {
  username: {
    type: DataTypes.TEXT,
    allowNull: false,
    unique: true
  },
} /* ... */
```

> sequelize functions

* find, findOrCreate
* findByPk()
* findOrCreate()
* findAndCountAll()
* findAll()
* findAndCountAll()
  * count: an integer - the total number records matching the query
  * rows: an array of objects - the obtained records

{% tabs %}
{% tab title='findAll.js' %}

```js
// SELECT foo, bar AS baz, qux FROM ...
Model.findAll({
  attributes: ['foo', ['bar', 'baz'], 'qux']
});

// SELECT foo, COUNT(hats) AS n_hats, bar FROM ...
Model.findAll({
  // equivalent, useful when many values
  // { include: [ [sequelize.fn('COUNT', sequelize.col('hats')), 'n_hats'] ]
  attributes: [ 'foo', [sequelize.fn('COUNT', sequelize.col('hats')), 'n_hats'], 'bar' ]
});

// SELECT id, foo, bar, qux FROM ... (Assuming all columns are 'id', 'foo', 'bar', 'baz' and 'qux')
Model.findAll({
  attributes: { exclude: ['baz'] }
});

CustomerAccount.findAll({
  attributes: [
    'uuid',
    'account_name',
    'account_number',
    'emergency_pay',
    [Sequelize.fn('SUM', Sequelize.col('customer_accounts_services.invoice_amount')), 'totalInvoiceAmount'],
    [Sequelize.fn('SUM', Sequelize.col('customer_accounts_services.core_amount')), 'totalCoreAmount']
  ],
  include: [
    {
      model: CustomerAccountService,
      attributes: []
    }
  ],
  group: ['CustomerAccount.uuid']
}).then(...);

// 1. find and count all
const { count, rows } = await Project.findAndCountAll({
  where: {
    title: { [Op.like]: 'foo%' }
  },
  offset: 10,
  limit: 2
});
console.log(count);
console.log(rows);

// 2. Find by PK
const project = await Project.findByPk(123);
if (project === null) {
  console.log('Not found!');
} else {
  console.log(project instanceof Project); // true
}

// 3. findOrCreate
const [user, created] = await User.findOrCreate({
  where: { username: 'sdepold' },
  defaults: {
    job: 'Technical Lead JavaScript'
  }
});
```

{% endtab %}
{% endtabs %}

> Where

{% tabs %}
{% tab title='where.js' %}

```js
// SELECT * FROM post WHERE authorId = 2
Post.findAll({
  where: {
    authorId: 2   // [Op.eq]: 2
  }
});

// SELECT * FROM post WHERE authorId = 12 AND status = 'active';
Post.findAll({
  where: {
    authorId: 12
    status: 'active'
  }
});

// mysql
// SELECT file_id FROM table WHERE datediff(curdate(), create_date) > 5;
{
  where: sequelize.where(sequelize.fn('datediff', sequelize.fn("NOW") , sequelize.col('create_date')), {
    [Op.gt] : 5
  })
}
```

{% endtab %}
{% endtabs %}

> Operator

{% tabs %}
{% tab title='operator.js' %}

```js
const { Op } = require("sequelize");
Post.findAll({
  where: {
    [Op.and]: [{ a: 5 }, { b: 6 }],            // (a = 5) AND (b = 6)
    [Op.or]: [{ a: 5 }, { b: 6 }],             // (a = 5) OR (b = 6)
    someAttribute: {
      [Op.eq]: 3,                     // = 3
      [Op.ne]: 20,                    // != 20
      [Op.gt]: 6,                     // > 6
      [Op.gte]: 6,                    // >= 6
      [Op.lt]: 10,                    // < 10
      [Op.lte]: 10,                   // <= 10
      [Op.between]: [6, 10],          // BETWEEN 6 AND 10
      [Op.notBetween]: [11, 15],      // NOT BETWEEN 11 AND 15

      // Using dialect specific column identifiers (PG in the following example):
      [Op.col]: 'user.organization_id',        // = "user"."organization_id"

      [Op.is]: null,                  // IS NULL
      [Op.in]: [1, 2],                // IN [1, 2]
      id: [1,2,3]                     // Same as using `id: { [Op.in]: [1,2,3] }`
      [Op.all]: sequelize.literal('SELECT 1'), // > ALL (SELECT 1)
      [Op.not]: true,                 // IS NOT TRUE
      [Op.notIn]: [1, 2],             // NOT IN [1, 2]
      [Op.or]: [5, 6],                // (someAttribute = 5) OR (someAttribute = 6)

      [Op.like]: '%hat',              // LIKE '%hat'
      [Op.notLike]: '%hat',           // NOT LIKE '%hat'
      [Op.startsWith]: 'hat',         // LIKE 'hat%'
      [Op.endsWith]: 'hat',           // LIKE '%hat'
      [Op.substring]: 'hat',          // LIKE '%hat%'
      [Op.iLike]: '%hat',             // ILIKE '%hat' (case insensitive) (PG only)
      [Op.notILike]: '%hat',          // NOT ILIKE '%hat'  (PG only)
      [Op.regexp]: '^[h|a|t]',        // REGEXP/~ '^[h|a|t]' (MySQL/PG only)
      [Op.notRegexp]: '^[h|a|t]',     // NOT REGEXP/!~ '^[h|a|t]' (MySQL/PG only)
      [Op.iRegexp]: '^[h|a|t]',       // ~* '^[h|a|t]' (PG only)
      [Op.notIRegexp]: '^[h|a|t]',    // !~* '^[h|a|t]' (PG only)
      [Op.any]: [2, 3],               // ANY ARRAY[2, 3]::INTEGER (PG only)

      // In Postgres, Op.like/Op.iLike/Op.notLike can be combined to Op.any:
      [Op.like]: { [Op.any]: ['cat', 'hat'] }  // LIKE ANY ARRAY['cat', 'hat']
    }
  }
});
```

{% endtab %}
{% endtabs %}

* Grouping

```js
Subtask.findAll({
  order: [
    ['title', 'DESC'],      // escape title and validate DESC against a list of valid direction parameters
    sequelize.fn('max', sequelize.col('age')),            // order by max(age)
    [sequelize.fn('max', sequelize.col('age')), 'DESC'],  // Will order by max(age) DESC

    // Will order by  otherfunc(`col1`, 12, 'lalala') DESC
    [sequelize.fn('otherfunc', sequelize.col('col1'), 12, 'lalala'), 'DESC'],

    // order an associated model's createdAt using the model name as the association's name.
    [Task, 'createdAt', 'DESC'],
    ['Task', 'createdAt', 'DESC'], // order by an associated model's createdAt using the name of the association.

    // order through an associated model's createdAt using the model names as the associations' names
    [Task, Project, 'createdAt', 'DESC'],
    ['Task', 'Project', 'createdAt', 'DESC'], // order by a nested associated model's createdAt using the names of the associations.

    [{model: Task, as: 'Task'}, 'createdAt', 'DESC'],   // order by an associated model's createdAt using a association object.

    // order by an associated model's createdAt using an association object. (preferred)
    [Subtask.associations.Task, 'createdAt', 'DESC'],

    // order by a nested associated model's createdAt association objects.
    [{model: Task, as: 'Task'}, {model: Project, as: 'Project'}, 'createdAt', 'DESC']

    // order by a nested associated model's createdAt using association objects. (preferred)
    [Subtask.associations.Task, Task.associations.Project, 'createdAt', 'DESC'],
  ],

  order: sequelize.literal('max(age) DESC'),        // order by max age descending

  // order by max age ascending assuming ascending is default order when direction is omitted
  order: sequelize.fn('max', sequelize.col('age')),
  order: sequelize.col('age'), // order by age ascending assuming ascending is default order when direction is omitted
  order: sequelize.random()    // order randomly based on the dialect (instead of fn('RAND') or fn('RANDOM'))
});

Foo.findOne({
  order: [
    ['name'],               // will return `name`
    ['username', 'DESC'],   // will return `username` DESC
    sequelize.fn('max', sequelize.col('age')),            // return max(`age`)
    [sequelize.fn('max', sequelize.col('age')), 'DESC'],  // return max(`age`) DESC

    // will return otherfunction(`col1`, 12, 'lalala') DESC
    [sequelize.fn('otherfunction', sequelize.col('col1'), 12, 'lalala'), 'DESC'],

    // will return otherfunction(awesomefunction(`col`)) DESC, This nesting is potentially infinite!
    [sequelize.fn('otherfunction', sequelize.fn('awesomefunction', sequelize.col('col'))), 'DESC']
  ]
});
```

{% tabs %}
{% tab title='sequelize' %}

* subQuery

```js
// SELECT *, ( SELECT COUNT(*) FROM reactions AS reaction
//     WHERE reaction.postId = post.id AND reaction.type = "Laugh") AS laughReactionsCount
//   FROM posts AS post
Post.findAll({
  attributes: {
    include: [
      [ // Note the wrapping parentheses in the call below!
        sequelize.literal(`( SELECT COUNT(*) FROM reactions AS reaction \
          WHERE reaction.postId = post.id AND reaction.type = "Laugh")`),
        'laughReactionsCount'
      ]
    ]
  },
  order: [
    [sequelize.literal('laughReactionsCount'), 'DESC']
  ]
});
```

> LEFT OUTER JOIN

* (default)
* only includes records from the parent table

```js
// SELECT parent.id, parend.name, child.id, child.name FROM parent
//   LEFT OUTER JOIN child ON child..parent = parent.id;
Parent.findAll({
  include: [ { model: Child } ]
});
```

* where

```js
Albums.findAll({
  include: [{
    model: Artists,
    as: 'Singer',
    where: { name: 'Al Green' }
  }]
})
```

* Referring to other columns
  * [NOTE] if hasMany, put user plural model name

```js
// SELECT * FROM user JOIN task ON
//   WHERE task.name = 'foobar'
User.findAll({
  include: [Task],
  where: { '$task.name$': 'foobar' }
});

// SELECT * FROM project JOIN task ON
//   WHERE task.state == project.state
Project.findAll({
  include: {
    model: Task,
    where: { state: Sequelize.col('project.state') }
  }
})
```

* RIGHT OUTER JOIN
  * right: true

* LEFT OUTER JOIN
  * required: false

{% tabs %}
{% tab title='join.js' %}

```js
// 1. Inner
/*
SELECT `user`.`id`, `user`.`name`, `Instruments`.`id` AS `Inst.id`, `Instruments`.`name` \
  AS `Inst.name`, `Instruments`.`size` AS `Instr.size`, `Instruments`.`userId` AS `Inst.userId` FROM `users` AS `user`
  INNER JOIN `tools` AS `Inst` ON `user`.`id` = `Inst`.`userId` AND `Inst`.`size` != 'small';
*/
User.findAll({
  include: {
    model: Tool,
    as: 'Instruments'
    where: {
      size: { [Op.ne]: 'small' }
    }
  }
});

// 2. Left Outer
/*
SELECT [...] FROM `users` AS `user`
LEFT OUTER JOIN `tools` AS `Instruments` ON `user`.`id` = `Instruments`.`userId` AND `Instruments`.`size` != 'small';
*/
await User.findAll({
  include: {
    model: Tool,
    as: 'Instruments',
    where: { size: { [Op.ne]: 'small' } },
    required: false
  }
});
```

{% endtab %}
{% tab title='read.js' %}

```js
// 2. Nested: Sequelize help the main (larger query) but you will still have to write that sub-query by yourself
// SELECT *, (SELECT COUNT(*) FROM reactions AS reaction
//            WHERE reaction.postId = post.id AND reaction.type = "Laugh") AS laughReactionsCount
// FROM posts AS post
Post.findAll({
  attributes: {
    include: [[ sequelize.literal(`( SELECT COUNT(*) FROM reactions AS reaction
                                     WHERE reaction.postId = post.id AND reaction.type = "Laugh")`),
                                     'laughReactionsCount']]
  }
});

// SELECT * FROM characteristic
//   WHERE characteristic_id = 1 and characteristic_id in (
//     select characteristic_id from characteristic_variant_val where rel_type = 'variant')
characteristic_id : {
  $in: [clout.sequelize.literal('select characteristic_id from characteristic_variant_val'))]
}
```

{% endtab %}
{% tab title='update.js' %}

```js
// 1. Update
//// Change everyone without a last name to "Doe"
await User.update({ lastName: "Doe" }, {
  where: { lastName: null }
});

//// UPDATE post SET updatedAt = null WHERE deletedAt NOT NULL;
Post.update({
  updatedAt: null,
}, {
  where :{
    deletedAt: { [Op.ne]: null }
  }
})

//// Toggle boolean
{
  where: { id },
  params: { finish: Sequelize.literal("NOT finish") },
}

// 2. Transaction
const t = await sequelize.transaction();

try {
  // Then, we do some calls passing this transaction as an option:
  const user = await User.create({
    firstName: 'Bart',
    lastName: 'Simpson'
  }, { transaction: t });

  await user.addSibling({
    firstName: 'Lisa',
    lastName: 'Simpson'
  }, { transaction: t });

  // If the execution reaches this line, no errors were thrown. We commit the transaction.
  await t.commit();

} catch (error) {

  // If the execution reaches this line, an error was thrown. We rollback the transaction.
  await t.rollback();
}
```

{% endtab %}
{% tab title='delete.js' %}

```js
// 1. Delete
// Delete everyone named "Jane"
await User.destroy({
  where: { firstName: "Jane" }
});

// DELETE FROM post WHERE status = "inactive"
Post.destroy({
  where: {
    status: 'inactive'
  }
});
```

{% endtab %}
{% endtabs %}

## Express

* Express works on the server-side, running on top of node.js
* Express is a 'web application framework'
* Handle route, accept client requests, retrieve data from DB, prepare views and send back responses

```js
// 1. Hello World
const express = require('express');
const PORT = process.env.HTTP_PORT || 4001;
const app = express();
app.get('/', (req, res) => {
  res.send('flowers smell nice');
});
app.listen(PORT, () => {
  console.log(`Server listening at port ${PORT}.`);
});

// Router
const express = require("express"); // Simple 3000 hosting
const app = express();              // set up view engine
app.set("view engine", "ejs");
app.get("/", (req, res) => {res.render("home");}); // create home route

app.listen(3000, () => {
  console.log("app now listening for requests on port 3000");
});
```

{% repo 'url_shorten' %}

## React

* Framework vs Library
  * Framework is a piece of code that dictates the architecture of your project and aids in programs
  * pre-written JavaScript which allows for easier development of JavaScript-based applications

* Create-react-app → Need node > 6
* Webpack development environment → run live server and a development environment
* babel → manage your code, make it write a version compatible with older browsers

> Terms

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

## Component

{% tabs %}
{% tab title='react' %}

> Term

* HOC: higher-order component is a function that takes a component and returns a new component
  * replacement of mixin as it introduces implicit dependencies and cause name clashes, complexity
  * [ex] CommentList, BlogPost

```ts
function withSubscription(WrappedComponent, selectData) {  // This function takes a component.
  return class extends React.Component {  // returns another component.
    constructor(props) {
      super(props);
      this.handleChange = this.handleChange.bind(this);
      this.state = { data: selectData(DataSource, props) };
    }

    componentDidMount() {
      DataSource.addChangeListener(this.handleChange);  // ... that takes care of the subscription...
    }

    componentWillUnmount() { DataSource.removeChangeListener(this.handleChange); }

    handleChange() {
      this.setState({ data: selectData(DataSource, this.props) });
    }

    render() {
      // renders the wrapped component with the fresh data! Notice that we pass through any additional props
      return <WrappedComponent data={this.state.data} {...this.props} />;
    }
  };
}
```

{% endtab %}
{% endtabs %}

### Class

* functions accept inputs (props) and return elements
* must have only one div
* starts with upper-cass

```js
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
```

### Functional

* Hook allows you to use functional component
* Only call Hooks at the top level. Don’t call Hooks inside loops, conditions, or nested functions
* Only call Hooks from React function components. Don’t call Hooks from regular JavaScript functions

```js
const [count, setCount] = useState(0);

// Similar to componentDidMount and componentDidUpdate:
useEffect(() => {
  // Update the document title using the browser API
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

### Router

{% tabs %}
{% tab title='django' %}

```py
# 1. views.py
from .models import Article
from .serializers import ArticleSerializer
from rest_framework import viewsets
from rest_framework.response import Response
from rest_framework import status
from django.shortcuts import get_object_or_404

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
```

{% endtab %}
{% tab title='react' %}

> (16,8): error TS2322: Type '{ children: Element; }' is not assignable to type 'IntrinsicAttributes & ...
  Type '{ children: Element; }' is not assignable to type 'Readonly\<RouterProps\>'.
  Property 'history' is missing in type '{ children: Element; }'.

```js
// import { Router } from 'react-router-dom';
import { BrowserRouter as Router } from 'react-router-dom';
```

{% endtab %}
{% endtabs %}

## States

{% tabs %}
{% tab title='react' %}

* Read-only
* share state by moving to closest common ancestor of the components that need it → lifting state up
* State is reserved only for interactivity, that is, data that changes over time

> Method

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

### Nav

{% tabs %}
{% tab title='react' %}

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

## Mobx

![Mobx](images/20210615_211557.png)

* [Mobx tutorial](https://mobxjs.github.io/mobx/getting-started.html)

```ts
import { observer } from "mobx-react-lite"

const myTimer = new Timer() // See the Timer definition above.
const TimerView = observer(({ timer }) => <span>Seconds passed: {timer.secondsPassed}</span>)

// Pass myTimer as a prop.
ReactDOM.render(<TimerView timer={myTimer} />, document.body)
```

* Store: similar to controller in MVC pattern
  * move logic and state out of components into testable unit
* domain state: store the data your application is all about
  * should be expressed using its own class or constructor function
* UI state: often very specific for your application, but usually very simple without logic
  * loosely coupled pieces of information about the UI
  * [ex] Session information, how far your application loaded, data not stored in the backend, data affects the UI globally

### Mobx react

* observe: intercept changes after they have been made
* intercept: detect and modify mutations before they are applied to the observable (validating, normalizing or cancelling)

> Method

* observer(): HoC automatically subscribes React components to any observables that are used during rendering
* useObserver(): Low level implementation used internally by observer HOC and Observer component
  * allows you to use an observer like behaviour

{% repo 'mobx-react' %}

## Material UI

* Explicitly built for react
* Flexibility, customize than bootstrap and semantic UI
* Active development, hooks

{% repo 'material' %}

### Expo

> Lan

* For this to work, on the same wifi network as your computer
* Fastest, safest. The phone connects to your computer just through your router

> Tunnel

* Under tunnel setting, your computer will setup a tunnel to exp.direct,
* a domain using the ngrok tunnel service
* all traffic will go through a proxy in the cloud, but it can punch through most firewalls,
* it will work under more conditions

> download

```sh
npm install -g expo-cli
expo init my-new-project
cd my-new-project
expo start
npm run eject    # removes the app from the Expo framework
```

## Heatlh Check

{% tabs %}
{% tab title='djagno' %}

> health_check

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
