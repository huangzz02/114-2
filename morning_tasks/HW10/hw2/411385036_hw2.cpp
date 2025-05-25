#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ifstream inFile("text.txt");
    if (!inFile) {
        cerr << "Error opening text.txt" << endl;
        return 1;
    }

    string content, line;
    while (getline(inFile, line)) {
        content += line + " ";
    }

    vector<int> numbers;
    string currentNumber;
    for (char c : content) {
        if (c >= '0' && c <= '9') {
            currentNumber += c;
        } else if (!currentNumber.empty()) {
            numbers.push_back(stoi(currentNumber));
            currentNumber.clear();
        }
    }
    if (!currentNumber.empty()) {
        numbers.push_back(stoi(currentNumber));
    }

    sort(numbers.begin(), numbers.end());

    string output;
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (i > 0) output += " ";
        output += to_string(numbers[i]);
    }

    cout << output << endl;

    ofstream outFile("output.txt");
    if (!outFile) {
        cerr << "Error opening output.txt" << endl;
        return 1;
    }
    outFile << output << endl;

    return 0;
}