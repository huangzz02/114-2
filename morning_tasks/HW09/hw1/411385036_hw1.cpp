#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream file("basic.txt");

    vector<string> data;
    string line;
    while (getline(file, line)) {
        data.push_back(line);
    }

    string inputName;
    cin >> inputName;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].substr(0, inputName.length()) == inputName) {
            cout << data[i] << endl;
            ofstream outputFile("output.txt");
            outputFile << data[i] << endl;
            break;
        }
    }

    return 0;
}