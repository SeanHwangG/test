# Video

> Term

* Adaptive bitrate stream: method of video streaming over HTTP where source content is encoded at multiple bit rates
* Container: metafile is a file format that allows multiple data streams to be embedded into a single file
  * mp4, avi
* Codec: Coder + Decoder
  * h264 (avc): Most commonly used, better bitrate than h263
  * h265 (hevc): high efficiency video coding
    * [+] Better image quality
    * [-] Triple resources to encode, not widely supported
  * vp9: royalty-free / open source by google
    * [+] More consistent and reliable
    * [-] Difficult to encode, not widely supported
* Format
  * mp4: mp4 container (part 14), ISO Base media file (part 12), H264 codec (part 10)
  * hls

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

> Example

{% link 'video_player' %}

> Reference

<https://en.wikipedia.org/wiki/Comparison_of_video_container_formats>

## Codec Video

* Software or hardware that compresses and decompresses digital video

> Term

* FourCC: Sequence of 4bytes used to identify data formats
  * DIVX
  * XVID
  * H264: Advanced Video Coding, supported by AVI, MKV, MP4
  * YV12: NxM U plane followed by (N/2)x(M/2) V and U planes, many MPEG codecs
  * YV16: YV12 with higher chroma resolution, comprises NxM Y plane (N/2)x(M/2) U and V planes
* Video Coding format (compression): Content representation format for storage or transmission of digital video content
  * Each specification (H.264), there can be many codecs implementing that specification (x264, OpenH264)
  * MJPEG: in 1992 ([ex] QuickTime)
  * Advanced Video Coding (H.264 / MPEG-4 AVC): in 2003, most marketshare ([ex] Blue Ray, Video Streaming)
  * High Efficiency Video Coding (H.265 / MPEG-H HEVC): in 2013 ([ex] UHD streaming)
  * Apple ProRes

> Example

* VP8: open and royalty-free video compression format created by On2 Technologies as successor to VP7
  * owned by Google from 2010
* VP9: successor to VP8 and competes mainly with MPEG's High Efficiency Video Coding (HEVC/H.265)
  * Support is common among modern web browsers, Android (Kitkat), iOS (v14)

{% tabs %}
{% tab title='cpp' %}

* VideoWriter
  * int fourcc(`codec`): [ex] \*'DIVX', \*'MJPG', \*'vp09'
* video.open(`file`, `codec`, `fps`, `Size`)

{% endtab %}
{% endtabs %}

> Reference

<https://fourcc.org/codecs.php>

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

## Streaming Video

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

* Kinesis Video Streaming: Flexible SDK for integration with on-device hardware media pipelines with AWS Integration
  * ![Kinesis Video Streaming](images/20210727_233303.png)
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

{% endtab %}
{% endtabs %}

> Reference

<https://www.youtube.com/watch?v=mrLsGq0HFVk>

## Tracking

| Term                                                          | Meaning                                |
| ------------------------------------------------------------- | -------------------------------------- |
| $$ \varphi(t) $$                                              | Finite number of parameters            |
| $$ \hat\varphi(t) $$                                          | Dynamic                                |
| $$ \varphi_p(t + 1) $$                                        | Estimate using parameters and dynamics |
| $$ \varphi_{c}(t+1)=f\left(\varphi_{p}(t+1), M(t+1)\right) $$ | Correction update the state            |

* [MOT](https://motchallenge.net/results/MOT17)

> Example

* SFM: Given two or more images or video without any information on camera position/motions as input
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
