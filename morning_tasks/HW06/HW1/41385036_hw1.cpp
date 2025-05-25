#include "stack.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string input;
    cout << "Enter stack elements: ";
    getline(cin, input);
    cout << endl;

    istringstream iss(input);
    int tempArray[10];
    int count = 0;
    int num;
    while (iss >> num && count < 10) {
        tempArray[count++] = num;
    }

    Stack stack(10);
    stack.initialize(tempArray, count);

    while (true) {
        cout << "1. Push\n2. Pop\n3. Empty\n4. Top\n5. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout << endl;

        if (choice == 5) {
            break;
        }

        stack.handleChoice(choice);
    }

    return 0;
}