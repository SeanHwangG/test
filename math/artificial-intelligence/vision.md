# Vision

* Extracting descriptions of the world from pictures or sequences of pictures
* ambiguous Interpretations: Changing viewpoint, moving light source, deforming the shape
* forward (graphics) well-posed, inverse (vision)
* Should computer vision follow from our understanding of human vision?

* How to solve
  * craft a solution using established methods and tailor them
  * build a math/physical model of the problem and implement algorithms with provably correct properties
  * gather image data, label it, and use machine learning to provide the solution

> Terms

* Calibration: With P1, ..., Pn with known 3D position and pixel coordinates q1, ..., qn, find K and $$ { }_{w}^{c} T $$

* Throughput: count / second
* Non maximal suppression
  ![Non Maximal Suppresion](images/20210213_232105.png)

* background substitution: subtract from previous frame

* Noise: Impulsive noise randomly pick a pixel and randomly set to a value
  * saturated version is called salt and pepper noise
  * Median filters - completely discard the spike, linear filter always responds to all aspects
  * Quantization effects - often called noise although it is not statistical
  * Unanticipated image structures - also often called noise although it is a real repeatable signal

* Eight point algorithm
  * Set $$ E_33 $$ to 0 and use 8 points to calculate $$ E_11 $$, $$ E_32 $$

$$
[u, v, 1]\left[\begin{array}{ccc}
E_{11} & E_{12} & E_{13} \\
E_{21} & E_{22} & E_{23} \\
E_{31} & E_{32} & E_{33}
\end{array}\right]\left[\begin{array}{c}
u^{\prime} \\
v^{\prime} \\
1
\end{array}\right]=0
$$

* Perspective: distant objects appear smaller than nearer objects
  * lines parallel in nature meet at the point at infinity
  * Most realistic because it’s the same way as photographic lenses and the human eye works
  * 1/2/3-point, based on the orientation of the projection plane towards the axes of the depicted object

![strong, weak perspective](images/20210322_214730.png)

* Projective geometry: provides an elegant means for handling these different situations in a unified way

* Point at Infinity: Where w is 0, with homogeneous coordinates

* Projective plane
  * = Euclidean plane ∪ Line at Infinity

{% tabs %}
{% tab title='python' %}

```py
# 1. Non maximal supression
while select bounding box with some threshold
  discard any remaining box with IoU >= 0.5 with the box output in previous step
```

{% endtab %}
{% endtabs %}

{% tabs %}
{% tab title='amazon' %}

![Amazon Sagemaker](images/20210728_010545.png)

{% endtab %}
{% endtabs %}

## Autmonomous vehicle

* Driving task: Perceiving the environment, Planning how to reach from point A to B
* Controlling the vehicle: Operational Design Domain / Environmental, Time of day

* Lateral Control steering
* Longitudinal control braking accelerating
* Object and Event Detection and Response detection, reaction
* Inertial measurement unit
  * Measures a vehicle’s three linear acceleration and rotational rate components

* Level of automation
    1. Assistance either, but not both longitudinal control or lateral (e.g. cruise, lane keeping)
    2. Both longitudinal control and lateral
    3. Includes automated object and event detection and response. Alert in case of failure
    4. Can handle emergencies autonomously
    5. Unlimited ODD

* Perception
  * Static objects
  * Dynamic objects
  * Ego localization

* Planning
  * Predictive: Make predictions about other vehicles and how they are moving
  * Rule based: Take into account the current state of ego and other objects and give decisions
  * Long term: How to navigate from NY to LA?
  * Short Term: Can I change my lane to lane right? Can I pass this intersection and join the left road?
  * Immediate: Accelerate, brake

## Visual Feature

* Harris: large difference with nearby pixel
* Good Features to Track: sorted by value, suppress non-max
* FAST: use nearby 16 pixels, fast than above two
* SIFT: Shi-Tomasi Corner Detector takes (Gaussian std, window size, threshold)
  * [+] Translation, scale, rotation-invariant
  * [-] strong illumination changes, Large out-of-plane rotations
  * [-] non-rigid deformations or articulations semantic correspondence
  * [ex] Panorama, stitching, 3D reconstruct, motion track, object recognition, DB indexing retrieval, robot navigation

* Feature Pyramid
  ![Feature Pyramid](images/20210213_232138.png)

* Anchor: object is assigned to grid cell that contains object's midpoint, anchor box for grid cell with highest IoU
  ![Anchor](images/20210213_232016.png)
  ![Anchor example](images/20210213_231959.png)

* CNN: Pixel depend on nearby pixels(locality): small receptive fields
  * Statistics of visual inputs are invariant across image: replicate receptive fields across images
  * Objects don't change based on location: translation invariance, spatial pooling
  * Objects are made of parts: get larger in the net
  * convolutional layer of replicated feature maps
  * Depth allows features of features to be learned which tend to get more abstract in deeper layers
  * Deeper networks are better as long as they allow the gradient to pass backwards easily
  * Reuse a pre-trained network and then add a softmax for categorization or logistic units for tagging
  $$
  W_{\text {out }}=\text { floor }(\frac{W_{\text {in }}+2 \times \text { padding }-\text { dilation } \times(k-1)-1}{\text{stride}})+1
  $$

* Mixture of Gaussian (improved adaptive gaussian mixture model for background subtraction, 2004)
  * Moving average
  * Save memory
    * $$ \alpha $$ weight for current frame (0.01)
  $$ B(x, y, t)=\alpha \cdot I(x, y, t)+(1-\alpha) \cdot B(x, y, t-1) $$

* viola-jones algorithm (Paul Viola and Michael Jones, 2001)
  * trained to detect a variety of object classes, it was motivated primarily by the problem of face detection
  * [+] robust: high detection rate (true-positive rate) & low false-positive rate always
  * [+] Real time: For practical applications at least 2 frames per second must be processed
  * Face detection only (not recognition) - The goal is to distinguish faces from non-faces

* haar-like features (Rapid Object Detection using a Boosted Cascade of Simple Features, 2001)
  * edge features, line features, four-rectangle features
  * uses integral of image and adaboost (Cascade of Classifiers) for faster computation
  1. Haar Feature Selection (eye, nose)
  1. Creating an Integral Image
  1. Adaboost Training
  1. Cascading Classifiers

* integral: integral image enables you to rapidly calculate summations over image subregions
  ![Integral](images/20210213_231506.png)

{% tabs %}
{% tab title='cpp' %}

```cpp
#include "opencv2/gapi.hpp"
#include "opencv2/gapi/core.hpp"
#include "opencv2/gapi/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  /* without compile
  cv::VideoCapture cap;
  CV_Assert(cap.isOpened());
  // BODY OF COMP
  cv::GComputation ac(in_frame, out_frame);
  cv::Mat input_frame;
  cv::Mat output_frame;
  CV_Assert(cap.read(input_frame));
  do {
    ac.apply(input_frame, output_frame);
    cv::imshow("output", output_frame);
  } while (cap.read(input_frame) && cv::waitKey(30) < 0);
  */
  cv::VideoCapture cap("/Users/sean/github/LEARN_C/opencv/data/complex_scene_01.mp4");
  cv::GComputation comp([]() {
    cv::GMat in_frame;
    cv::GMat vga = cv::gapi::resize(in_frame, cv::Size(), 0.5, 0.5);
    cv::GMat gray = cv::gapi::BGR2Gray(vga);
    cv::GMat blurred = cv::gapi::blur(gray, cv::Size(5, 5));
    cv::GMat edges = cv::gapi::Canny(blurred, 32, 128, 3);
    cv::GMat b, g, r;
    tie(b, g, r) = cv::gapi::split3(vga);
    cv::GMat out_frame = cv::gapi::merge3(b, g | edges, r);
    return cv::GComputation(cv::GIn(in_frame), cv::GOut(out_frame));
  });
  int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
  int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
  cv::Mat in_frame(height, width, CV_8UC3);  // dimension required for compile
  cv::Mat blur_frame;
  auto exec = comp.compile(cv::descr_of(in_frame));
  CV_Assert(cap.read(in_frame));
  do {
    exec(cv::gin(in_frame), cv::gout(blur_frame));
    cv::imshow("output", blur_frame);
  } while (cap.read(in_frame) && cv::waitKey(30) < 0);
  return 0;
}
```

{% endtab %}
{% endtabs %}

### Coresspondence

> Question

* ambiguity (2-1 matching), multiple interpretation
* Half occluded image
  ![Half occluded image](images/20210721_132752.png)
* Window shape
  ![Window Shape](images/20210721_132729.png)

* What does random dot stereogram tell us about the human visual system
  * Human visual feature doesn't do traditional feature based matching but dense area matching to identify objects
* Rank, census, Sum of Absolute difference, zero mean SAD

> Term

* Feature-based: process each image monocularly to detect image features (corners or SIFT)
* Area-based: Directly compare image regions between the two images
* Normalized cross correlation
  * $$ \overline{W_{i}}=\frac{1}{n} ∑_{x, y} W_{i} $$
  * $$ \quad \sigma_{W_{i}}=\sqrt{\frac{1}{n} ∑_{x, y}(W_{i}-\overline{W_{i}})^{2}} $$
  * $$ \frac{\sum_{x, y}(W_{1}(x, y)-\bar{W}_{1})(W_{2}(x, y)-\bar{W}_{2})}{δW_{1} \cdot δW_{2}} $$
* Sum of squared distance
  * $$ \sum_{x=y}|W_{1}(x, y)-W_{2}(x, y)|^{2} $$

{% tabs %}
{% tab title='python' %}

```py
# O(nrows, * ncols * disparities * winx * winy)
for i in range(1, nrows):
  for j in range(1, ncols):
    best(i, j) = -1
    for k in range(min_disparity, max_disparity):
      c = Match_Metric(I1, (i, j), I2(i, j + k), winsize)
      if c > best(i, j):
        best(i, j) = c
        disparities(i, j) = k
```

{% endtab %}
{% endtabs %}

## Epipolar

![Epipolar](images/20210214_020403.png)

* Baseline: line connecting two center of projection O and O'
* Epipoles (e, e'): Two intersection points of baseline with image planes
* Epipolar plane: Any plain that contains the baseline
* Epipolar lines: Pair of lines from intersection of an epipolar plane with two image plane

## Colors

![Color](images/20210210_184754.png)

* gray: 0 Black - 255 White
  * 1Byte → unsigned char in c++, numpy.uint8 in python

* HSL, HSV

* YUV 4:2:0: requires 4×8+8+8=48 bits per 4 pixels, so its depth is 12 bits per pixel
  * I420 is by far the most common format in VLC

* NV12: commonly found as the native format from various machine vision, and other, video cameras
  * another variant where colour information is stored at a lower resolution than the intensity data
  * intensity (Y) data is stored as 8 bit samples, and colour (Cr, Cb) information as 2x2 subsampled image, known as 4:2:0

* I420: identical to YV12 except that the U and V plane order is reversed

## Object Classification

* [Coco](https://gist.github.com/50e1deaec61bbd28b60bb96cb10ab74d)
  * 80 labels (people, bicycles, cars and trucks, airplanes, stop signs and fire hydrants, animals, kitchens)
  * object detection, segmentation

{% include '.object-classification.prob' %}

## Eye

* 1604 Kepler eye as an optical instrument, which image is inverted on retina
* 1625 Scheiner experimented by this idea

* Color is precieved differently by
  * previously seen color
  * neighborhood colors
  * state of mind

* Camera vs Eye
  ![Camera vs Eye](images/20210210_185040.png)

| Camera        | Human              |
| ------------- | ------------------ |
| curved retina | wide range of view |
| hard lense    | soft lense         |

![Eye](images/20210210_185112.png)

| rods                   | cones           |
| ---------------------- | --------------- |
| night (a lot of light) | day             |
| many                   | few             |
| one                    | three(color)    |
| low resolution         | high resolution |

## Motion

| Term                       | Meaning                 |
| -------------------------- | ----------------------- |
| p                          | $$ (x, y, z)^{T} $$     |
| T                          | Velocity vector         |
| w                          | Angular velocity vector |
| $$ \hat{p}=T+w \times p $$ | General Motion          |
| $$ ({u}, {v}) $$           | image point coordinate  |
| $$ (\hat{u}, \hat{v}) $$   | image point velocity    |
| f                          | focal length            |
| d                          | depth                   |

$$ \dot{u}=\frac{T_{z} u-T_{x} f}{z}-\omega_{y} f+\omega_{z} v+\frac{\omega_{x} u v}{f}-\frac{\omega_{y} u^{2}}{f} $$
$$ \dot{v}=\frac{T_{z} v-T_{y} f}{z}+\omega_{x} f-\omega_{z} u-\frac{\omega_{y} u v}{f}-\frac{\omega_{x} v^{2}}{f} $$

> Term

* Bundle adjustment: sum of errors between the measured pixel coordinates uij and the re-projected pixel coordinates
  * optimized with non-linear least squares algorithm
  * w_{ij}: 1 if point i is visible in image j, and 0 otherwise
  $$
  g( P , R , T )=\sum_{i=1}^{M} \sum_{j=1}^{N} w_{i j}\|P(P_{i}, R_{j}, t_{j})-[\begin{array}{l}
  u_{i, j} \\
  v_{i, j}
  \end{array}]\|^{2}
  $$

## Object Recognition

* pose estimation / recognition / segmentation
* feature extraction → classification
* Challnges
  * pose variability (direction, color, shadow), lighting, occlusion
  * within-class variability (articulated, deformable, different shapes and patterns)

![FNMR vs FMR](images/20210518_193319.png)

* Photometric stereo: Multiple images, static scene, fixed viewpoint, multiple lighting conditions, correspondence trivial

{% tabs %}
{% tab title='amazon' %}

![AWS Structure](images/20210727_232931.png)

{% endtab %}
{% endtabs %}

> Reference

<https://medium.com/zenofai/real-time-face-identification-on-live-camera-feed-using-amazon-rekognition-video-and-kinesis-video-52b0a59e8a9>

### Pattern matching

{% tabs %}
{% tab title='cpp' %}

```cpp
#include <stdio.h>

#include <iostream>
#include <string>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

Mat img, templ, result;
string ORIG_WINDOW_NAME = "Source Image", RESULT_WINDOW_NAME = "Result window";

int match_method;
int max_Trackbar = 5;

void MatchingMethod(int, void *);

int main() {
  img = imread("/Users/sean/github/LEARN_C/opencv/data/mario.png", 1);
  templ = imread("/Users/sean/github/LEARN_C/opencv/data/coin.png", 1);

  namedWindow(ORIG_WINDOW_NAME, WINDOW_AUTOSIZE);
  namedWindow(RESULT_WINDOW_NAME, WINDOW_AUTOSIZE);

  string trackbar_label =
      "Method: \n 0: SQDIFF \n 1: SQDIFF NORM \n 2: TM CCORR \n 3: TM CCORR NORM \n 4: TM COEFF \n 5: TM COEFF NORM";
  createTrackbar(trackbar_label, ORIG_WINDOW_NAME, &match_method, max_Trackbar, MatchingMethod);

  MatchingMethod(0, 0);

  waitKey(0);
  return 0;
}

void MatchingMethod(int, void *) {
  Mat orig;
  img.copyTo(orig);

  result.create(img.cols - templ.cols + 1, img.rows - templ.rows + 1, CV_32FC1);

  matchTemplate(img, templ, result, match_method);
  normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

  double minVal, maxVal;
  Point minLoc, maxLoc, matchLoc;

  minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

  if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
    matchLoc = minLoc;
  else
    matchLoc = maxLoc;

  rectangle(orig, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
  rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);

  imshow(ORIG_WINDOW_NAME, orig);
  imshow(RESULT_WINDOW_NAME, result);

  return;
}
```

{% endtab %}
{% endtabs %}

### Tracking

| Term                                                          | Meaning                                |
| ------------------------------------------------------------- | -------------------------------------- |
| $$ \varphi(t) $$                                              | Finite number of parameters            |
| $$ \hat\varphi(t) $$                                          | Dynamic                                |
| $$ \varphi_p(t + 1) $$                                        | Estimate using parameters and dynamics |
| $$ \varphi_{c}(t+1)=f\left(\varphi_{p}(t+1), M(t+1)\right) $$ | Correction update the state            |

* [MOT](https://motchallenge.net/results/MOT17)

> SFM

* Given two or more images or video without any information on camera position/motions as input
* estimate camera motion and 3D structure of a scene
* Discrete motion (wide baseline)
* Continuous (Infinitesimal) motion usually from video

* 2 \* M \* N measurements
* 3 * N unknowns for points
* (M - 1) * 6 unknowns for cameras
  * Affix world coordinate system to location of first camera frame
  * 3 rotation, 3 translation
* Can only recover structure and motion up to scale factor (one fewer unknown)
* (M - 1) \* 6 + e \* N - 1 ≤ 2 \* M \* N (M = 2, N = 5 or M = 3, N = 4)

{% tabs %}
{% tab title='cpp' %}

```cpp
#include <opencv2/core/ocl.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

using namespace cv;
using namespace std;

#define SSTR(x) (ostringstream() << std::dec << x).str()

int main(int argc, char **argv) {
  string trackerTypes[8] = {"BOOSTING",   "MIL",    "KCF",   "TLD",
                            "MEDIANFLOW", "GOTURN", "MOSSE", "CSRT"};  // tracker types in 3.4.1
  string trackerType = trackerTypes[2];
  Ptr<Tracker> tracker;

  if (trackerType == "BOOSTING") tracker = TrackerBoosting::create();
  if (trackerType == "MIL") tracker = TrackerMIL::create();
  if (trackerType == "KCF") tracker = TrackerKCF::create();
  if (trackerType == "TLD") tracker = TrackerTLD::create();
  if (trackerType == "MEDIANFLOW") tracker = TrackerMedianFlow::create();
  if (trackerType == "GOTURN") tracker = TrackerGOTURN::create();
  if (trackerType == "MOSSE") tracker = TrackerMOSSE::create();
  if (trackerType == "CSRT") tracker = TrackerCSRT::create();
  VideoCapture video(0);

  if (!video.isOpened()) {
    cout << "Could not read video file" << endl;
    return 1;
  }

  Mat frame;
  bool ok = video.read(frame);

  Rect2d bbox(500, 100, 300, 320);

  // Uncomment the line below to select a different bounding box
  // bbox = selectROI(frame, false);
  rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);

  imshow("Tracking", frame);
  tracker->init(frame, bbox);

  while (video.read(frame)) {
    double timer = (double)getTickCount();
    bool ok = tracker->update(frame, bbox);
    float fps = getTickFrequency() / ((double)getTickCount() - timer);
    if (ok)
      rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
    else
      putText(frame, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);

    putText(frame, trackerType + " Tracker", Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);
    putText(frame, "FPS : " + SSTR(fps), Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);
    imshow("Tracking", frame);

    int k = waitKey(1);
    if (k == 27) break;
  }
}
```

{% endtab %}
{% tab title='python' %}

```py
import cv2
import sys

(major_ver, minor_ver, subminor_ver) = (cv2.__version__).split('.')

tracker_types = ['BOOSTING', 'MIL', 'KCF', 'TLD', 'MEDIANFLOW', 'GOTURN', 'MOSSE', 'CSRT']
tracker_type = tracker_types[2]

if tracker_type == 'BOOSTING':
  tracker = cv2.TrackerBoosting_create()
if tracker_type == 'MIL':
  tracker = cv2.TrackerMIL_create()
if tracker_type == 'KCF':
  tracker = cv2.TrackerKCF_create()
if tracker_type == 'TLD':
  tracker = cv2.TrackerTLD_create()
if tracker_type == 'MEDIANFLOW':
  tracker = cv2.TrackerMedianFlow_create()
if tracker_type == 'GOTURN':
  tracker = cv2.TrackerGOTURN_create()
if tracker_type == 'MOSSE':
  tracker = cv2.TrackerMOSSE_create()
if tracker_type == "CSRT":
  tracker = cv2.TrackerCSRT_create()

video = cv2.VideoCapture(0)
if not video.isOpened():
  print("Could not open video")
  sys.exit()

ok, frame = video.read()
if not ok:
  print('Cannot read video file')
  sys.exit()

# Define an initial bounding box
bbox = cv2.selectROI(frame, False)
ok = tracker.init(frame, bbox)  # Initialize tracker with first frame and bounding box

while True:
  ok, frame = video.read()
  if not ok:
    break

  timer = cv2.getTickCount()
  ok, bbox = tracker.update(frame)
  fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer)
  if ok:
    p1 = (int(bbox[0]), int(bbox[1]))
    p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
    cv2.rectangle(frame, p1, p2, (255, 0, 0), 2, 1)
  else:  # Tracking failure
    cv2.putText(frame, "Tracking failure detected", (100, 80), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (0, 0, 255), 2)

  cv2.putText(frame, tracker_type + " Tracker", (100, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50, 170, 50), 2)
  cv2.putText(frame, "FPS : " + str(int(fps)), (100, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50, 170, 50), 2)
  cv2.imshow("Tracking", frame)
  k = cv2.waitKey(1) & 0xff
  if k == 27:
    break
```

{% endtab %}
{% endtabs %}

## Processing

* Gaussian Smoothing
  $$ G_{\sigma}=\frac{1}{2 \pi \sigma^{2}} e^{-\frac{\left(x^{2}+y^{2}\right)}{2 \sigma^{2}}} $$

### Filtering

![Filter](images/20210309_010213.png)

* The most common filters are linear filters and the process of applying a linear filter is called convolution
* For convolution kernel is flipped over both axis unlike correlation
* Any linear, shift-invariant operator can be represented as a convolution

* Enhance images: Denoise, resize, increase contrast
* Extract information from images: Texture, edges, distinctive points, etc
* Detect pattern: template matching

* Blur
  ![Blur](images/20210527_163938.png)

* Sharpen
  ![Sharpen](images/20210527_163958.png)

* CNN: Convolutional Neural Networks Weights of the CNN are learned
  * Can be extended to RGB, Volumetric data such as MRI, CT

> Question

* Smoothing an image with an average filter and then convolving with a derivative filter will give better results
  than first convolving with a derivative filter and then smoothing with an average filter
  * False. Convolution is commutative, so it will give the same result

{% tabs %}
{% tab title='cpp' %}

```cpp
#include <chrono>
#include <iostream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
using namespace std::chrono;

// 1. Blur in parrallel
class ParallelProcess : public cv::ParallelLoopBody {
 private:
  cv::Mat img;
  cv::Mat &retVal;
  int size;
  int n_thread;

 public:
  ParallelProcess(cv::Mat inputImgage, cv::Mat &outImage, int size, int n_thread)
      : img(inputImgage), retVal(outImage), size(size), n_thread(n_thread) {}

  virtual void operator()(const cv::Range &range) const {
    for (int i = range.start; i < range.end; i++) {
      cv::Mat in(img, cv::Rect(0, (img.rows / n_thread) * i, img.cols, img.rows / n_thread));
      cv::Mat out(retVal, cv::Rect(0, (retVal.rows / n_thread) * i, retVal.cols, retVal.rows / n_thread));

      cv::medianBlur(in, out, size);
    }
  }
};

int main() {
  VideoCapture cap(0);

  cv::Mat img, out;

  for (int n_thead = 1; n_thead < 100; n_thead++) {
    auto start1 = high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
      cap.read(img);
      out = cv::Mat::zeros(img.size(), CV_8UC3);

      cv::parallel_for_(cv::Range(0, 8), Parallel_process(img, out, 31, 10));

      cv::imshow("blur", out);
      cv::waitKey(1);
    }
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout << "TBB Time: " << duration1.count() / 1000 << "ms" << endl;
  }

  return 0;
}
```

{% endtab %}
{% tab title="python" %}

```py
from collections import deque
from multiprocessing.pool import ThreadPool

import cv2

VIDEO_PATH = "/Users/sean/github/data/video"

def process_frame(frame):
  frame = cv2.medianBlur(frame, 19)
  return frame

cap = cv2.VideoCapture(f"{VIDEO_PATH}/sd_sample_03.mp4")
thread_num = cv2.getNumberOfCPUs()
pool = ThreadPool(processes=thread_num)
pending_task = deque()

while True:
  while len(pending_task) > 0 and pending_task[0].ready():
    res = pending_task.popleft().get()
    cv2.imshow('threaded video', res)

  if len(pending_task) < thread_num:
    frame_got, frame = cap.read()
    if frame_got:
      task = pool.apply_async(process_frame, (frame.copy(),))
      pending_task.append(task)

  if cv2.waitKey(1) == 27 or not frame_got:
    break

cv2.destroyAllWindows()
```

{% endtab %}
{% endtabs %}

## Segmentation

![semantic vs instance segmentation](images/20210210_190100.png)

* process of dividing an image into connected regions st pixels within a region share certain characteristics
* Boundaries or edges divide segmented regions
* Single short multibox detector: 74.3 mAP, 59 FPS

> Term

* tessellation: aka tiling of flat surface is covering of plane using 1+ tiles, with no overlaps and no gaps
  ![Tessellation](images/20210716_170218.png)
* Voroni Diagram: partition of a plane into regions close to each of a given set of objects
  ![20 points voronoi cells](images/20210716_170029.png)

> Solution

* Faster R-CNN: 73.2 mAP, 7 FPS
* Darknet: 19 convolutional layers and 5 maxpooling layers
* Tiny Yolo: 23.7mAP, 244FPS

### YOLO

![Yolo](images/20210210_190347.png)

* v1
  * 74.3mAP, 59FPS
  * 49 objects / Relatively high localization error

* v2: Classification and prediction in a single framework
  * Batch Normalization, Multi-scale training
  * classiﬁer network at 224×224, Increase in image size 448*448
  * divides into 13 * 13 grid cells → finegrand feature
  * Anchor boxes

* Yolo v3 (J Redmon, 2018)
  * 0 normalized 416 (320, 608) RGB input → [(507, 85), (2028, 85), (8112, 85)]

* mask-RCNN (Mask R-CNN, He 2017): Faster R-CNN + FCN

![Segmentation](images/20210210_190110.png)

{% tabs %}
{% tab title='cpp' %}

```cpp
// 1. Yolo
// terminate called after throwing an instance of 'std::logic_error'
//   what():  Computation's output protocol doesn't match actual arguments!
// Aborted (core dumped)
// -> output format doesn't match in exec
cv::GComputation comp([ot]() {
  cv::GMat in_frame;
  cv::GMat detections = cv::gapi::infer<custom::Objects>(in_frame);
  cv::GArray<pz::DetectedObject> detected_objects = custom::Yolov2PostProc::on(detections, in_frame, in_is_tiny);
  cv::GArray<vas::ot::Object> tracked_objects = custom::vas_ot::on(ot, in_frame, detected_objects);
  cv::GMat out_frame = cv::gapi::copy(in_frame);
  return cv::GComputation(cv::GIn(in_frame, in_is_tiny), cv::GOut(out_frame, tracked_objects));
});
auto exec = comp.compile(cv::descr_of(in_frame), cv::descr_of(is_tiny), cv::compile_args(kernels, networks));
exec(cv::gin(in_frame), cv::gout(out_frame));

// what():  OpenCV(4.3.0-openvino-2020.3.0) ~/intel/openvino/opencv/include/opencv2/gapi/garray.hpp:227:
// error: (-215:Assertion failed) sizeof(T) == m_ref->m_elemSize in function 'check'
// -> output format doesn't match
cv::GComputation comp([ot]() {
  cv::GMat in_frame;
  cv::GArray<vas::ot::Object> tracked_objects = custom::vas_ot::on(ot, in_frame, detected_objects);
  return cv::GComputation(cv::GIn(in_frame, in_is_tiny), cv::GOut(out_frame, tracked_objects));
});
auto exec = comp.compile(cv::descr_of(in_frame), cv::descr_of(is_tiny), cv::compile_args(kernels, networks));
std::vector<int> ints;
exec(cv::gin(in_frame), cv::gout(out_frame, ints));

// terminate called after throwing an instance of 'std::logic_error'
//  what():  Computation output 2 is not a result of any operation
// Aborted (core dumped)
// -> output foramt doesn't match
```

{% endtab %}
{% endtabs %}

## Stereo

* extraction of 3D information from digital images, such as those obtained by a CCD camera

> Term

* 1-D Epipolar Search: Arbitrary images of same scene may be rectified based on epipolar geometry
  * s.t. stereo matches lie along one-dimensional scanlines
  * This reduces computational complexity and also reduces the likelihood of false matches

* Monotonic Ordering: Points along an epipolar scanline appear in the same order in both stereo images
  * assuming that all objects in the scene are approximately the same distance from the cameras

* Image Brightness Constancy: Assuming Lambertian surfaces, brightness of corresponding points in stereo images are same

* Match Uniqueness: For every point in one stereo image, there is at most one corresponding point in the other image
* Disparity Continuity: Disparities vary smoothly (disparity gradient is small) over most of the image
  * This assumption is violated at object boundaries
* Disparity Limit: search space may be reduced significantly by limiting the disparity range
  * reducing both computational complexity and the likelihood of false matches
* Fronto-Parallel Surfaces: implicit assumption made by area-based matching is that objects have front-parallel surfaces
  * depth is constant within the region of local support). This assumption is violated by sloping and creased surfaces
* Feature Similarity: Corresponding features must be similar (edges must have roughly the same length and orientation)
* Structural Grouping: Corresponding feature groupings and their connectivity must be consistent

## Video Streaming

* Lossy count algorithm: Identify elements in a data stream whose frequency count exceed a threshold (ranking)
  * Step 1: Divide incoming data stream into buckets of width  w = 1 / e, where e is mentioned by user as error bound
    * along with minimum support threshold = σ
  * Step 2: Increment the frequency count of each item according to the new bucket values
    * After each bucket, decrement all counters by 1
  * Step 3: Repeat – Update counters and after each bucket, decrement all counters by 1

* Challenges
  * Cumbersome to rewrite code for various devices and development environments
  * Elastically scale to millions of devices
  * Reliable support for cadence, latency, jitter on stream
  * Secure streaming and storage
  * Easy to use APIs to retriev, replace, and process video

{% tabs %}
{% tab title='amazon' %}

* Kinesis Video Streaming
  * Flexible SDK for integration with on-device hardware media pipelines with AWS Integration
  * Handle streaming Put API to stream continuously in a reliable manner
  * Add metadata to video fragments applied by the device directly
  * Methods
    * CreateStream / DeleteStream / DescribeStream / ListStreams:
    * UpdateDataRetention: Increase or decreases the stream's data retention period
    * UpdateStream: Update data medata
    * GetDataEndpoint: Get endpoint for a specified stream for either reading / writing
    * PutMedia: Long-running streaming API to write media data to a video stream
    * GetMedia: Retrieve media content from a video stream
    * GetMediaFroFragmentList: retrieve media data for a list of fragments from the video stream
    * ListFragments: Returns list of Fragments from the specified video stream and start location
    * GetHLSSStreamingSessionURLMedia: Retrieve an HTTP Live Streaming URL for the stream
  * Kinesis Video Streams Parser Library: Open source java that makes easy to work with GetMedia Output
    * Get frame-level object and its associated metadata
    * Extract and apply video fragment-specific metadata
    * Merge consecutive fragments, decode media to JPEG/PNG
    * Build into your custom ML or other video-processing applications
    * Scale to process 1000's of streams concurrently
  * Kinesis Video Streams Inference Template (KIT): Sample, parse, decode invoke sagemaker real-time

![Kinesis Video Streaming](images/20210727_233303.png)

{% endtab %}
{% endtabs %}

> Reference

<https://www.youtube.com/watch?v=mrLsGq0HFVk>

## Upsampling

{% include '.upsampling.prob' %}
