#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

using namespace std;
using namespace cv;

enum class Status;
const Scalar BG_CLR = Scalar(0, 0, 0);
const Scalar LINE_CLR = Scalar(255, 255, 255);
const Scalar TEXT_CLR = Scalar(255, 255, 255);

class Board
{
public:
    vector<vector<int>> numbers;

    Board(int WSIZE, int GSIZE) : WSIZE(WSIZE), GSIZE(GSIZE)
    {
        namedWindow("board");
        numbers.resize(GSIZE, vector<int>(GSIZE, 0));
        board = Mat::zeros(WSIZE, WSIZE, CV_8UC3);
    }

    void draw()
    {
        board = Mat::zeros(WSIZE, WSIZE, CV_8UC3);
        for (int gridNum = 1; gridNum < GSIZE; gridNum++)
        {
            line(board, Point(0, WSIZE * gridNum / GSIZE), Point(WSIZE, WSIZE * gridNum / GSIZE), LINE_CLR, 2);
            line(board, Point(WSIZE * gridNum / GSIZE, 0), Point(WSIZE * gridNum / GSIZE, WSIZE), LINE_CLR, 2);
        }
        for (int row = 0; row < GSIZE; row++)
        {
            for (int col = 0; col < GSIZE; col++)
            {
                if (numbers[row][col] != 0)
                    putText(board, to_string(numbers[row][col]), Point(col * (WSIZE / GSIZE) + 50 - (to_string(numbers[row][col]).length() - 1) * 12, row * (WSIZE / GSIZE) + 80), 2, 2 - 0.2 * to_string(numbers[row][col]).length(), TEXT_CLR);
            }
        }
        imshow("board", board);
    }
private:
    Mat board;
    int GSIZE, WSIZE;
};