#include <bits/stdc++.h>
using namespace std;

// vector -> TLE

using ll = long long;
constexpr ll inf = 1e18;

int w[250001];
ll dp[2][10][10][3];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    for(int k1 = 0; k1 <= k; ++k1) {
        for(int k2 = 0; k2 <= k; ++k2) {
            for(int p = 0; p < 3; ++p) {
                dp[0][k1][k2][p] = inf;
            }
        }
    }
    dp[0][0][0][1] = 0;
    for(int i = 0; i < n; ++i) {
        const int ni = (i + 1) & 1;
        for(int k1 = 0; k1 <= k; ++k1) {
            for(int k2 = 0; k2 <= k; ++k2) {
                for(int p = 0; p < 3; ++p) {
                    dp[ni][k1][k2][p] = inf;
                }
            }
        }
        for(int k1 = 0; k1 <= k; ++k1) {
            for(int k2 = 0; k2 <= k; ++k2) {
                for(int p = 0; p < 3; ++p) {
                    if(dp[i & 1][k1][k2][p] == inf) continue;
                    if(k1 != k) { // swapped
                        dp[ni][k1 + 1][k2][0] = min(dp[ni][k1 + 1][k2][0], dp[i & 1][k1][k2][p]);
                    }
                    // not swapped
                    dp[ni][k1][k2][0] = min(dp[ni][k1][k2][0], dp[i & 1][k1][k2][p] + w[i]);

                    if(p != 2) { // not put
                        if(k2 != k) { // swapped
                            dp[ni][k1][k2 + 1][p + 1] = min(dp[ni][k1][k2 + 1][p + 1], dp[i & 1][k1][k2][p] + w[i]);
                        }
                        // not swapped
                        dp[ni][k1][k2][p + 1] = min(dp[ni][k1][k2][p + 1], dp[i & 1][k1][k2][p]);
                    }
                }
            }
        }
    }

    ll ans = inf;
    for(int i = 0; i <= k; ++i) {
        for(int j = 0; j < 2; ++j) {
            ans = min(ans, dp[n & 1][i][i][j]);
        }
    }

    cout << ans << endl;
}
