#include <bits/stdc++.h>
using namespace std;
 
const int inf = 1e9;
 
int main() {
    int w, h, k; cin >> w >> h >> k;
    int n; cin >> n;
    vector<vector<int>> cost(w, vector<int>(h / 2, 1));
    for(int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        x--, y--;
        if(y % 2 == 0) continue;
        cost[x][y / 2] = 2;
    }
 
    k -= (w + 1) / 2;
    if(k < 0) {
        cout << -1 << endl;
        return 0;
    }
 
    const int hz = (h - 1) / 2, wz = (w + 1) / 2;
    vector<vector<int>> dp(wz + 1, vector<int>(2, inf));
    dp[0][0] = 0;
    for(int y = 0; y < hz; ++y) {
        for(int x = 0; x < wz; ++x) {
            if(dp[x][0] != inf) {
                dp[x + 1][0] = min(dp[x + 1][0], dp[x][0] + cost[x * 2][y]);
                if(x != wz - 1) {
                    dp[x + 1][1] = min(dp[x + 1][1], dp[x][0] + cost[x * 2 + 1][y]);
                }
            }
            if(dp[x][1] != inf) {
                dp[x + 1][0] = min(dp[x + 1][0], dp[x][1] + cost[x * 2 - 1][y]);
            }
        }
        const int ns = dp[wz][0];
        for(int x = 0; x <= wz; ++x) {
            for(int S = 0; S < 2; ++S) {
                dp[x][S] = inf;
            }
        }
        dp[0][0] = ns;
    }
 
    int ans = dp[0][0];
    const int tcnt = min(k, ans - hz * wz);
    const int ocnt = max(0, k - tcnt);
    ans = max(0, ans - tcnt * 2 - ocnt);
    cout << ans << endl;
}