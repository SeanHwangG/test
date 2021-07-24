#include <execution>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "image.h"
#include "opencv2/opencv.hpp"
#include "prof.h"

using namespace std;
using namespace cv;
using namespace std::filesystem;

void worker(vector<cv::Mat>::iterator start, vector<cv::Mat>::iterator end) {
    ofstream fs;
    ostringstream ss;

    ss << this_thread::get_id();
    string idstr = ss.str();
    VideoWriter video(idstr + ".avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10,
                      Size(start->cols, start->rows));
    for (auto itr = start; itr < end; ++itr) {
        cv::Mat edge;
        auto img = *itr;
        Canny(img, edge, 0.1, 0.2, 5);
        video.write(edge);
    }
    fs.close();
}

int main() {
    cv::VideoCapture cap("data/video.mp4");
    vector<cv::Mat> frames;
    while (1) {
        cv::Mat frame;
        cap >> frame;
        frames.push_back(frame);
        if (frame.empty()) break;
    }

    vector<thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(thread(worker, frames.begin() + i * 10, frames.begin() + (i + 1) * 10));
    }

    PROF_START();
    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }
    PROF_END();
}