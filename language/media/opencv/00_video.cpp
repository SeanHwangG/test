#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void reverse_video() {
  VideoCapture cap("data/short.mov");

  double frame_rate = cap.get(CAP_PROP_FPS);
  double frame_msec = 1000 / frame_rate;
  cap.set(CAP_PROP_POS_AVI_RATIO, 1);

  double video_time = cap.get(CAP_PROP_POS_MSEC);

  Mat frame;
  namedWindow("window");

  while (video_time > 0) {
    video_time -= frame_msec;
    cap.set(CAP_PROP_POS_MSEC, video_time);
    cap >> frame;
    imshow("window", frame);
    if (waitKey(frame_msec) >= 0) break;
  }
}
void infinite_loop() {
  VideoCapture cap("data/short.mov");
  Mat frame;
  namedWindow("window");

  double frame_rate = cap.get(CAP_PROP_FPS);
  cap.set(CAP_PROP_POS_AVI_RATIO, 1);
  double video_time = cap.get(CAP_PROP_POS_MSEC);
  cap.set(CAP_PROP_POS_AVI_RATIO, 0);
  cout << frame_rate << endl;
  cout << video_time << endl;
  int i = 0;

  while (true) {
    i = i + 1;
    cap.set(CAP_PROP_POS_MSEC, i);
    cap >> frame;
    imshow("window", frame);
    waitKey(10);
  }
}

int main() {
  infinite_loop();
  reverse_video();
}
