#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 2e18;

ll solve(vector<ll> bus, vector<ll> train) {
    const int n = bus.size();
    vector<vector<ll>> dp(30, vector<ll>(30, inf));
    dp[0][0] = 0;
    for(int i = 0; i < n; ++i) {
        vector<vector<ll>> nxt(30, vector<ll>(30, inf));
        for(int j = 0; j < 30; ++j) {
            for(int k = 0; k < 30; ++k) {
                const ll bcost = (j == 0 ? bus[i] : 0);
                const ll tcost = (k == 0 ? 2 * train[i] : 0);
                const int nb = max(0, j - 1), nt = max(0, k - 1);
                nxt[29][29] = min(nxt[29][29], dp[j][k] + 90); // 8
                nxt[29][nt] = min(nxt[29][nt], dp[j][k] + 45 + tcost); // 7
                nxt[max(nb, 6)][max(nt, 6)] = min(nxt[max(nb, 6)][max(nt, 6)], dp[j][k] + 36); // 6
                nxt[max(nb, 6)][nt] = min(nxt[max(nb, 6)][nt], dp[j][k] + tcost + 18); // 5
                nxt[nb][nt] = min(nxt[nb][nt], dp[j][k] + min({6LL, 3 + tcost, bcost + tcost})); // 4, 3, 1
            }
        }
        dp = move(nxt);
    }

    ll ans = inf;
    for(int i = 0; i < 30; ++i) {
        for(int j = 0; j < 30; ++j) {
            ans = min(ans, dp[i][j]);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<ll> bus(n), train(n);
        for(int i = 0; i < n; ++i) {
            cin >> bus[i] >> train[i];
        }
        cout << solve(move(bus), move(train)) << endl;
    }
}
