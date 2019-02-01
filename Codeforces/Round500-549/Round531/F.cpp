#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> v[i][j];
        }
    }

    vector<vector<int>> cost(n, vector<int>(n));
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            int t = inf;
            for(int k = 0; k < m; ++k) {
                t = min(t, abs(v[i][k] - v[j][k]));
            }
            cost[i][j] = cost[j][i] = t;
            //cout << "i, j: " << i << ' ' << j << " => " << cost[i][j] << endl;
        }
    }

    vector<vector<vector<int>>> dp(1 << n, vector<vector<int>>(n, vector<int>(n, -inf)));
    for(int i = 0; i < n; ++i) {
        dp[1 << i][i][i] = inf;
    }
    for(int S = 1; S < (1 << n); ++S) {
        for(int fst = 0; fst < n; ++fst) {
            for(int lst = 0; lst < n; ++lst) {
                if(dp[S][fst][lst] == -inf) continue;
                //cout << S << ' ' << fst << ' ' << lst << ' ' << " => " << dp[S][fst][lst] << endl;
                for(int nxt = 0; nxt < n; ++nxt) {
                    if(S & (1 << nxt)) continue;
                    const int nS = S | (1 << nxt);
                    dp[nS][fst][nxt] = max(dp[nS][fst][nxt], min(dp[S][fst][lst], cost[lst][nxt]));
                }
            }
        }
    }

    int ans = 0;
    for(int fst = 0; fst < n; ++fst) {
        for(int lst = 0; lst < n; ++lst) {
            const int S = (1 << n) - 1;
            for(int i = 0; i + 1 < m; ++i) {
                dp[S][fst][lst] = min(dp[S][fst][lst], abs(v[fst][i] - v[lst][i + 1]));
            }
            ans = max(ans, dp[S][fst][lst]);
        }
    }

    cout << ans << endl;
}
