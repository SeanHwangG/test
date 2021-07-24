#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap("data/sample.mov");
    Mat bird = imread("data/bird.png"), result;
    double minVal, maxVal;
    Point minLoc, maxLoc;

    while (1)
    {
        Mat frame;
        cap >> frame;

        if (frame.empty())
            break;

        /*
        matchTemplate(bird, frame, result, TM_SQDIFF);
        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

        rectangle(frame, Point(minLoc.x, minLoc.y), Point(maxLoc.x, maxLoc.y), 2);
        */
        imshow("Frame", frame);
        auto key = waitKey(1);
        if (key == 27)
            break;
        else if (key == 's')
            imwrite("data/capture.png", frame);
    }

    cap.release();
    destroyAllWindows();

    return 0;
}