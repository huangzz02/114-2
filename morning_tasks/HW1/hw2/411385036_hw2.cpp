#include <iostream>
#include <string>
using namespace std;

int main() {
    string data;
    cin >> data;

    int balance = 0;
    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == '(') {
            balance++;
        } else if (data[i] == ')') {
            balance--;
        }
        if (balance < 0) {
            break;
        }
    }

    if (balance == 0) {
        cout << "valid" << endl;
    } else {
        cout << "invalid" << endl;
    }

    return 0;
}