#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string input;

    vector<string> Vincent;
    vector<string> Leo;

    cout << "#Vincent's friend:" << endl;
    while ((cin >> input) && (input != "0")) {
        Vincent.push_back(input);
    }
    cout << endl;

    cout << "#Leo's friend:" << endl;
    while ((cin >> input) && (input != "0")) {
        Leo.push_back(input);
    }
    cout << endl;

    vector<string> invitee = Vincent;
    for (int i = 0; i < Leo.size(); i++) {
        bool found = false;
        for (int j = 0; j < Vincent.size(); j++) {
            if (Leo[i] == Vincent[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            invitee.push_back(Leo[i]);
        }
    }
    cout << "#Invitee:" << endl;
    for (int i = 0; i < invitee.size(); i++) {
        cout << invitee[i] << endl;
    }

    return 0;
}