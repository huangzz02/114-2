#include <iostream>
#include <vector>
// #include <unistd.h> -> For sleep function
using namespace std;

int main() {
    int n;

    while (cin >> n && n != -1) {
        int m = 1;

        while (m <= n) {
            /*
            For testing output:
            cout << "m: " << m << endl;
            */
            vector<int> data;
            for (int i = 0; i < n; i++) {
                data.push_back(i + 1);
            }

            int index = 0;
            int to_eliminate = 0;
            while (data.size() > 1) {
                /*
                For testing output:
                for (int i = 0; i < data.size(); i++) {
                    cout << data[i] << " ";
                }
                cout << endl;
                cout << data[index] << " is out" << endl;
                sleep(1);
                */
                index = (index + (m - 1)) % (data.size() - 1);
                data.erase(data.begin() + to_eliminate);
                to_eliminate = index;
            }

            if (data[0] == 13) {
                cout << m << endl;
                break;
            }

            m++;
        }

        if (m > n) {
            cout << "No answer" << endl;
        }

        cout << endl;
    }

    return 0;
}