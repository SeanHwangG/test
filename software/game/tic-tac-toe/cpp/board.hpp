#pragma once

#include <functional>
#include <map>
#include <string>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

function<void(int event, int r, int c)> callback;

class Board {
 public:
  static void onMouseClick(int event, int r, int c, int flags, void *) { callback(event, r, c); }

  int grid[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  int SIZE;
  Mat board;

  Board(int SIZE) : SIZE(SIZE) {
    namedWindow("board");
    board = Mat::zeros(SIZE, SIZE, CV_8UC3);
    setMouseCallback("board", onMouseClick, &board);

    line(board, Point(0, SIZE / 3), Point(SIZE, SIZE / 3), LINE_CLR, 2);
    line(board, Point(0, SIZE * 2 / 3), Point(SIZE, SIZE * 2 / 3), LINE_CLR, 2);
    line(board, Point(SIZE / 3, 0), Point(SIZE / 3, SIZE), LINE_CLR, 2);
    line(board, Point(SIZE * 2 / 3, 0), Point(SIZE * 2 / 3, SIZE), LINE_CLR, 2);
  }

  void draw(string message) {
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++) {
        if (grid[r][c] == 1)
          circle(board, Point(SIZE * r / 3 + SIZE / 6, SIZE * c / 3 + SIZE / 6), SIZE / 6, Scalar(255, 0, 0), -1);
        else if (grid[r][c] == 2)
          circle(board, Point(SIZE * r / 3 + SIZE / 6, SIZE * c / 3 + SIZE / 6), SIZE / 6, Scalar(0, 255, 0), -1);
      }

    putText(board, message, Point(SIZE / 2, SIZE / 2), 2, 2, TEXT_CLR);
    imshow("board", board);
  }

 private:
  const Scalar BG_CLR = Scalar(0, 0, 0);
  const Scalar TEXT_CLR = Scalar(255, 255, 255);
  const Scalar LINE_CLR = Scalar(255, 255, 255);
};
