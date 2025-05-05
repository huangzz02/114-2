#include <iostream>
#include <string>
#include <thread> // Sleep
#include <chrono> // Calculate the time
#include "maze.h"
#include "move.h"
#include "pathfinder.h"
using namespace std;

void waiting3s(string message) {
    for (int i = 0; i <= 3; ++i) {
        cout << "\r" << message; // Use \r to overwrite the line
        for (int j = 0; j < i; ++j) {
            cout << ".";
        }
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;
}

void waitingCountDown(string message1, int seconds, string message2) {
    for (int i = 0; i <= seconds; ++i) {
        cout << "\r" << message1 << seconds - i << message2; // Use \r to overwrite the line
        for (int j = 0; j < i; ++j) {
            cout << ".";
        }
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;
}

int main() {
    string filename = "mazegraph.txt";
    Maze maze;
    if (!maze.readMaze(filename)) {
        cout << "Failed to read maze file." << endl;
        cout << "----------------------------------------------" << endl;
        waitingCountDown("The program will exit within ", 3, " seconds");
        return 1;
    }

    Move move(maze);
    PathFinder pathFinder(maze);

    while (true) {
        maze.restoreOriginalMaze(); // Restore the original maze for each new game

        cout << "0 : Player, 1 : Goal" << endl;
        maze.displayMaze();
        cout << "Choose mode (1: Auto, 2: Manual, 3: Exit): ";
        int choosedMode;
        cin >> choosedMode;

        if (choosedMode == 1) {
            cout << "----------------------------------------------" << endl;
            waiting3s("Computing shortest path");

            stack<Maze::Position> path = pathFinder.findShortestPath();
            int steps = path.size() - 1; // Exclude the player's initial position

            if (path.empty()) {
                cout << "No path found!" << endl;
                break;
            } else {
                while (!path.empty()) {
                    system("cls");
                    cout << "0 : Player, 1 : Goal" << endl;

                    Maze::Position next = path.top();
                    path.pop();
                    maze.setMazeCell(maze.getPlayer().x, maze.getPlayer().y, Maze::WENTPATH);
                    maze.setPlayer(next);
                    maze.setMazeCell(next.x, next.y, ((path.size() == 0) ? Maze::GOAL : Maze::PLAYER));

                    maze.displayMaze();
                    cout << "Step: " << (steps - path.size()) << "/" << steps << endl;

                    this_thread::sleep_for(chrono::milliseconds(300));
                }

                cout << "Reached the goal!" << endl;
                cout << "Total steps: " << steps << endl;
            }

            maze.saveMaze(filename, true);
            cout << "----------------------------------------------" << endl;
            waitingCountDown("The program will return to the main screen in ", 3, " seconds");
            system("cls");
            continue;
        } else if (choosedMode == 2) {
            while (true) {
                system("cls");
                cout << "0 : Player, 1 : Goal" << endl;
                maze.displayMaze();
                cout << "Step: " << maze.getPositionHistory().size() << endl;

                cout << "Use W(Up), S(Down), A(Left), D(Right) to move, U to undo, Q to exit: ";
                char input;
                cin >> input;
                input = tolower(input);
                if (input != 'w' && input != 's' && input != 'a' && input != 'd' && input != 'u' && input != 'q') {
                    cout << "Invalid input! Please use W, S, A, D, U, or Q." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    continue;
                }

                bool reachGoal = false;

                if (input == 'q') {
                    cout << "Exiting..." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    maze.saveMaze(filename, true);
                    break;
                }
                else if (input == 'u') {
                    cout << "Undoing..." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    move.undoMove();
                }
                else if (!maze.getMoveHistory().empty() && move.isOppositeMove(input, maze.getMoveHistory().top())) {
                    cout << "Detected opposite move , auto undoing..." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    move.undoMove();
                }
                else if (input == 'w' || input == 's' || input == 'a' || input == 'd') {
                    if (move.movePlayer(input)) {
                        if (maze.getIsGameOver()) {
                            reachGoal = true;
                        }
                    } else {
                        cout << "Invalid move!" << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                    }
                }
                
                if (reachGoal) {
                    system("cls");
                    cout << "0 : Player, 1 : Goal" << endl;
                    maze.displayMaze();
                    cout << "Step: " << maze.getPositionHistory().size() << endl;
                    cout << "You reached the goal!" << endl;
                    break;
                }
            }

            maze.saveMaze(filename, true);
            cout << "----------------------------------------------" << endl;
            waitingCountDown("The program will return to the main screen in ", 3, " seconds");
            system("cls");
            continue;
        } else if (choosedMode == 3) {
            break;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Try again." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            continue;
        }
    }

    maze.saveMaze(filename, true);
    cout << "----------------------------------------------" << endl;
    waitingCountDown("The program will exit within ", 3, " seconds");

    return 0;
}
/*
    1. Changed the display of the interactive interface.
*/