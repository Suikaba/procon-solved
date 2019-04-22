#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n;
    while(cin >> n) {
        if(n == 0) break;
        vector<int> x(n);
        for(int i = 0; i < n; ++i) {
            cin >> x[i];
        }

        vector<int> can_pos(n);
        for(int i = 0; i < n; ++i) {
            int it = i;
            while(it + 1 < n && x[it + 1] - x[i] <= 10) {
                it += 1;
            }
            can_pos[i] = it;
        }

        vector<vector<int>> dp(n, vector<int>(12, inf));
        dp[1][1] = 0;
        for(int i = 1; i < n - 1; ++i) {
            for(int j = 11; j >= 1; --j) {
                if(dp[i][j] == inf || i - j < 0) continue;
                const int nxt1 = can_pos[i - j], nxt2 = can_pos[i - j] - 1;
                if(nxt1 > i) {
                    dp[nxt1][nxt1 - i] = min(dp[nxt1][nxt1 - i], dp[i][j] + 1);
                }
                if(nxt2 > i) {
                    dp[nxt2][nxt2 - i] = min(dp[nxt2][nxt2 - i], dp[i][j] + 1);
                }
            }
        }

        const int ans = *min_element(begin(dp[n - 1]), end(dp[n - 1]));
        if(ans == inf) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
}