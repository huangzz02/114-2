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
    Compared to HW3/version5:
        1. main.cpp
            1.1. Removed "#include "pathfinder.h" " and "PathFinder pathFinder(maze);".
            1.2. Changed the code when "choosedMode == 1" (The auto mode is not yet completed).
            1.3. Removed the code when "choosedMode == 2" and "Detected opposite move" part
                 (Detect the last move for auto-undo is not suitable for pushing boxes).
        2. maze.cpp
            2.1. readMaze()
                2.1.1. Added the setting for "box_" position.
            2.2. restoreOriginalMaze()
                2.2.1. Added the setting for "box_" position.
                2.2.2. Removed "while (!moveHistory_.empty()) moveHistory_.pop();"
                       (Push box won't need to auto-detect the last move).
                2.2.3. Added "while (!boxPositionHistory_.empty()) boxPositionHistory_.pop();" and
                             "while (!boxIsMovedHistory_.empty()) boxIsMovedHistory_.pop();".
        3. maze.h
            3.1. Public
                3.1.1. Removed the "WENTPATH" part (Not suitable for pushing boxes), and added "BOX".
                3.1.2. Added "getBox()" and "setBox()".
                3.1.3. Removed "getMoveHistory()" (Not needed),
                       Added "getBoxPositionHistory()" and "getBoxIsMovedHistory()" (For undo move).
            3.2. Private
                3.2.1. Added "box_".
                3.2.2. Removed "moveHistory_" (Not needed).
                       Added "boxPositionHistory_" and "boxIsMovedHistory_" (For undo move).
        4. move.cpp
            4.1. Removed "isOppositeMove()" (Detect the last move for auto-undo is not suitable for pushing boxes).
            4.2. Significantly change the logic of "movePlayer()" and "undoMove()",
                 to support the box moving and undoing.
        5. move.h
            5.1. Removed "isOppositeMove()" (Detect the last move for auto-undo is not suitable for pushing boxes).
        6. pathfinder.cpp
            6.1. Removed (The auto mode is not yet completed) 
        7. pathfinder.h
            7.1. Removed (The auto mode is not yet completed)

    Supplement: The core change is 4.2.
    Note: This program can only handle the situation of one box at the moment.
*/