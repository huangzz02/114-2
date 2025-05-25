#include <iostream>
#include <string>
using namespace std;

int main() {
    string a, b;
    while(cin >> a >> b && (a != "0" || b != "0")) {
        int lenA = a.length();
        int lenB = b.length();
        int i = 0;
        for (int j = 0; j < lenB; j++) {
            if (i == lenA) {
                break;
            }
            if (a[i] == b[j]) {
                i++;
            }
        }
        if (i == lenA) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
    return 0;
}