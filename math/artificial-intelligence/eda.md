# EDA

> Reference

* [Matplot lib](https://matplotlib.org/stable/gallery/index.html)

{% tabs %}
{% tab title='python' %}

* mathplot
  * 0 is black 1 is white
  * Matplotlib only supports PNG images
  * float32 and uint8 (only float32 greyscale)
  * axis('off'): Remove axis
  * imshow(img, cmap) → None        # Display Image ('gray')
  * fig.colorbar(im, ax=ax)

![colorbar](images/20210309_003050.png)
![color types](images/20210309_010526.png)

```py
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

fig, axs = plt.subplots(2, 3)
axs[0, 0].set_title('1 : scatter')
axs[0, 0].plot([1, 2, 3, 4], [1, 4, 9, 16], 'ro')

axs[0, 1].set_title('2 : line')
axs[0, 1].plot([1, 2, 3, 4], [1, 4, 9, 16])

axs[0, 2].set_title('3 : heatmap')
axs[0, 2].imshow(np.random.random((16, 16)), cmap='hot', interpolation='nearest')

axs[1, 0].set_title('4 : bar')
axs[1, 0].bar(['A', 'B', 'C'], [1, 5, 3])

axs[1, 1].set_title('5 : curve')
axs[1, 1].plot(np.linspace(0, 2 * np.pi, 400), np.sin(np.linspace(0, 2 * np.pi, 400) ** 2))

X, Y = np.meshgrid(np.arange(-5,6,1), np.arange(-5,6,1))
u, v = X|5, -Y|5
axs[1, 2].quiver(X,Y,u,v)

plt.show()

for ax in axs.flat:
  ax.set(xlabel='x-label', ylabel='y-label')

# Hide x labels and tick labels for top plots and y ticks for right plots.
for ax in axs.flat:
  ax.label_outer()

# Color types
from cv2 import cv2
import matplotlib.pyplot as plt

fig, axs = plt.subplots(1, 5)

dog_np = cv2.cvtColor(cv2.imread('data/dog.jpg'), cv2.COLOR_BGR2RGB)
axs[0].imshow(dog_np)
axs[0].axis('off')

axs[1].imshow(cv2.imread('data/dog.jpg', cv2.IMREAD_GRAYSCALE))
axs[1].axis('off')

axs[2].imshow(cv2.resize(dog_np,(300, 600)))
axs[2].axis('off')

axs[3].imshow(cv2.resize(dog_np, (0,0), dog_np, 1, 0.5))
axs[3].axis('off')

axs[4].imshow(cv2.flip(dog_np, -1))
axs[4].axis('off')

cv2.imwrite("data/dog_np.jpg", dog_np)
```

{% endtab %}
{% endtabs %}

## Bar Graph

{% tabs %}
{% tab title='python' %}

![horizontal](images/20210614_082839.png)
![Draw n gram](images/20210520_201231.png)

```py
import matplotlib.pyplot as plt
import numpy as np

# 1. Mathplot
np.random.seed(19680801)

people = ('Tom', 'Dick', 'Harry', 'Slim', 'Jim')
y_pos = np.arange(len(people))
performance = 3 + 10 * np.random.rand(len(people))
error = np.random.rand(len(people))

fig, ax = plt.subplots()

hbars = ax.barh(y_pos, performance, xerr=error, align='center')
ax.set_yticks(y_pos)
ax.set_yticklabels(people)
ax.invert_yaxis()
ax.set_xlabel('Performance')
ax.set_title('How fast do you want to go today?')

ax.bar_label(hbars, fmt='%.2f')
ax.set_xlim(right=15)

plt.show()

# 2. draw n gram
def draw_n_gram(string,i):
  n_gram = (pd.Series(nltk.ngrams(string, i)).value_counts())[:15]
  n_gram_df=pd.DataFrame(n_gram)
  n_gram_df = n_gram_df.reset_index()
  n_gram_df = n_gram_df.rename(columns={"index": "word", 0: "count"})
  print(n_gram_df.head())
  plt.figure(figsize = (16,9))
  return sns.barplot(x='count',y='word', data=n_gram_df)
```

{% endtab %}
{% tab title='r' %}

* colab.to/r
* hist()
  * breaks: x-axis width

```r
library(ggplot2)

# 1. Plot
(mis <- read.csv("MIS_mid_data.csv")) # read csv

ages <- mis$age
hist(ages, breaks=10)
```

{% endtab %}
{% endtabs %}

### Vertical

{% tabs %}
{% tab title='python' %}

![vertical](images/20210614_082910.png)

> Seaborn

![count plot](images/20210309_002938.png)

* seaborn.countplot(`Y_train`): [ex] [1,2,3,4,5,6,7,5,7,4,58,45,2,4,53,45,2]

```py
# 1. plt.md
fig, ax = plt.subplots()

p1 = ax.bar(ind, menMeans, width, yerr=menStd, label='Men')
p2 = ax.bar(ind, womenMeans, width, bottom=menMeans, yerr=womenStd, label='Women')

ax.axhline(0, color='grey', linewidth=0.8)
ax.set_ylabel('Scores')
ax.set_title('Scores by group and gender')
ax.set_xticks(ind)
ax.set_xticklabels(('G1', 'G2', 'G3', 'G4', 'G5'))
ax.legend()

ax.bar_label(p1, label_type='center')
ax.bar_label(p2, label_type='center')
ax.bar_label(p2)

plt.show()
```

{% endtab %}
{% endtabs %}

## Line

{% tabs %}
{% tab title='python' %}

![line](images/20210614_083233.png)
![ROC](images/20210614_085922.png)

```py
import matplotlib.pyplot as plt
import numpy as np
from sklearn import svm, datasets
from sklearn.model_selection import train_test_split
from sklearn.metrics import precision_recall_curve, plot_precision_recall_curve

# 1. Line
t = np.arange(0.0, 2.0, 0.01)
s = 1 + np.sin(2 * np.pi * t)

fig, ax = plt.subplots()
ax.plot(t, s)

ax.set(xlabel='time (s)', ylabel='voltage (mV)', title='About as simple as it gets, folks')
ax.grid()

fig.savefig("test.png")
plt.show()

# 2. ROC
iris = datasets.load_iris()
X, y = iris.data, iris.target

n_samples, n_features = X.shape # Add noisy feature
X = np.c_[X, random_state.randn(n_samples, 200 * n_features)]

""" Limit to the two first classes, and split into training and test """
X_train, X_test, y_train, y_test = train_test_split(X[y < 2], y[y < 2], test_size=.5)

classifier = svm.LinearSVC(random_state=random_state)
classifier.fit(X_train, y_train)
y_score = classifier.decision_function(X_test)

disp = plot_precision_recall_curve(classifier, X_test, y_test)
disp.ax_.set_title(f'2-class Precision-Recall curve: ' 'AP={average_precision:0.2f}')
```

{% endtab %}
{% endtabs %}

### Surface

{% tabs %}
{% tab title='python' %}

![Surface](images/20210614_083817.png)

```py
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

X = np.arange(-5, 5, 0.25)
Y = np.arange(-5, 5, 0.25)
X, Y = np.meshgrid(X, Y)
R = np.sqrt(X**2 + Y**2)
Z = np.sin(R)

fig = plt.figure()
ax = Axes3D(fig, auto_add_to_figure=False)
fig.add_axes(ax)
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.viridis)

plt.show()
```

{% endtab %}
{% endtabs %}

## Pie

{% tabs %}
{% tab title='python' %}

```py
import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots(figsize=(6, 3), subplot_kw=dict(aspect="equal"))

data = [375, 75, 250, 300]
ingredients = ["flour", "sugar", "butter", "berries"]

def func(pct, allvals):
  absolute = int(round(pct/100.*np.sum(allvals)))
  return f"{pct:.1f}%\n({absolute:d} g)"


wedges, texts, autotexts = ax.pie(data, autopct=lambda pct: func(pct, data), textprops=dict(color="w"))

ax.legend(wedges, ingredients, title="Ingredients", loc="center left", bbox_to_anchor=(1, 0, 0.5, 1))

plt.setp(autotexts, size=8, weight="bold")

ax.set_title("Matplotlib bakery: A pie")

plt.show()
```

{% endtab %}
{% endtabs %}

### Heatmap

{% tabs %}
{% tab title='python' %}

![heatmap](images/20210614_090651.png)
![confusion_matrix](images/20210614_085541.png)

```py
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.metrics import plot_confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC

np.random.seed(0)
sns.set_theme()

# 1. heatmap
uniform_data = np.random.rand(10, 12)
ax = sns.heatmap(uniform_data, annot=True)

# 2. Confusion matrix
X, y = make_classification(random_state=0)
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
clf = SVC(random_state=0)
clf.fit(X_train, y_train)
SVC(random_state=0)
plot_confusion_matrix(clf, X_test, y_test)
plt.show()
```

{% endtab %}
{% endtabs %}

## Scatter

{% tabs %}
{% tab title='python' %}

![Scatter](images/20210614_083117.png)

```py
import matplotlib.pyplot as plt
import numpy as np

# Fixing random state for reproducibility
np.random.seed(19680801)


x = np.arange(0.0, 50.0, 2.0)
y = x ** 1.3 + np.random.rand(*x.shape) * 30.0
s = np.random.rand(*x.shape) * 800 + 500

plt.scatter(x, y, s, c="g", alpha=0.5, marker=r'$\clubsuit$', label="Luck")
plt.xlabel("Leprechauns")
plt.ylabel("Gold")
plt.legend(loc='upper left')
plt.show()
```

{% endtab %}
{% endtabs %}

## Image

{% tabs %}
{% tab title="python" %}

> Images

* copy() → np.ndarray
* cvtColor(img, type)
  * type: COLOR_BGR2RGB, COLOR_BGR2GRAY)
* imread(filename, parames)     np.ndarray: (IMREAD_COLOR/GRAYSCALE/UNCHANGED (PNG)
* imwrite(fn, img, params = N) → if Success: [IMWRITE_JPEG_QUALITY, 90] compression rate of 90
* CV_8U / S: np.uint8 /  np.int8
* CV_16U / S / F: np.uint16 / np.int16 /  np.float16
* CV_8UC1 / CV_8UC3: np.uint8, shape (h, w) (Grey scale video) / (h, w, 3) (Color scale video)
* rectangle(img,(38,0),(51,12),(0,255,0),3)
  * image, top_left, bottom_right, color, thickness

* sobel(src, ddepth, dx, dy, ksize): first, second, third, or mixed image derivatives
* cv.blur(src, ksize, dst, anchor, borderType): blurs image using box filter

```py
import cv2
import numpy as np
import fire
import math
import glob
import itertools
import matplotlib.pyplot as plt

def slide_show():
  img = np.zeros((255, 255, 3))
  cv2.line(img, (0, 0), (255, 255), (0, 0, 255), 10)
  cv2.rectangle(img, (10, 10), (50, 50), 5)
  cv2.circle(img, (100, 100), 10, (1, 255, 1), -1)
  cv2.putText(img, 'OpenCv', (10, 200), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 255), 10, cv2.LINE_AA)

  imgs = [img] + [cv2.imread(f) for f in glob.glob('data/*.jpg')]

  # cv2.setWindowProperty("slides", cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
  i, mx = 0, len(imgs)
  while True:
    cv2.imshow("slides", imgs[i])
    try:
      for (p, c) in zip(cv2.split(imgs[i]), ['b', 'g', 'r']):
        hist = cv2.calcHist([p], [0], None, [256], [0, 256])
        plt.plot(hist, color=c)
    except:
      pass
    key = cv2.waitKey(-1)
    if key == 123:
      i = (i + mx - 1) % mx
    elif key == 124:
      i = (i + 1) % mx
    elif key == ord('b'):
      imgs[i] = cv2.add(imgs[i], (50, 50, 50, 0))
    elif key == ord('d'):
      imgs[i] = cv2.add(imgs[i], (-50, -50, -50, 0))
    elif key == ord('q'):
      break

def combine():
  messi = cv2.imread('data/combine/messi.jpg')
  b, g, r = cv2.split(messi)
  messi = cv2.merge((r, g, b))
  ball = messi[290:340, 340:390]
  messi[0:50, 0:50] = ball

  logo = cv2.imread('data/combine/logo.png')
  logo = cv2.resize(logo, (messi.shape[1], messi.shape[0]))
  combined = cv2.addWeighted(messi, .9, logo, .1, 2)

  plane_bg = cv2.imread('data/combine/airplane.bmp')
  mask = cv2.imread('data/combine/mask_plane.bmp')
  field = cv2.imread('data/combine/field.bmp')
  plane = cv2.copyTo(plane_bg, mask)
  field[mask > 0] = plane_bg[mask > 0]

  imgs = [messi, logo, combined, plane, field]

  i, mx = 0, len(imgs)
  while True:
    cv2.imshow("slides", imgs[i])
    key = cv2.waitKey(-1)
    if key == 123:
      i = (i + mx - 1) % mx
    elif key == 124:
      i = (i + 1) % mx
    elif key == ord('q'):
      break
```

{% endtab %}
{% endtabs %}

## Video

{% tabs %}
{% tab title='cpp' %}

```cpp
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

// 1. image
Mat frame = imread("lena.png"), gray, hsv, yCrCb, luv, bgra;
imshow("frame", frame);
cvtColor(frame, gray, COLOR_BGR2GRAY);
imshow("gray", gray);
cvtColor(frame, bgra, COLOR_BGR2BGRA);
imshow("gray", bgra);
waitKey();

// 2. video
VideoCapture cap(0);
if (!cap.isOpened()) return -1;

namedWindow("Video", 1);
while (true) {
  Mat frame;
  cap >> frame;
  imshow("Video", frame);
  if (waitKey(30) >= 0) break;
}

// 3. Video IO
cout << "Built with OpenCV " << CV_VERSION << endl;
Mat image;
Mat src;
VideoCapture capture;
capture.open(0);
capture >> src;
bool isColor = (src.type() == CV_8UC3);
VideoWriter writer;
int codec = VideoWriter::fourcc('M', 'P', '4', 'V');
double fps = 15.0;
string filename = "live.mp4";
Size sizeFrame(640, 480);
writer.open(filename, codec, fps, sizeFrame, isColor);
cout << "Started writing video... " << endl;
for (int i = 0; i < 60; i++) {
  capture >> image;
  Mat xframe;
  resize(image, xframe, sizeFrame);
  writer.write(xframe);
  imshow("Sample", image);
  char c = (char)waitKey(1);
  if (c == 27) break;
}
cout << "Write complete !" << endl;
capture.release();
writer.release();
return 0;
}
```

{% endtab %}
{% tab title='python' %}

```py
from IPython.display import Video, HTML, YouTubeVideo, FileLink
import numpy as np
from PIL import Image, ImageDraw
import cv2
import fire

# 1. Youtube / Vimeo / Local on jupyter
HTML('<iframe width="560" height="315" src="https://youtube.com/embed/S_f2qV2_U00?rel=0&amp;controls=0&amp;showinfo=0" \
  frameborder="0" allowfullscreen></iframe>')
YouTubeVideo('nC3QfNiudQ4')

HTML('<iframe src="https://player.vimeo.com/video/26763844?title=0&byline=0&portrait=0" width="700" height="394" \
  frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe><p> \
   <a href="https://vimeo.com/26763844">BAXTER DURY - CLAIRE (Dir Cut)</a> from \
   <a href="https://vimeo.com/dannysangra">Danny Sangra</a> on <a href="https://vimeo.com">Vimeo</a>.</p>')

FileLinks('.')     # See all file links in current directory
Video("test.mp4")  # embed=True if No video with supported format or MIME type found
HTML("""
<video width="320" height="240" controls>
  <source src="path/to/your.mp4" type="video/mp4">
</video>
""")

# 2. convert to video
videodims = (100,100)
fourcc = cv2.VideoWriter_fourcc(*'avc1')
video = cv2.VideoWriter("test.mp4",fourcc, 60,videodims)
img = Image.new('RGB', videodims, color = 'darkred')
for i in range(0, 60 * 60):  # draw stuff that goes on every frame here
  imtemp = img.copy()
  video.write(cv2.cvtColor(np.array(imtemp), cv2.COLOR_RGB2BGR))
video.release()

# 3. Video info
def check_video(path):
  cap = cv2.VideoCapture(path)
  frame = cap.get(cv2.CAP_PROP_FRAME_COUNT)
  fps = cap.get(cv2.CAP_PROP_FPS)
  length = -1 if fps == 0 else frame / fps
  width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
  height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
  print(f"FRAME \t {frame}")
  print(f"FPS \t {fps}")
  print(f"LENGTH \t {length}")
  print(f"SIZE \t {width} x {height}")


# 4. Display video
def open_video(path):
  cap = cv2.VideoCapture(path)

  while cap.isOpened():
    _, frame = cap.read()
    cv2.imshow('frame', frame)
    key = cv2.waitKey(1)
    if key == ord('q'):
      break

# 5. Capture video
def capture_video():
  cap = cv2.VideoCapture(0)

  print(f'HEIGHT \t {cap.get(cv2.CAP_PROP_FRAME_HEIGHT)}')
  print(f'WIDTH \t {cap.get(cv2.CAP_PROP_FRAME_WIDTH)}')
  while cap.isOpened():
    _, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cv2.imshow('frame', frame)

    key = cv2.waitKey(1)
    if key == ord('q'):
      break
    elif key == ord('s'):
      cv2.imwrite('data/result/capture.jpg', frame)
    elif key == ord('g'):
      cv2.imwrite('data/result/capture.jpg', gray)

  cap.release()
  cv2.destroyAllWindows()
```

{% endtab %}
{% endtabs %}

{% tabs %}
{% tab title='google' %}

* [Speed Control](
  https://chrome.google.com/webstore/detail/video-speed-controller/nffaoalbilbmmfgbnbgppjihopabppdk/related?hl=en)

{% endtab %}
{% endtabs %}

### Audio

{% tabs %}
{% tab title='python' %}

```py
from IPython.display import Audio  # create Audio objcet with local mp3 file.
audio = Audio(filename='./test.mp3')
display(audio)
```

{% endtab %}
{% endtabs %}

### Text EDA

{% tabs %}
{% tab title='python' %}

```py
from sklearn.manifold import TSNE
import matplotlib.pyplot as plt
word_10d = np.random.random((10, 10))

tsne_model = TSNE()
word_2d = tsne_model.fit_transform(word_10d)
for i, (x, y) in enumerate(word_2d):
  plt.scatter(x, y)
  plt.annotate(i, xy=(x, y), ha='right', va='bottom')
```

{% endtab %}
{% endtabs %}
