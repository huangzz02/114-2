#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool check(string input) {
    if (input.length() == 10 && isupper(input[0]) && (input[1] == '1' || input[1] == '2')) return true;
    else return false;
}

int main() {
    cout << "Please Enter an ID Number: ";
    string input;
    cin >> input;

    if (check(input)) cout << "Correct" << endl;
    else cout << "Incorrect" << endl;

    return 0;
}