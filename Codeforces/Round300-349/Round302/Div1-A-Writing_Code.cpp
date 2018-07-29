
// http://codeforces.com/contest/544/problem/C

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, b, mod;
    cin >> n >> m >> b >> mod;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> dp(m + 1, vector<int>(b + 1));
    dp[0][0] = 1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= m - 1; ++j) {
            for(int k = 0; k <= b - a[i]; ++k) {
                (dp[j + 1][k + a[i]] += dp[j][k]) %= mod;
            }
        }
    }

    int ans = 0;
    for(int i = 0; i <= b; ++i) {
        (ans += dp[m][i]) %= mod;
    }
    cout << ans << endl;
}
