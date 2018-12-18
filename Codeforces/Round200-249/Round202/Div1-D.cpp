#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 1e9 + 7;

int add(int a, int b) {
    a += b;
    if(a >= mod) a -= mod;
    return a;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<string> v(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    vector<vector<int>> dp(n, vector<int>(m));
    auto calc = [&] (int sy, int sx, int gy, int gx) {
        if(v[sy][sx] == '#') return 0;
        for(int i = 0; i < n; ++i) {
            fill(begin(dp[i]), end(dp[i]), 0);
        }
        dp[sy][sx] = 1;
        for(int i = sy; i < n; ++i) {
            for(int j = sx; j < m; ++j) {
                if(v[i][j] == '#' || (i == sy && j == sx)) continue;
                if(i != 0) dp[i][j] = add(dp[i][j], dp[i - 1][j]);
                if(j != 0) dp[i][j] = add(dp[i][j], dp[i][j - 1]);
            }
        }
        return dp[gy][gx];
    };

    int ans = (ll)calc(1, 0, n - 1, m - 2) * calc(0, 1, n - 2 , m - 1) % mod;
    (ans += mod - (ll)calc(1, 0, n - 2, m - 1) * calc(0, 1, n - 1, m - 2) % mod) %= mod;
    cout << ans << endl;
}
