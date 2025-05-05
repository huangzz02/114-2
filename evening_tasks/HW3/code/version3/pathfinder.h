#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "maze.h"
#include <stack>

class PathFinder {
private:
    Maze& maze_;
public:
    PathFinder(Maze& maze);
    std::stack<Maze::Position> findShortestPath();
};

#endif