#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 1e9 + 7;

int main() {
    int n, k;
    while(cin >> n >> k) {
        vector<vector<int>> g(n);
        for(int i = 0; i < n - 1; ++i) {
            int a, b; cin >> a >> b;
            g[a - 1].push_back(b - 1);
            g[b - 1].push_back(a - 1);
        }

        vector<int> sz(n);
        function<vector<vector<vector<ll>>>(int, int)> solve = [&] (int v, int p) {
            vector<vector<vector<ll>>> dp(k + 1, vector<vector<ll>>(2, vector<ll>(2)));
            sz[v] = 1;
            dp[0][0][0] = 1;
            for(auto const to : g[v]) {
                if(to == p) continue;
                const auto ch = solve(to, v);
                vector<vector<vector<ll>>> nxt(k + 1, vector<vector<ll>>(2, vector<ll>(2)));
                for(int i = 0; i <= sz[v]; ++i) {
                    for(int j = 0; j < 2; ++j) for(int t1 = 0; t1 < 2; ++t1) {
                        for(int l = 0; i + l <= k && l <= sz[to]; ++l) {
                            for(int m = 0; m < 2; ++m) for(int t2 = 0; t2 < 2; ++t2) {
                                (nxt[i + l][j || m][t1 || t2] += dp[i][j][t1] * ch[l][m][t2]) %= mod;
                            }
                        }
                    }
                }
                sz[v] += sz[to];
                dp = move(nxt);
            }
            for(int i = k - 1; i >= 0; --i) { // put
                (dp[i + 1][0][1] += dp[i][0][1] + dp[i][1][1]) %= mod;
                (dp[i + 1][1][1] += dp[i][0][0]) %= mod;
                (dp[i][0][0] += dp[i][0][1]) %= mod;
                dp[i][1][0] = dp[i][1][1] = dp[i][0][1] = 0;
            }
            return dp;
        };
        const auto dp = solve(0, -1);
        cout << (dp[k][0][0] + dp[k][0][1]) % mod << endl;
    }
}
