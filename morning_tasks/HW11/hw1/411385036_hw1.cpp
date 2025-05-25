#include <iostream>
#include <string>
using namespace std;

int main() {
    string input, output;
    while (cin >> input && input != "0") {
        for (int i = input.length() - 1; i >= 0; i--) {
            output.push_back(input[i]);
        }
        cout << output << endl;
        output.clear();
    }

    return 0;
}