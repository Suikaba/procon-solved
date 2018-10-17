// http://codeforces.com/contest/581/problem/F

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    if(n == 2) {
        cout << 1 << endl;
        return 0;
    }
    int root = -1;
    for(int i = 0; i < n; ++i) {
        if(g[i].size() != 1u) root = i;
    }

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2, inf)));
    vector<int> sz(n);
    function<void(int, int)> dfs = [&] (int v, int p) {
        if(g[v].size() == 1u) {
            sz[v] = 1;
            dp[v][0][0] = dp[v][1][1] = 0;
            return;
        }
        int fst_ch = -1;
        for(auto to : g[v]) {
            if(to == p) continue;
            if(fst_ch == -1) fst_ch = to;
            dfs(to, v);
        }
        {
            int sum = 0;
            for(auto to : g[v]) {
                if(to == p) continue;
                sum += sz[to];
            }
            dp[v].assign(sum + 1, vector<int>(2, inf));
        }
        for(auto to : g[v]) {
            if(to == p) continue;
            sz[v] += sz[to]; // !! add here
            if(to == fst_ch) {
                for(int cnt = 0; cnt <= sz[v]; ++cnt) {
                    for(int c = 0; c < 2; ++c) {
                        for(int cc = 0; cc < 2; ++cc) {
                            if(dp[to][cnt][cc] == inf) continue;
                            dp[v][cnt][c] = min(dp[v][cnt][c], dp[to][cnt][cc] + (c != cc));
                        }
                    }
                }
            } else {
                for(int cnt = sz[v]; cnt >= 0; --cnt) {
                    for(int c = 0; c < 2; ++c) {
                        int mini = inf;
                        for(int ch_cnt = 0; ch_cnt <= min(sz[to], cnt); ++ch_cnt) {
                            for(int ch_c = 0; ch_c < 2; ++ch_c) {
                                mini = min(mini, dp[v][cnt - ch_cnt][c] + dp[to][ch_cnt][ch_c] + (c != ch_c));
                            }
                        }
                        dp[v][cnt][c] = mini;
                    }
                }
            }
        }
    };
    dfs(root, -1);

    cout << min(dp[root][sz[root] / 2][0], dp[root][sz[root] / 2][1]) << endl;
}
