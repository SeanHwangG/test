#pragma once

#include <map>
#include <string>
#include "board.h"

enum class Direction
{
    RIGHT = 1,
    LEFT = -1,
    UP = 2,
    DOWN = -2
};

enum class Status
{
    GAMEOVER = -1,
    PROGRESS = 0
};

class Snake
{
public:
    Snake(Board board, int GSIZE);
    void updateStatus();
    void start();
    void move(Direction d);

private:
    int turn;
    int GSIZE;
    Status status;
    Board board;
    map<Status, string> status2message;
    Direction direction;
    vector<int> food;
    vector<vector<int>> bodies;
};