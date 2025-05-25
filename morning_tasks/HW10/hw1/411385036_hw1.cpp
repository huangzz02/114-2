#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    
    while (true) {
        getline(cin, s);
        
        if (s == "0") {
            break;
        }
        
        int len = s.length();
        int lastWord = 0;
        bool inWord = false;
        
        for (int i = len - 1; i >= 0; i--) {
            if (s[i] != ' ') {
                inWord = true;
                lastWord++;
            }
            else if (inWord) {
                break;
            }
        }
        
        cout << lastWord << endl;
    }
    
    return 0;
}