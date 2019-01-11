#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> v(n), a(n), b(n), c(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        v[i] = a[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(2)); // 0: before
    dp[1][0] = a[0], dp[1][1] = b[0];
    for(int i = 1; i < n; ++i) {
        dp[i + 1][0] = max(dp[i][0] + b[i], dp[i][1] + a[i]);
        dp[i + 1][1] = max(dp[i][0] + c[i], dp[i][1] + b[i]);
    }

    cout << dp[n][0] << endl;
}
