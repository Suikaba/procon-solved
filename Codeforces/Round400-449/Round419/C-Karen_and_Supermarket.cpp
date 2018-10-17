// https://codeforces.com/contest/815/problem/C

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = (int)(1e9) + 1;

int dp[5001][5001][2];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    for(int i = 0; i < 5001; ++i) {
        for(int j = 0; j < 5001; ++j) {
            dp[i][j][0] = dp[i][j][1] = inf;
        }
    }

    int n, b; cin >> n >> b;
    vector<int> c(n), d(n);
    vector<vector<int>> g(n);
    for(int i = 0; i < n; ++i) {
        cin >> c[i] >> d[i];
        if(i != 0) {
            int p; cin >> p;
            g[p - 1].push_back(i);
        }
    }
    vector<int> sz(n);
    function<void(int)> solve = [&] (int v) {
        sz[v] = 1;
        dp[v][0][0] = 0, dp[v][0][1] = inf;
        dp[v][1][0] = c[v], dp[v][1][1] = c[v] - d[v];
        for(auto to : g[v]) {
            solve(to);
            for(int cnt = sz[v]; cnt >= 0; --cnt) {
                for(int ch_cnt = 0; ch_cnt <= sz[to]; ++ch_cnt) {
                    // use d[i] (coupon)
                    dp[v][cnt + ch_cnt][1] = min(dp[v][cnt + ch_cnt][1], dp[v][cnt][1] + dp[to][ch_cnt][0]);
                    dp[v][cnt + ch_cnt][1] = min(dp[v][cnt + ch_cnt][1], dp[v][cnt][1] + dp[to][ch_cnt][1]);
                    // not use d[i]
                    dp[v][cnt + ch_cnt][0] = min(dp[v][cnt + ch_cnt][0], dp[v][cnt][0] + dp[to][ch_cnt][0]);
                }
            }
            sz[v] += sz[to];
        }
    };
    solve(0);

    int ans = 0;
    for(int i = n; i >= 0; --i) {
        if(dp[0][i][0] <= b || dp[0][i][1] <= b) {
            ans = i;
            break;
        }
    }

    cout << ans << endl;
}
