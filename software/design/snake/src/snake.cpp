#include <iostream>
#include <string>
#include "snake.h"
#include "board.h"

using namespace std;

Snake::Snake(Board board, int GSIZE) : GSIZE(GSIZE)
{
    direction = Direction::RIGHT;
    food = {rand() % GSIZE, rand() % GSIZE};
    bodies = {{rand() % GSIZE, rand() % GSIZE}};
    board = Board(GSIZE, 500, bodies, food);
}

static int GSIZE = 10;
static int waitTime = 80;
static Status status = Status::PROGRESS;

void Snake::move(Direction d)
{
    vector<int> head = bodies.front();
    switch (d)
    {
    case Direction::UP:
        head = {head[0], (head[1] + GSIZE - 1) % GSIZE};
        break;
    case Direction::DOWN:
        head = {head[0], (head[1] + 1) % GSIZE};
        break;
    case Direction::RIGHT:
        head = {(head[0] + 1) % GSIZE, head[1]};
        break;
    case Direction::LEFT:
        head = {(head[0] - 1 + GSIZE) % GSIZE, head[1]};
        break;
    default:
        break;
    }

    bodies.insert(bodies.begin(), head);

    if (head[0] == food[0] && head[1] == food[1])
    {
        do
            food = {rand() % GSIZE, rand() % GSIZE}; // locate food outside of bodies
        while (find(bodies.begin(), bodies.end(), food) != bodies.end());
    }
    else
        bodies.pop_back();
}

void Snake::updateStatus()
{
    if (find(bodies.begin(), bodies.end(), bodies[0]) != bodies.end())
        status = Status::GAMEOVER;
}

int main()
{
    while (char pressed_key = waitKey(waitTime))
    {
        switch (pressed_key)
        {
        case 'w':
            if (direction != Direction::DOWN)
                direction = Direction::UP;
            break;
        case 's':
            if (direction != Direction::UP)
                direction = Direction::DOWN;
            break;
        case 'a':
            if (direction != Direction::RIGHT)
                direction = Direction::LEFT;
            break;
        case 'd':
            if (direction != Direction::LEFT)
                direction = Direction::RIGHT;
            break;
        default:
            break;
        }
        status = move(direction);
        board.draw();
        if (pressed_key == 'q' || status == Status::GAMEOVER)
            break;
    }
    while (true)
    {
        board.gameover("GAMEOVER");
        if (waitKey())
            break;
    }
    return 0;
}