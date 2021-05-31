#pragma once

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <string>
#include <map>

using namespace std;
using namespace cv;

const Scalar BG_CLR = Scalar(0, 0, 0);
const Scalar SNAKE_CLR = Scalar(0, 255, 0);
const Scalar APPLE_CLR = Scalar(255, 0, 0);
const Scalar LINE_CLR = Scalar(255, 255, 255);
const Scalar TEXT_CLR = Scalar(255, 255, 255);

class Board
{
public:
    int WSIZE;
    Mat board;
    vector<vector<int>> bodies;
    vector<int> food;
    vector<vector<int>> grid;

    Board();
    Board(int WSIZE, vector<vector<int>> &bodies, vector<int> &food);
    Board(const Board &a);

    void draw();

    void gameover(String message)
    {
        putText(board, message, Point(WSIZE / 6, WSIZE / 2), 2, 2, TEXT_CLR);
        imshow("board", board);
        waitKey();
    }
};