#include <iostream>
#include <string>
using namespace std;

int main() {
    int r, c;
    cin >> r >> c;
    string blank(7, ' ');

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (i == j || (i == c && j == r)) {
                if (i * j < 10) {
                    cout << j << "*" << i << "= " << i * j << " ";
                } else {
                    cout << j << "*" << i << "=" << i * j << " ";
                }
            } else {
                cout << blank;
            }
        }
        cout << endl;
    }

    return 0;
}

