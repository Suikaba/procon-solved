#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll = long long;

constexpr int inf = 1e9;

struct edge {
    int to, cost;
    edge(int t, int c) : to(t), cost(c) {}
};

using edges = vector<edge>;
using graph = vector<edges>;

void add_edge(graph& g, int from, int to, int cost) {
    g[from].emplace_back(to, cost);
    g[to].emplace_back(from, cost);
}

int main() {
    int n, m; cin >> n >> m;
    graph g(n);
    for(int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        add_edge(g, a - 1, b - 1, c);
    }

    vector<vector<int>> cost(13, vector<int>(13));
    for(int s = 0; s < 13; ++s) {
        vector<int> dist(n, inf);
        priority_queue<pii, vector<pii>, greater<>> que;
        dist[s] = 0;
        que.emplace(0, s);
        while(!que.empty()) {
            const auto [cur_d, v] = que.top();
            que.pop();
            if(cur_d > dist[v]) continue;
            for(auto const& e : g[v]) {
                if(dist[e.to] > dist[v] + e.cost) {
                    dist[e.to] = dist[v] + e.cost;
                    que.emplace(dist[e.to], e.to);
                }
            }
        }
        for(int t = 0; t < 13; ++t) {
            cost[s][t] = dist[t];
        }
    }

    vector<vector<ll>> dp(1 << 13, vector<ll>(13, inf));
    dp[0][0] = 0;
    for(int S = 0; S < (1 << 13); ++S) {
        for(int cur = 0; cur < 13; ++cur) {
            if(dp[S][cur] == inf) continue;
            for(int to = 0; to < 13; ++to) {
                if(S & (1 << to)) continue;
                dp[S | (1 << to)][to] = min(dp[S | (1 << to)][to], dp[S][cur] + cost[cur][to]);
            }
        }
    }
    cout << dp[(1 << 13) - 1][0] << endl;
}
