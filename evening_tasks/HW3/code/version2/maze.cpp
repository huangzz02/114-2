#include "maze.h"
#include <iostream>
#include <fstream>

Maze::Maze() : rows_(0), cols_(0), isGameOver_(false) {}

bool Maze::readMaze(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    file >> rows_ >> cols_;
    maze_.resize(rows_, std::vector<char>(cols_));
    originalMaze_.resize(rows_, std::vector<char>(cols_));

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            file >> maze_[i][j];
            originalMaze_[i][j] = maze_[i][j];

            if (maze_[i][j] == PLAYER) {
                player_ = {i, j};
            } else if (maze_[i][j] == GOAL) {
                goal_ = {i, j};
            }
        }
    }
    file.close();
    return true;
}

void Maze::saveMaze(const std::string& filename, bool restoreOriginal) {
    std::ofstream file(filename);
    file << rows_ << " " << cols_ << std::endl;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            file << (restoreOriginal ? originalMaze_[i][j] : maze_[i][j]);
        }
        file << std::endl;
    }
    file.close();
}

void Maze::displayMaze() const{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout << maze_[i][j];
        }
        std::cout << std::endl;
    }
}