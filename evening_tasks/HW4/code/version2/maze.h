#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>
#include <string>

class Maze {
public:
    static const char WALL = '/';
    static const char PATH = '-';
    static const char PLAYER = '0';
    static const char BOX = '1';
    static const char GOAL = '2';

    struct Position { // This part will be used in private, so the public part must write first
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
    Position getBox() const { return box_; }
    Position getGoal() const { return goal_; }
    int getRows() const { return rows_; }
    int getCols() const { return cols_; }
    bool getIsGameOver() const { return isGameOver_; }
    std::stack<Position>& getPlayerPositionHistory() { return playerPositionHistory_; }
    std::stack<Position>& getBoxPositionHistory() { return boxPositionHistory_; }
    std::stack<bool>& getBoxIsMovedHistory() { return boxIsMovedHistory_; }

    void setPlayer(const Position& pos) { player_ = pos; }
    void setBox(const Position& pos) { box_ = pos; }
    void setMazeCell(int x, int y, char value) { maze_[x][y] = value; }
    void setIsGameOver(bool value) { isGameOver_ = value; }
private:
    std::vector<std::vector<char>> maze_;
    std::vector<std::vector<char>> originalMaze_;
    Position player_;
    Position box_;
    Position goal_;
    std::stack<Position> playerPositionHistory_;
    std::stack<Position> boxPositionHistory_;
    std::stack<bool> boxIsMovedHistory_;
    int rows_, cols_;
    bool isGameOver_;
};

#endif