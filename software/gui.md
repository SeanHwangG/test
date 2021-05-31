# GUI

{% tabs %}
{% tab title='python' %}

> PyQt5

```py
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout
from PyQt5.QtGui import QPixmap, QImage
import numpy as np
import sys


def print_img():
  app = QApplication(sys.argv)
  win = QWidget()
  label = QLabel()
  label.setPixmap(QPixmap("data/beach.jpg"))
  vbox = QVBoxLayout()
  vbox.addWidget(label)
  win.setLayout(vbox)
  win.show()

  sys.exit(app.exec_())


def print_np():
  app = QApplication(sys.argv)

  win = QWidget()
  label = QLabel()

  img = np.zeros((500, 500), dtype=np.uint8)
  img[250:, :] = 255

  qImg = QPixmap(
      QImage(img.data, img.shape[0], img.shape[1], QImage.Format_Indexed8))
  label.setPixmap(qImg)

  vbox = QVBoxLayout()
  vbox.addWidget(label)
  win.setLayout(vbox)
  win.show()

  sys.exit(app.exec_())

print_np()


class App(QWidget):
  def __init__(self):
    super().__init__()
    self.title = 'PyQt5 image - pythonspot.com'
    # position of the window
    self.left = 10
    self.top = 10
    # size of the window
    self.width = 640
    self.height = 480

    self.setWindowTitle(self.title)
    self.setGeometry(self.left, self.top, self.width, self.height)

    # Create widget
    label = QLabel(self)
    img = np.zeros((50, 50, 40))
    image = QPixmap(QImage(img.data, 50, 50, 1, QImage.Format_RGB888))
    PrintImage
    # label.setPixmap(image)

    self.show()

app = QApplication(sys.argv)
ex = App()
sys.exit(app.exec_())
```

> pyautogui

* pyautogui.mouseInfo(): get RGB from mouse
* pyautogui.pixel(28, 18): get RGB from pixel

* Box
  * left, top, width, height

* locateOnScreen
  * region=(x, y, width, height)
  * greyscale=True
  * confidence=0.9 (pip install opencv-python)

```py
file_loc = pyautogui.locateOnScreen("file_menu.png") # Get location on certain image, None if not exists
pyautogui.moveTo(file_loc)
pyautogui.click(file_loc)

# Multiple images
for file_loc in pyautogui.locateAllOnScreen("file_menu.png"):
  pyautogui.click(i, duration=0.25)

# With timeout
file_location = None
while not file_location:
  file_location = pyautogui.locateOnScreen("file_menu.png")
  end = time.time()
  if end - start > timeout:
  print("timout")
  sys.exit()
```

{% endtab %}
{% endtabs %}

## Component

{% tabs %}
{% tab title='react' %}

![Lifecycle](images/20210715_173414.png)

> Term

* Class: functions accept inputs (props) and return elements
  * must have only one div
  * starts with upper-cass
* Functional: Hook allows you to use functional component
  * Only call Hooks at the top level. Don’t call Hooks inside loops, conditions, or nested functions
  * Only call Hooks from React function components. Don’t call Hooks from regular JavaScript functions

```js
// 1. Class component
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

> Reference

<https://reactjs.org/docs/react-component.html>
<https://projects.wojtekmaj.pl/react-lifecycle-methods-diagram/>

{% endtab %}
{% endtabs %}

## Mouse Event

{% tabs %}
{% tab title='javascript' %}

* onchange: HTML element has been changed
* onclick: clicks an HTML element
* onmouseover: moves the mouse over an HTML element
* onmouseout: moves the mouse away from an HTML element
* onkeydown: pushes a keyboard key
* onload: browser has finished loading the page

* :focus: selected input with focus (clicked)
* :hover: when mouse move over it
* :active: it adds style to active link
* :selected: for checkbox
* :checked+label: for radio
* :first-of-type: first element
* :link / visited: add style to unvisited / visited link

```jsx
// 1. Change color on hover
// html
<style>
  html, body { height: 100%; margin: 0; }
  .screen { height: 100%; background-color: black; display: flex; }
  .left { background-color: red; }
  p:hover~.screen { display: var(--arg); }
</style>
<p style="--arg: hidden;">show</p>
<div class="screen"> </div>

// css
<style>
#a:hover + #b { background: #ccc }
</style>
<div id="a">Div A</div>
<div id="b">Div B</div>

// 2. custom event
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Creating Events</title>
  <meta name="viewport" content="width=device-width">
</head>
<body>
  <h1>Creating Events</h1>
  <main>
  </main>
  <script>
    //1. let evt = new Event('explode');
    //2. let evt = new CustomEvent('explode', {detail:{speed:20, volume:40}});
    let born = new Event('born');
    let died = new CustomEvent('died', {detail:{time:Date.now()}});

    document.addEventListener('DOMContentLoaded', function (){
      let m = document.querySelector('main');
      addParagraph(m, 'This is a paragraph.');
      addParagraph(m, 'A new Star Wars movie is coming soon.');
      m.addEventListener('click', function(ev){ removeParagraph(m, m.firstElementChild); })
    });

    function addParagraph(parent, txt){
      let p = document.createElement('p');
      p.textContent = txt;
      //set up and dispatch events
      p.addEventListener('born', wasBorn);
      p.addEventListener('died', hasDied);
      p.dispatchEvent(born)
      parent.appendChild(p); //add to screen
    }
    function removeParagraph(parent, p){
      p.dispatchEvent(died); // dispatch event
      parent.removeChild(p); //remove element from screen
    }
    function wasBorn(ev){
      console.log(ev.type, ev.target);
    }
    function hasDied(ev){
      console.log(ev.type, ev.target, ev.detail.time);
      //remove the listeners
      ev.target.removeEventListener('born', wasBorn);
      ev.target.removeEventListener('died', hasDied);
    }
  </script>
</body>
</html>
```

{% endtab %}
{% tab title='python' %}

```py
# 1. Pallete class
class Pallete:
  def __init__(self):
    self.ix = -1
    self.iy = -1
    # HEIGHT/y: 200, WIDTH/x: 300
    self.img = np.ones((200, 300, 3), np.uint8) * 255
    self.mode = "RECTANGLE"
    self.points = []

  def draw_shape(self, event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
      self.drawing = True
      (self.ix, self.iy) = x, y
    elif event == cv2.EVENT_LBUTTONUP:
      self.drawing = False
      cv2.rectangle(self.img, (self.ix, self.iy), (x, y), (0, 0, 0), -1)

  def draw_line(self, event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
      # OpenCV uses BGR
      cv2.circle(self.img, (x, y), 3, (0, 0, 255), -1)
      self.points.append((x, y))
    elif event == cv2.EVENT_LBUTTONUP:
      if len(self.points) > 1:
        self.img = cv2.line(
          self.img, self.points[-1], self.points[-2], (255, 0, 0), 5)

  def start(self):
    windowName = 'Drawing Demo'
    cv2.namedWindow(windowName)
    cv2.setMouseCallback(windowName, self.draw_line)
    while(True):
      cv2.imshow(windowName, self.img)

      k = cv2.waitKey(1)
      if k == 27:
        break

    cv2.destroyAllWindows()

# 2. grep cut
src = cv2.imread('data/messi.jpg')

mask = np.zeros(src.shape[:2], np.uint8)
bgdModel = np.zeros((1, 65), np.float64)
fgdModel = np.zeros((1, 65), np.float64)
rc = cv2.selectROI(src)
cv2.grabCut(src, mask, rc, bgdModel, fgdModel, 1, cv2.GC_INIT_WITH_RECT)
mask2 = np.where((mask == 0) | (mask == 2), 0, 1).astype('uint8')
dst = src * mask2[:,:, np.newaxis]

cv2.imshow('dst', dst)

def on_mouse(event, x, y, flags, param):
  if event == cv2.EVENT_LBUTTONDOWN:
    cv2.circle(dst, (x, y), 3, (255, 0, 0), -1)
    cv2.circle(mask, (x, y), 3, cv2.GC_FGD, -1)
  elif event == cv2.EVENT_RBUTTONDOWN:
    cv2.circle(dst, (x, y), 3, (0, 0, 255), -1)
    cv2.circle(mask, (x, y), 3, cv2.GC_BGD, -1)
  elif event == cv2.EVENT_MOUSEMOVE:
    if flags & cv2.EVENT_FLAG_LBUTTON:
      cv2.circle(dst, (x, y), 3, (255, 0, 0), -1)
      cv2.circle(mask, (x, y), 3, cv2.GC_FGD, -1)
    elif flags & cv2.EVENT_FLAG_RBUTTON:
      cv2.circle(dst, (x, y), 3, (0, 0, 255), -1)
      cv2.circle(mask, (x, y), 3, cv2.GC_BGD, -1)
  cv2.imshow('dst', dst)

cv2.setMouseCallback('dst', on_mouse)

while True:
  key = cv2.waitKey()
  if key == 13:
    cv2.grabCut(src, mask, rc, bgdModel, fgdModel, 1, cv2.GC_INIT_WITH_MASK)
    mask2 = np.where((mask == 2) | (mask == 0), 0, 1).astype('uint8')
    dst = src * mask2[:,:, np.newaxis]
    cv2.imshow('dst', dst)
  elif key == 27:
    break

cv2.destroyAllWindows()
```

{% endtab %}
{% endtabs %}

## Select

{% tabs %}
{% tab title='javascript' %}

* label
  * a label for an input tag

```js
// 1. Radio: one by default set checked to select by default
<style>
  [type="radio"]:checked+label { font-weight: bold; }
  [type="radio"]#male:checked~p { color: blue; }
  [type="radio"]#female:checked~p { color: red; }
  [type="radio"]#young:checked~p { font-size: 20px; }
  [type="radio"]#old:checked~p { font-size: 30px; }
</style>
<input type="radio" id="male" name="gender" checked> <label for="male">male</label>
<input type="radio" id="female" name="gender"> <label for="female">female</label>
<br>
<input type="radio" id="young" name="age"> <label for="young">young</label>
<input type="radio" id="old" name="age" checked> <label for="old">old</label>
<p>Hi</p>

```

{% endtab %}
{% endtabs %}

### Multi Select

{% tabs %}
{% tab title='javascript' %}

* input
  * type: [ex] checkbox

```jsx
// 1. Option
<label for="cars">Choose a car:</label>
<select name="cars" id="cars">
  <option value="volvo">Volvo</option>
  <option value="saab">Saab</option>
  <option value="mercedes">Mercedes</option>
  <option value="audi">Audi</option>
</select>

<input type="number" min="0" max="64" list="numbersxx" id="numberx">        # number color text
<input type="checkbox" id="agree" />
<label for="agree">I agree with the Terms and Conditions</label>
<label>My input <input type="text" id="my-input" /> </label>
```

{% endtab %}
{% endtabs %}

### Slider

{% tabs %}
{% tab title='django' %}

> admin-numeric-filter

* pip install django-admin-numeric-filter

```py
# admin.py
from admin_numeric_filter.admin import NumericFilterModelAdmin, SingleNumericFilter, RangeNumericFilter, SliderNumericFilter
from .models import YourModel

class CustomSliderNumericFilter(SliderNumericFilter):
  MAX_DECIMALS = 2
  STEP = 10

@admin.register(YourModel)
class YourModelAdmin(NumericFilterModelAdmin):
  list_filter = (
    ('field_A', SingleNumericFilter),       # Single field search, __gte lookup
    ('field_B', RangeNumericFilter),        # Range search, __gte and __lte lookup
    ('field_C', SliderNumericFilter),       # Same as range above but with slider
    ('field_D', CustomSliderNumericFilter), # Filter with custom attributes
  )
```

{% endtab %}
{% endtabs %}

{% tabs %}
{% tab title='javascript' %}

```js
// 1. Silder
<style>
  .switch {
    position: relative;
    display: inline-block;
    width: 60px;
    height: 34px;
  }

  .switch input {
    opacity: 0;
    width: 0;
    height: 0;
  }

  /* Square slider */
  .slider {
    position: absolute;
    cursor: pointer;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: #ccc;
    -webkit-transition: .4s;
    transition: .4s;
  }

  .slider:before {
    position: absolute;
    content: "";
    height: 26px;
    width: 26px;
    left: 4px;
    bottom: 4px;
    background-color: white;
    -webkit-transition: .4s;
    transition: .4s;
  }

  input:checked+.slider {
    background-color: #2196F3;
  }

  input:focus+.slider {
    box-shadow: 0 0 1px #2196F3;
  }

  input:checked+.slider:before {
    -webkit-transform: translateX(26px);
    -ms-transform: translateX(26px);
    transform: translateX(26px);
  }

  /* Rounded sliders */
  .slider.round {
    border-radius: 34px;
  }

  .slider.round:before {
    border-radius: 50%;
  }
</style>
<label class="switch">
  <input type="checkbox">
  <span class="slider"></span>
</label>

<label class="switch">
  <input type="checkbox">
  <span class="slider round"></span>
</label>
```

{% endtab %}
{% endtabs %}

## PPT

{% tabs %}
{% tab title='python' %}

> python-pptx

```py
class PPT:
  def __init__(self, layout=[12192000, 6858000]):     # 13.33, 7.5 inches
    self.layout = layout
    if os.path.exists('template.pptx'):
      self.prs = Presentation('template.pptx')    # template file with "browsed by individual window" turned on
      rId = self.prs.slides._sldIdLst[0].rId
      self.prs.part.drop_rel(rId)
      del self.prs.slides._sldIdLst[0]
    else:
      self.prs = Presentation()                   # starting from default settings
    self.prs.slide_width, self.prs.slide_height = layout

  def create_verse(self, sermon):     # Bible.pptx format (verses and hyperlinks)
    self.add_slide()                # create title slide
    if '"' in sermon.title:
      self.add_textbox(sermon.title, [1.67, 0.08, 10, 1.2], 26, spacing=1.1)
    else:
      self.add_textbox('"' + sermon.title + '"', [1.67, 0.08, 10, 1.2], 26, spacing=1.1)
    self.add_paragraph('(' + sermon.passages_raw[0] + '/ ' + sermon.preacher + ')', 24)

    p = self.add_verse_slides(sermon.passages_ext, 'p')     # add verses in main passage
    q = self.add_verse_slides(sermon.quotes_ext, 'q')       # add verses to quote

    for slide in self.prs.slides:
      self.slide = slide
      self.add_link_table(p + q)  # add hyperlink table

  def create_large(self, sermon):     # Large.pptx format
    self.add_large_slides(sermon, sermon.passages_ext, 7)

  def add_slide(self):                # create new blank slide
    self.slide = self.prs.slides.add_slide(self.prs.slide_layouts[6])
```

{% endtab %}
{% endtabs %}

## GUI List

* ul: an unordered list
* ol: an ordered list
* li: a list item
* dl: a description list
* dt: a term/name in a description list
* dd: a description of a term/name in a description list

## Table

{% tabs %}
{% tab title='javascript' %}

* table: a table
* caption: a table caption
* th: a header cell in a table
* tr: a row in a table
* td: a cell in a table
* thead: Groups the header content in a table
* tbody: Groups the body content in a table
* tfoot: Groups the footer content in a table
* col: Specifies column properties for each column within a `<colgroup>` element
* colgroup: Specifies a group of one or more columns in a table for formatting

{% endtab %}
{% endtabs %}
