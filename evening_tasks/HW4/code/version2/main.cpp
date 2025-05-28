#include <iostream>
#include <string>
#include <thread> // Sleep
#include <chrono> // Calculate the time
#include "maze.h"
#include "move.h"
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
    cout << "Enter the name of the maze map document (remember to add \".txt\"): ";
    string filename;
    cin >> filename;
    Maze maze;
    if (!maze.readMaze(filename)) {
        cout << "Failed to read maze file." << endl;
        cout << "----------------------------------------------" << endl;
        waitingCountDown("The program will exit within ", 3, " seconds");
        return 1;
    }

    Move move(maze);

    while (true) {
        maze.restoreOriginalMaze(); // Restore the original maze for each new game

        cout << "0 : Player, 1 : Goal" << endl;
        maze.displayMaze();
        cout << "Choose mode (1: Auto, 2: Manual, 3: Exit): ";
        int choosedMode;
        cin >> choosedMode;

        if (choosedMode == 1) {
            cout << "----------------------------------------------" << endl;
            waitingCountDown("This feature is not yet completed, returning to the main screen in ", 3, " seconds");
            cout << "\033[2J\033[1;1H" << flush;
            continue;
        } else if (choosedMode == 2) {
            while (true) {
                cout << "\033[2J\033[1;1H" << flush;
                cout << "0 : Player, 1 : Goal" << endl;
                maze.displayMaze();
                cout << "Step: " << maze.getPlayerPositionHistory().size() << endl;

                int x = maze.getBox().x;
                int y = maze.getBox().y;
                auto& grid = maze.getMaze();
                if ((grid[x - 1][y] == Maze::WALL && grid[x][y - 1] == Maze::WALL) ||
                    (grid[x - 1][y] == Maze::WALL && grid[x][y + 1] == Maze::WALL) ||
                    (grid[x + 1][y] == Maze::WALL && grid[x][y - 1] == Maze::WALL) ||
                    (grid[x + 1][y] == Maze::WALL && grid[x][y + 1] == Maze::WALL)) {
                    if (maze.getPlayerPositionHistory().size() == 0) {
                        cout << "The box is stuck! The maze cannot be solved." << endl;
                        break;
                    } else {
                        waiting3s("The box is stuck! Auto undoing");
                        move.undoMove();
                        continue;
                    }
                }

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
                    cout << "\033[2J\033[1;1H" << flush;
                    cout << "0 : Player, 1 : Goal" << endl;
                    maze.displayMaze();
                    cout << "Step: " << maze.getPlayerPositionHistory().size() << endl;
                    cout << "You reached the goal!" << endl;
                    break;
                }
            }

            maze.saveMaze(filename, true);
            cout << "----------------------------------------------" << endl;
            waitingCountDown("The program will return to the main screen in ", 3, " seconds");
            cout << "\033[2J\033[1;1H" << flush;
            continue;
        } else if (choosedMode == 3) {
            break;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Try again." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "\033[2J\033[1;1H" << flush;
            continue;
        }
    }

    maze.saveMaze(filename, true);
    cout << "----------------------------------------------" << endl;
    waitingCountDown("The program will exit within ", 3, " seconds");

    return 0;
}
/*
    Compared to version1:
        1. Added auto undo when the box is stuck.

    Note1: This program can only handle the situation of one box at the moment.
    Note2: Before the game ends, the player can move to the goal (The goal icon will be replaced by the player icon temporarily).
*/