#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

const char WALL = '/';
const char PATH = '-';
const char WENTPATH = '.';
const char PLAYER = '0';
const char GOAL = '1';

struct Position {
    int x, y;
};

vector<vector<char>> maze, originalMaze;
Position player, goal;
stack<Position> positionHistory;
stack<char> moveHistory;
int rows, cols;
bool isGameOver = false;

bool readMaze(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return false;
    }

    file >> rows >> cols;
    maze.resize(rows, vector<char>(cols));
    originalMaze.resize(rows, vector<char>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> maze[i][j];
            originalMaze[i][j] = maze[i][j];

            if (maze[i][j] == PLAYER) {
                player = {i, j};
            } else if (maze[i][j] == GOAL) {
                goal = {i, j};
            }
        }
    }
    file.close();
    return true;
}

void saveMaze(const string& filename, bool restoreOriginal = false) {
    ofstream file(filename);
    file << rows << " " << cols << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << (restoreOriginal ? originalMaze[i][j] : maze[i][j]);
        }
        file << endl;
    }
    file.close();
}

void displayMaze() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

bool isValidMove(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != WALL;
}

bool isOppositeMove(char current, char last) {
    return (current == 'w' && last == 's') ||
           (current == 's' && last == 'w') ||
           (current == 'a' && last == 'd') ||
           (current == 'd' && last == 'a');
}

bool movePlayer(char direction) {
    Position newPos = player;
    if (direction == 'w') newPos.x--;
    else if (direction == 's') newPos.x++;
    else if (direction == 'a') newPos.y--;
    else if (direction == 'd') newPos.y++;

    if (maze[newPos.x][newPos.y] == GOAL) {
        isGameOver = true;
    }

    if (isValidMove(newPos.x, newPos.y)) {
        positionHistory.push(player);
        moveHistory.push(direction);
        maze[player.x][player.y] = WENTPATH;
        player = newPos;
        maze[player.x][player.y] = isGameOver ? GOAL : PLAYER;
        return true;
    }
    return false;
}

void undoMove() {
    if (positionHistory.empty()) {
        cout << "There are no undoable moves!" << endl;
        return;
    }
    maze[player.x][player.y] = PATH;
    player = positionHistory.top();
    positionHistory.pop();
    moveHistory.pop();
    maze[player.x][player.y] = PLAYER;
}

int main() {
    string filename = "maze.txt";
    if (!readMaze(filename)) {
        cout << "Failed to read maze file." << endl;
        return 1;
    }

    cout << "0 : Player, 1 : Goal" << endl;
    char input;
    while (true) {
        displayMaze();
        cout << endl;
        cout << "Step: " << positionHistory.size() + 1 << endl;
        cout << "Use W(Up), S(Down), A(Left), D(Right) to move, U to undo, Q to exit:" << endl;
        cin >> input;
        input = tolower(input);
        if (input != 'w' && input != 's' && input != 'a' && input != 'd' && input != 'u' && input != 'q') {
            cout << "Invalid input! Please use W, S, A, D, U, or Q." << endl;
            continue;
        }

        if (input == 'q') {
            saveMaze(filename, true);
            break;
        }
        else if (input == 'u') undoMove();
        else if (!moveHistory.empty() && isOppositeMove(input, moveHistory.top())) {
            cout << "Detected opposite move , auto undoing..." << endl;
            undoMove();
        }
        else if (input == 'w' || input == 's' || input == 'a' || input == 'd') {
            if (movePlayer(input)) {
                if (isGameOver) {
                    displayMaze();
                    cout << "You reached the goal!" << endl;
                    break;
                }
            } else {
                cout << "Invalid move!" << endl;
            }
        }

        saveMaze(filename, false);
    }

    saveMaze(filename, true);
    cin.ignore();
    cout << endl << "Press Enter to exit..." << endl;
    cin.get();

    return 0;
}