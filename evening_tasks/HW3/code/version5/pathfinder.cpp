#include "pathfinder.h"
#include <queue>
#include <vector>

PathFinder::PathFinder(Maze& maze) : maze_(maze) {}

std::stack<Maze::Position> PathFinder::findShortestPath() {
    std::vector<std::vector<bool>> visited(maze_.getRows(), std::vector<bool>(maze_.getCols(), false)); // Initialize visited array to false
    std::vector<std::vector<Maze::Position>> parent(maze_.getRows(), std::vector<Maze::Position>(maze_.getCols(), {-1, -1})); // Used to backtrack the path, initialized to -1

    std::queue<Maze::Position> q;
    Maze::Position player = maze_.getPlayer(); // Get the player's initial position
    visited[player.x][player.y] = true;
    q.push(player);

    while (!q.empty()) {
        Maze::Position current = q.front(); // Get the current position from the queue
        q.pop();

        if (current.x == maze_.getGoal().x && current.y == maze_.getGoal().y) {
            maze_.setIsGameOver(true);
            break; // Goal found
        }

        std::vector<Maze::Position> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right
        for (const auto& dir : directions) {
            int newX = current.x + dir.x;
            int newY = current.y + dir.y;

            if (newX >= 0 && newX < maze_.getRows() && newY >= 0 && newY < maze_.getCols() &&
                maze_.getMaze()[newX][newY] != Maze::WALL && !visited[newX][newY]) {
                visited[newX][newY] = true;
                parent[newX][newY] = current; // Set the parent of the new position
                q.push({newX, newY});
            }
        }
    }

    if (maze_.getIsGameOver()) {
        // Backtrack the path from goal to player
        std::stack<Maze::Position> path;
        Maze::Position current = maze_.getGoal();
        while (current.x != -1 && current.y != -1) {
            path.push(current);
            current = parent[current.x][current.y]; // Move to the parent position
        }

        return path;
    } else {
        // Return empty stack if no path found
        std::stack<Maze::Position> emptyStack;
        return emptyStack;
    }
}