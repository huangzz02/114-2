#include "move.h"
#include <iostream>
#include <thread>
#include <chrono>

Move::Move(Maze& maze) : maze_(maze) {}

bool Move::isValidMove(int x, int y) const {
    return x >= 0 && x < maze_.getRows() && y >= 0 && y < maze_.getCols() && maze_.getMaze()[x][y] != Maze::WALL;
}

bool Move::isOppositeMove(char current, char last) const {
    return (current == 'w' && last == 's') ||
           (current == 's' && last == 'w') ||
           (current == 'a' && last == 'd') ||
           (current == 'd' && last == 'a');
}

bool Move::movePlayer(char direction) {
    Maze::Position newPos = maze_.getPlayer();
    if (direction == 'w') newPos.x--;
    else if (direction == 's') newPos.x++;
    else if (direction == 'a') newPos.y--;
    else if (direction == 'd') newPos.y++;

    if (maze_.getMaze()[newPos.x][newPos.y] == Maze::GOAL) {
        maze_.setIsGameOver(true);
    }

    if (isValidMove(newPos.x, newPos.y)) {
        maze_.getPositionHistory().push(maze_.getPlayer());
        maze_.getMoveHistory().push(direction);
        maze_.setMazeCell(maze_.getPlayer().x, maze_.getPlayer().y, Maze::WENTPATH);
        maze_.setPlayer(newPos);
        maze_.setMazeCell(newPos.x, newPos.y, maze_.getIsGameOver() ? Maze::GOAL : Maze::PLAYER);
        return true;
    }
    return false;
}

void Move::undoMove() {
    if (maze_.getPositionHistory().empty()) {
        std::cout << "There are no undoable moves!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }
    maze_.setMazeCell(maze_.getPlayer().x, maze_.getPlayer().y, Maze::PATH);
    maze_.setPlayer(maze_.getPositionHistory().top());
    maze_.getPositionHistory().pop();
    maze_.getMoveHistory().pop();
    maze_.setMazeCell(maze_.getPlayer().x, maze_.getPlayer().y, Maze::PLAYER);
}