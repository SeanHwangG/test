#include "board.h"

Board::Board(){};
Board::Board(const Board &a) : WSIZE(a.WSIZE), bodies(a.bodies), food(a.food), grid(a.grid), board(a.board){};
Board::Board(int WSIZE, vector<vector<int>> &bodies, vector<int> &food) : WSIZE(WSIZE), bodies(bodies), food(food)
{
    namedWindow("board");
    grid.resize(GSIZE, vector<int>(GSIZE, 0));
    board = Mat::zeros(WSIZE, WSIZE, CV_8UC3);
}
void Board::draw()
{
    board = Mat::zeros(WSIZE, WSIZE, CV_8UC3);

    for (auto &elem : grid)
        fill(elem.begin(), elem.end(), 0);

    for (vector<int> body : bodies)
        grid[body[0]][body[1]] = 1;
    grid[food[0]][food[1]] = 2;

    for (int r = 0; r < GSIZE; r++)
        for (int c = 0; c < GSIZE; c++)
        {
            if (grid[r][c] == 1)
                rectangle(board, Point(WSIZE / GSIZE * r, WSIZE / GSIZE * c), Point(WSIZE / GSIZE * r + WSIZE / GSIZE, WSIZE / GSIZE * c + WSIZE / GSIZE), SNAKE_CLR, -1);
            if (grid[r][c] == 2)
                rectangle(board, Point(WSIZE / GSIZE * r, WSIZE / GSIZE * c), Point(WSIZE / GSIZE * r + WSIZE / GSIZE, WSIZE / GSIZE * c + WSIZE / GSIZE), APPLE_CLR, -1);
            imshow("board", board);
        }
}