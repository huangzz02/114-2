#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int h, m;

    while ((cin >> h) && (h != -1)) {
        cin >> m;
        
        double h_angle = (h % 12) * 30 + m * 0.5;
        double m_angle = m * 6;

        int angle = int(round(abs(h_angle - m_angle)));
        if (angle > 180) angle = 360 - angle;

        cout << angle << endl;
    }

    return 0;
}