#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main() {
  VideoCapture cap("/Users/sean/github/LEARN_C/opencv/data/crowd.mp4");

  Mat bgra;
  Mat bgr;

  while (true) {
    cap >> bgr;
    cout << bgra.type();

    Mat bgra = Mat(bgr, cv::COLOR_BGR2BGRA);
    imshow("video", bgra);
    if (waitKey(1) >= 0) break;
  }
}