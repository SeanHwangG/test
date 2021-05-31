#pragma once

#include <iostream>
#include <map>
#include <string>

#include "board.hpp"

static int BOARD_SIZE = 500;
static Board board = Board(BOARD_SIZE);
enum class Status
{
  ENDED = -1,
  PROGRESS = 0,
  WIN_1 = 1,
  WIN_2 = 2,
  DRAW = 3,
};

class TicTacToe
{
public:
  TicTacToe(Board board) : board(board)
  {
    callback = [&](int event, int r, int c)
    {
      if (event == EVENT_LBUTTONDOWN)
        if (move(r * 3 / board.SIZE, c * 3 / board.SIZE))
        {
          updateStatus();
          turn++;
        }
    };
    status2message = {
        {Status::ENDED, "Aborted"},
        {Status::PROGRESS, ""},
        {Status::WIN_1, "Player 1 won"},
        {Status::WIN_2, "Player 2 won"},
        {Status::DRAW, "Draw"},
    };
  }

  bool move(int row, int col)
  {
    if (board.grid[row][col] != 0)
      return false;
    board.grid[row][col] = turn % 2 + 1;
    return true;
  }

  void updateStatus()
  {
    for (int i = 0; i < 3; i++)
    {
      int row_count = 0, col_count = 0, ld_count = 0, rd_count = 0;
      for (int j = 0; j < 3; j++)
      {
        if (board.grid[i][j] == (turn % 2 + 1))
          row_count++;
        if (board.grid[j][i] == (turn % 2 + 1))
          col_count++;
        if (board.grid[j][j] == (turn % 2 + 1))
          ld_count++;
        if (board.grid[2 - j][j] == (turn % 2 + 1))
          rd_count++;
      }
      if (row_count == 3 || col_count == 3 || ld_count == 3 || rd_count == 3)
      {
        status = turn % 2 == 0 ? Status::WIN_1 : Status::WIN_2;
        return;
      }
    }

    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (board.grid[i][j] == 0)
        {
          status = Status::PROGRESS;
          return;
        }

    status = Status::DRAW;
  }

  void start()
  {
    turn = 0;
    status = Status::PROGRESS;
    while (status == Status::PROGRESS)
    {
      int key = waitKey(100);
      if (key == 'q')
        status = Status::ENDED;
      board.draw(status2message[status]);
    }
    waitKey(-1);
  }

private:
  int turn;
  Status status;
  Board board;
  map<Status, string> status2message;
};
