#ifndef MOVE_H
#define MOVE_H

#include "maze.h"

class Move {
private:
    Maze& maze_;
public:
    Move(Maze& maze);

    bool isValidMove(int x, int y) const;
    bool isOppositeMove(char current, char last) const;
    bool movePlayer(char direction);
    void undoMove();
};

#endif