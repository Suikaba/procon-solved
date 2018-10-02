// http://codeforces.com/contest/580/problem/D

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll = long long;

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> cs(n, vector<int>(n));
    for(int i = 0; i < k; ++i) {
        int x, y, c; cin >> x >> y >> c;
        cs[x - 1][y - 1] = c;
    }

    vector<vector<ll>> dp(1 << n, vector<ll>(n, -1));
    for(int i = 0; i < n; ++i) {
        dp[1 << i][i] = a[i];
    }
    ll ans = 0;
    for(int S = 1; S < (1 << n); ++S) {
        for(int pre = 0; pre < n; ++pre) {
            if(dp[S][pre] == -1) continue;
            if(__builtin_popcount(S) == m) {
                ans = max(ans, dp[S][pre]);
            }
            for(int nxt = 0; nxt < n; ++nxt) {
                if(S & (1 << nxt)) continue;
                const int nS = S | (1 << nxt);
                dp[nS][nxt] = max(dp[nS][nxt], dp[S][pre] + a[nxt] + cs[pre][nxt]);
            }
        }
    }

    cout << ans << endl;
}
