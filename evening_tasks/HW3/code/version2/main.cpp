#include <iostream>
#include <string>
#include "maze.h"
#include "move.h"
using namespace std;

int main() {
    string filename = "maze.txt";
    Maze maze;
    if (!maze.readMaze(filename)) {
        cout << "Failed to read maze file." << endl;
        
        cout << endl << "Press Enter to exit..." << endl;
        cin.ignore();
        cin.get();
        return 1;
    }

    Move move(maze);

    cout << "0 : Player, 1 : Goal" << endl;
    char input;
    while (true) {
        maze.displayMaze();
        cout << endl;
        cout << "Step: " << maze.getPositionHistory().size() + 1 << endl;
        cout << "Use W(Up), S(Down), A(Left), D(Right) to move, U to undo, Q to exit:" << endl;
        cin >> input;
        input = tolower(input);
        if (input != 'w' && input != 's' && input != 'a' && input != 'd' && input != 'u' && input != 'q') {
            cout << "Invalid input! Please use W, S, A, D, U, or Q." << endl;
            continue;
        }

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
                    maze.displayMaze();
                    cout << "You reached the goal!" << endl;
                    break;
                }
            } else {
                cout << "Invalid move!" << endl;
            }
        }

        maze.saveMaze(filename, false);
    }

    maze.saveMaze(filename, true);
    cout << endl << "Press Enter to exit..." << endl;
    cin.ignore();
    cin.get();

    return 0;
}
/*
    1. Change the code into a class-based structure.
*/