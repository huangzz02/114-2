#include "move.h"
#include <iostream>
#include <thread>
#include <chrono>

Move::Move(Maze& maze) : maze_(maze) {}

bool Move::isValidMove(int x, int y) const {
    return x >= 0 && x < maze_.getRows() && y >= 0 && y < maze_.getCols() && maze_.getMaze()[x][y] != Maze::WALL;
}

bool Move::movePlayer(char direction) {
    Maze::Position newPlayerPos = maze_.getPlayer();
    Maze::Position newBoxPos = maze_.getBox();
    bool isBoxMoved = false;
    if (direction == 'w') {
        newPlayerPos.x--;
        if (maze_.getMaze()[newPlayerPos.x][newPlayerPos.y] == Maze::BOX) {
            newBoxPos.x--;
            isBoxMoved = true;
        }
    } else if (direction == 's') {
        newPlayerPos.x++;
        if (maze_.getMaze()[newPlayerPos.x][newPlayerPos.y] == Maze::BOX) {
            newBoxPos.x++;
            isBoxMoved = true;
        }
    } else if (direction == 'a') {
        newPlayerPos.y--;
        if (maze_.getMaze()[newPlayerPos.x][newPlayerPos.y] == Maze::BOX) {
            newBoxPos.y--;
            isBoxMoved = true;
        }
    } else if (direction == 'd') {
        newPlayerPos.y++;
        if (maze_.getMaze()[newPlayerPos.x][newPlayerPos.y] == Maze::BOX) {
            newBoxPos.y++;
            isBoxMoved = true;
        }
    }

    if (maze_.getMaze()[newBoxPos.x][newBoxPos.y] == Maze::GOAL) {
        maze_.setIsGameOver(true);
    }

    if (maze_.getMaze()[newPlayerPos.x][newPlayerPos.y] != Maze::GOAL &&  // Player cannot move to goal directly
        isValidMove(newPlayerPos.x, newPlayerPos.y) && isValidMove(newBoxPos.x, newBoxPos.y)) {
        if (isBoxMoved) {
            maze_.getBoxIsMovedHistory().push(true);
        } else {
            maze_.getBoxIsMovedHistory().push(false);
        }

        maze_.getPlayerPositionHistory().push(maze_.getPlayer());
        maze_.getBoxPositionHistory().push(maze_.getBox());

        maze_.setMazeCell(maze_.getPlayer().x, maze_.getPlayer().y, Maze::PATH);
        maze_.setMazeCell(newPlayerPos.x, newPlayerPos.y, Maze::PLAYER);
        maze_.setPlayer(newPlayerPos);
        if (isBoxMoved) {
            maze_.setMazeCell(newBoxPos.x, newBoxPos.y, maze_.getIsGameOver() ? Maze::GOAL : Maze::BOX);
            maze_.setBox(newBoxPos);
        }

        return true;
    }
    return false;
}

void Move::undoMove() {
    if (maze_.getPlayerPositionHistory().empty()) {
        std::cout << "There are no undoable moves!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    if (maze_.getBoxIsMovedHistory().top() == true) {
        maze_.setMazeCell(maze_.getBox().x, maze_.getBox().y, Maze::PATH);
        maze_.setMazeCell(maze_.getPlayer().x, maze_.getPlayer().y, Maze::BOX);
    } else {
        maze_.setMazeCell(maze_.getPlayer().x, maze_.getPlayer().y, Maze::PATH);
    }
    
    maze_.setPlayer(maze_.getPlayerPositionHistory().top());
    maze_.setBox(maze_.getBoxPositionHistory().top());
    maze_.getPlayerPositionHistory().pop();
    maze_.getBoxPositionHistory().pop();
    maze_.getBoxIsMovedHistory().pop();

    maze_.setMazeCell(maze_.getPlayer().x, maze_.getPlayer().y, Maze::PLAYER);
}