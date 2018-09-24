
// http://codeforces.com/contest/570/problem/E

#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

int main() {
    int n, m; cin >> n >> m;
    vector<string> v(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    vector<vector<int>> dp(n, vector<int>(n));
    constexpr int dx1[2] = {0, 1}, dy1[2] = {1, 0};
    constexpr int dx2[2] = {0, -1}, dy2[2] = {-1, 0};
    auto in_range = [n, m] (int y, int x) {
        return 0 <= y && y < n && 0 <= x && x < m;
    };
    dp[0][n - 1] = v[0][0] == v[n - 1][m - 1];
    for(int i = 0; 2 * (i + 1) <= n + m - 2; ++i) {
        vector<vector<int>> nxt(n, vector<int>(n));
        for(int y1 = 0; y1 < n; ++y1) {
            for(int y2 = 0; y2 < n; ++y2) {
                const int x1 = i - y1, x2 = n + m - 2 - i - y2;
                if(!in_range(y1, x1) || !in_range(y2, x2)) continue;
                for(int d1 = 0; d1 < 2; ++d1) {
                    for(int d2 = 0; d2 < 2; ++d2) {
                        const int ny1 = y1 + dy1[d1], nx1 = x1 + dx1[d1];
                        const int ny2 = y2 + dy2[d2], nx2 = x2 + dx2[d2];
                        if(!in_range(ny1, nx1) || !in_range(ny2, nx2) || v[ny1][nx1] != v[ny2][nx2]) continue;
                        if(ny1 > ny2 || nx1 > nx2) continue;
                        (nxt[ny1][ny2] += dp[y1][y2]) %= mod;
                    }
                }
            }
        }
        dp = move(nxt);
    }
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            (ans += dp[i][j]) %= mod;
        }
    }

    cout << ans << endl;
}
