#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll inf = 1e9;

struct edge {
    int to, cost;
    edge(int t, int c) : to(t), cost(c) {}
};

using edges = vector<edge>;
using graph = vector<edges>;

int main() {
    int n, r;
    while(cin >> n >> r, n) {
        r--;
        graph g(n);
        for(int i = 0; i < n - 1; ++i) {
            int a, b, c; cin >> a >> b >> c;
            a--, b--;
            g[a].emplace_back(b, c);
            g[b].emplace_back(a, c);
        }
        if(n == 1) {
            cout << 0 << endl;
            continue;
        }

        vector<vector<ll>> dp(n, vector<ll>(2, inf));
        function<void(int, int)> solve = [&] (int v, int p) {
            dp[v][1] = 0;
            if(g[v].size() == 1u && p != -1) return;
            for(auto const& e : g[v]) {
                if(e.to == p) continue;
                solve(e.to, v);
            }
            dp[v][0] = 0;
            for(auto const& e : g[v]) {
                if(e.to == p) continue;
                dp[v][0] += min(dp[e.to][0], (ll)e.cost);
            }
        };
        solve(r, -1);

        cout << dp[r][0] << endl;
    }
}