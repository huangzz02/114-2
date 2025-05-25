#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    while (cin >> N && N != 0) {
        vector<int> dp(N + 1, 0);
        dp[0] = 1;

        vector<int> coins = {1, 5, 10, 50};
        for (int coin : coins) {
            for (int i = coin; i <= N; i++) {
                dp[i] += dp[i - coin];
            }
        }
        cout << dp[N] << endl;
    }
    return 0;
}

// Reference to: https://www.youtube.com/watch?v=jaNZ83Q3QGc

/* Recursion cannot be used because it will lead to double counting.
#include <iostream>
using namespace std;

int count(int n) {
    if (n == 0) {
        return 1;
    }
    if (n < 0) {
        return 0;
    }
    return count(n - 1) + count(n - 5) + count(n - 10) + count(n - 50);
}

int main() {
    int n;
    while (cin >> n && n != 0) {
        cout << count(n) << endl;
    }
    return 0;
}
*/