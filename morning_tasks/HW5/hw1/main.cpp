#include <iostream>
#include <vector>
#include "matrix.h"
using namespace std;

int main() {
    int n;
    cout << "Input N: ";
    cin >> n;

    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;

    cout << "Input matrix A: ";
    for(int i = 0; i < n; i++){
        vector<int> row;
        for(int j = 0; j < n; j++){
            int x;
            cin >> x;
            row.push_back(x);
        }
        matrix1.push_back(row);
    }

    cout << "Input matrix B: ";
    for(int i = 0; i < n; i++){
        vector<int> row;
        for(int j = 0; j < n; j++){
            int x;
            cin >> x;
            row.push_back(x);
        }
        matrix2.push_back(row);
    }
    cout << endl;

    while(1) {
        cout << "1-Addition" << endl;
        cout << "2-Subtraction" << endl;
        cout << "3-Multiplication" << endl;
        cout << "4-Divition" << endl;
        cout << "5-Exit" << endl;

        int choice;
        cin >> choice;

        vector<vector<int>> result;
        Matrix m(n, matrix1, matrix2);

        switch(choice){
            case 1:
                result = m.add(matrix1, matrix2);
                break;
            case 2:
                result = m.sub(matrix1, matrix2);
                break;
            case 3:
                result = m.multipe(matrix1, matrix2);
                break;
            case 4:
                result = m.divition(matrix1, matrix2);
                break;
            case 5:
                return 0;
        }

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cout << result[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;
    }

    return 0;
}