#include <iostream>
#include <string>
#include "maze.h"
#include "move.h"
#include "pathfinder.h"
using namespace std;

int main() {
    string filename = "mazegraph.txt";
    Maze maze;
    if (!maze.readMaze(filename)) {
        cout << "Failed to read maze file." << endl;
        cout << endl << "Press Enter to exit..." << endl;
        cin.ignore();
        cin.get();
        return 1;
    }

    Move move(maze);
    PathFinder pathFinder(maze);

    cout << "0 : Player, 1 : Goal" << endl;
    maze.displayMaze();
    cout << "-----------------------------------------" << endl;

    while (true) {
        maze.restoreOriginalMaze(); // Restore the original maze for each new game

        cout << "Choose mode (1: Auto, 2: Manual, 3: Exit): ";
        int choosedMode;
        cin >> choosedMode;
        if (choosedMode == 1) {
            cout << "-----------------------------------------" << endl;
            cout << "Computing shortest path..." << endl << endl;
            stack<Maze::Position> path = pathFinder.findShortestPath();
            int steps = path.size() - 1; // Exclude the player's initial position

            if (path.empty()) {
                cout << "No path found!" << endl;
                break;
            } else {
                while (!path.empty()) {
                    Maze::Position next = path.top();
                    path.pop();
                    maze.setMazeCell(maze.getPlayer().x, maze.getPlayer().y, Maze::WENTPATH);
                    maze.setPlayer(next);
                    maze.setMazeCell(next.x, next.y, ((path.size() == 0) ? Maze::GOAL : Maze::PLAYER));
                }

                maze.displayMaze();
                cout << "Step: " << steps << endl << endl;
                cout << "Reached the goal!" << endl;
            }

            maze.saveMaze(filename, true);
            cout << "-----------------------------------------" << endl;
            continue;
        } else if (choosedMode == 2) {
            cout << "-----------------------------------------" << endl;
            while (true) {
                cout << "Use W(Up), S(Down), A(Left), D(Right) to move, U to undo, Q to exit: ";
                char input;
                cin >> input;
                input = tolower(input);
                if (input != 'w' && input != 's' && input != 'a' && input != 'd' && input != 'u' && input != 'q') {
                    cout << "Invalid input! Please use W, S, A, D, U, or Q." << endl;
                    continue;
                }

                bool reachGoal = false;

                if (input == 'q') {
                    maze.saveMaze(filename, true);
                    break;
                }
                else if (input == 'u') move.undoMove();
                else if (!maze.getMoveHistory().empty() && move.isOppositeMove(input, maze.getMoveHistory().top())) {
                    cout << "Detected opposite move , auto undoing..." << endl;
                    move.undoMove();
                }
                else if (input == 'w' || input == 's' || input == 'a' || input == 'd') {
                    if (move.movePlayer(input)) {
                        if (maze.getIsGameOver()) {
                            reachGoal = true;
                        }
                    } else {
                        cout << "Invalid move!" << endl;
                    }
                }

                maze.displayMaze();
                cout << "Step: " << maze.getPositionHistory().size() << endl;
                cout << endl;

                if (reachGoal) {
                    cout << "You reached the goal!" << endl;
                    break;
                }
            }

            maze.saveMaze(filename, true);
            cout << "-----------------------------------------" << endl;
            continue;
        } else if (choosedMode == 3) {
            break;
        } else {
            cout << "Invalid choice! Try again." << endl;
            continue;
        }
    }

    maze.saveMaze(filename, true);
    cout << "-----------------------------------------" << endl;
    cout << "Press Enter to exit..." << endl;
    cin.ignore();
    cin.get();

    return 0;
}
/*
    1. Automatic mode has been added. The program can now automatically find the shortest path using BFS.
*/