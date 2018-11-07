#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

constexpr int inf = 1e9;

int main() {
    int n; cin >> n;
    vector<int> p(n);
    vector<vector<int>> g(n);
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    for(int i = 0; i < n - 1; ++i) {
        int s, t; cin >> s >> t;
        g[s - 1].push_back(t - 1);
        g[t - 1].push_back(s - 1);
    }

    // 0: start, 1: last, 2: start & last, 3: inter
    int ans = -inf;
    vector<vector<int>> dp(n, vector<int>(4, -inf));
    function<void(int, int)> dfs = [&] (int v, int par) {
        dp[v][0] = dp[v][1] = dp[v][2] = dp[v][3] = p[v];
        vector<int> ch0, ch1, ch2;
        vector<pii> sub0, sub1;
        int sum2 = 0, max_sub3 = 0;
        for(auto to : g[v]) {
            if(to == par) continue;
            dfs(to, v);
            ch0.push_back(max(0, dp[to][0] - 1));
            ch1.push_back(max(0, dp[to][1] - 1));
            ch2.push_back(max(0, dp[to][2] - 2));
            sub0.emplace_back(ch0.back() - ch2.back(), to);
            sub1.emplace_back(ch1.back() - ch2.back(), to);
            max_sub3 = max(max_sub3, max(0, dp[to][3] - 2) - ch2.back());
            sum2 += ch2.back();
        }
        const int sz = ch0.size();
        sort(rbegin(sub0), rend(sub0));
        sort(rbegin(sub1), rend(sub1));
        for(int i = 0; i < sz; ++i) {
            dp[v][0] = max(dp[v][0], sum2 + ch0[i] - ch2[i] + p[v]);
            dp[v][1] = max(dp[v][0], sum2 + ch1[i] - ch2[i] + p[v]);
        }
        dp[v][2] = max(dp[v][2], sum2 + p[v]);
        // inter
        dp[v][3] = max(dp[v][3], sum2 + max_sub3 + p[v]);
        if(sz >= 2) {
            for(int i = 0; i < 2; ++i) {
                for(int j = 0; j < 2; ++j) {
                    if(i == j || sub0[i].second == sub1[j].second) continue;
                    dp[v][3] = max(dp[v][3], sum2 + sub0[i].first + sub1[j].first + p[v]);
                }
            }
        }
        ans = max(ans, *max_element(begin(dp[v]), end(dp[v])));
    };
    dfs(0, -1);

    cout << ans << endl;
}
