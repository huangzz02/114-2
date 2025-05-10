#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    ifstream file("text.txt");

    vector<string> data;
    string line;
    while (file >> line) {
        data.push_back(line);
    }

    sort(data.begin(), data.end());

    ofstream outputFile("answer.txt");
    int count = 1;
    if (!data.empty()) {
        string currentWord = data[0];
        for (size_t i = 1; i <= data.size(); ++i) {
            if (i < data.size() && data[i] == currentWord) {
                count++;
            } else {
                if (isalpha(currentWord[0])) {
                    string outputLine = "\"" + currentWord + "\" appears " + to_string(count) + " time in the file.";
                    cout << outputLine << endl;
                    outputFile << outputLine << endl;
                }

                if (i < data.size()) {
                    currentWord = data[i];
                    count = 1;
                }
            }
        }
    }

    return 0;
}