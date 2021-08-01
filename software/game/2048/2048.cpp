#include "board.h"
#include <vector>
#include <algorithm>

using namespace std;

enum class Status
{
  GAMEOVER = -1,
  PROGRESS = 0
};

static int GSIZE = 4, WSIZE = 500;
static Board board = Board(WSIZE, GSIZE);

Status check_game_status()
{
  for (int row = 0; row < GSIZE; row++)
    if (find(board.numbers[row].begin(), board.numbers[row].end(), 0) != board.numbers[row].end())
      return Status::PROGRESS;
  return Status::GAMEOVER;
}

void addNewNumber()
{
  int row, col;
  do
  {
    row = rand() % GSIZE;
    col = rand() % GSIZE;
  } while (board.numbers[row][col] != 0);
  board.numbers[row][col] = 2;
}

void push_left()
{
  for (int j = 0; j < GSIZE; j++)
  {
    vector<int> old_line = board.numbers[j];
    vector<int> nonempty, new_line;
    copy_if(old_line.begin(), old_line.end(), back_inserter(nonempty), [](int &value)
            { return value != 0; });

    bool check;
    for (int number : nonempty)
    {
      if (check || new_line.empty() || *new_line.rbegin() != number)
      {
        new_line.push_back(number);
        check = false;
      }
      else
      {
        *new_line.rbegin() += number;
        check = true;
      }
    }
    new_line.resize(4, 0);
    board.numbers[j] = new_line;
  }
}

void rotateCW(vector<vector<int> > &mat, int times)
{
  for (int i = 0; i < times; i++)
    for (int x = 0; x < GSIZE / 2; x++)
      for (int y = x; y < GSIZE - x - 1; y++)
      {
        int temp = mat[x][y];
        mat[x][y] = mat[GSIZE - 1 - y][x];
        mat[GSIZE - 1 - y][x] = mat[GSIZE - 1 - x][GSIZE - 1 - y];
        mat[GSIZE - 1 - x][GSIZE - 1 - y] = mat[y][GSIZE - 1 - x];
        mat[y][GSIZE - 1 - x] = temp;
      }
}

int main()
{
  addNewNumber();
  while (check_game_status() == Status::PROGRESS)
  {
    vector<vector<int> > prev_board = board.numbers;
    char pressed_key = waitKey(50);
    switch (pressed_key)
    {
    case 'w':
      rotateCW(board.numbers, 3);
      push_left();
      rotateCW(board.numbers, 1);
      break;
    case 's':
      rotateCW(board.numbers, 1);
      push_left();
      rotateCW(board.numbers, 3);
      break;
    case 'a':
      push_left();
      break;
    case 'd':
      rotateCW(board.numbers, 2);
      push_left();
      rotateCW(board.numbers, 2);
      break;
    case 'q':
      return -1;
    default:
      break;
    }

    if (prev_board != board.numbers)
      addNewNumber();

    board.draw();
  }
  return 0;
}