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

    // dp[v][i] := i is 0 -> distance from 1 is 1
    //             i is 1 -> distance from 1 is 2
    //             i is 2 -> distance from 1 is 2 because of child node
    vector<vector<int>> dp(n, vector<int>(3, inf));
    function<void(int, int)> solve = [&] (int v, int p) {
        dp[v][0] = (p != 0);
        dp[v][1] = 0;
        dp[v][2] = inf;
        for(auto to : g[v]) {
            if(to == p) continue;
            solve(to, v);
            dp[v][0] += min(dp[to][0], dp[to][1]);
            dp[v][1] += min(dp[to][0], dp[to][2]);
        }
        for(auto to : g[v]) {
            if(to == p) continue;
            // 子のうちから 1 つ選んで頂点 1 とつなげる必要がある、ほかは dp[v][1] のときの値と同じ
            dp[v][2] = min(dp[v][2], dp[v][1] - min(dp[to][0], dp[to][2]) + dp[to][0]);
        }
    };

    int ans = 0;
    for(auto to : g[0]) {
        solve(to, 0);
        ans += min({dp[to][0], dp[to][1], dp[to][2]});
    }

    cout << ans << endl;
}
