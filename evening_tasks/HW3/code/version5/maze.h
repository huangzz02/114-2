#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>
#include <string>

class Maze {
public:
    static const char WALL = '/';
    static const char PATH = '-';
    static const char WENTPATH = '#';
    static const char PLAYER = '0';
    static const char GOAL = '1';

    struct Position { // It'll be used in private, so the public part must write first
        int x, y;
    };

    Maze();

    bool readMaze(const std::string& filename);
    void saveMaze(const std::string& filename, bool restoreOriginal = false);
    void displayMaze() const;
    void restoreOriginalMaze();

    const std::vector<std::vector<char>>& getMaze() const { return maze_; }
    const std::vector<std::vector<char>>& getOriginalMaze() const { return originalMaze_; }
    Position getPlayer() const { return player_; }
    Position getGoal() const { return goal_; }
    int getRows() const { return rows_; }
    int getCols() const { return cols_; }
    bool getIsGameOver() const { return isGameOver_; }
    std::stack<Position>& getPositionHistory() { return positionHistory_; }
    std::stack<char>& getMoveHistory() { return moveHistory_; }

    void setPlayer(const Position& pos) { player_ = pos; }
    void setMazeCell(int x, int y, char value) { maze_[x][y] = value; }
    void setIsGameOver(bool value) { isGameOver_ = value; }
private:
    std::vector<std::vector<char>> maze_;
    std::vector<std::vector<char>> originalMaze_;
    Position player_;
    Position goal_;
    std::stack<Position> positionHistory_;
    std::stack<char> moveHistory_;
    int rows_, cols_;
    bool isGameOver_;
};

#endif