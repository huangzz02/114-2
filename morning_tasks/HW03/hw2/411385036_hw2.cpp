#include "time.h"
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    Time t;
    int h = 0, m = 0, s = 0;
    cout << "Initial Time is: " << t.showTime() << endl << endl;

    while(1) {
        cout << "Please set time: ";
        
        if (cin >> h) {
            if (h == -1) {
                break;
            }

            char nextChar = cin.get();

            if (nextChar == ' ') {
                if (cin >> m >> s) {
                    if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59) {
                        cout << "Error!" << endl << endl;
                        continue;
                    }
                    t.setTime(h, m, s);
                }
            } else {
                s = h;
                h = 0;
                m = 0;
                if (s < 0 || s > 86399) {
                    cout << "Error!" << endl << endl;
                    continue;
                }
                t.setTime(s);
            }

            cout << "Set time: " << t.showTime() << endl << endl;
        }
    }
    return 0;
}