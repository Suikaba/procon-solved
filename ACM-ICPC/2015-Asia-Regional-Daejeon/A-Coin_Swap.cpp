#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

constexpr int inf = 1e9;

struct edge {
    int to, cap, cost, rev;
};

using graph = vector<vector<edge>>;

void add_edge(graph& g, int from, int to, int cap, int cost) {
    g[from].push_back(edge{to, cap, cost, (int)g[to].size()});
    g[to].push_back(edge{from, 0, -cost, (int)g[from].size() - 1});
}

int min_cost_flow(graph& g, int s, int t, int f) {
    int res = 0;
    vector<int> h(g.size(), 0), dist(g.size());
    vector<int> prevv(g.size()), preve(g.size());
    while(f > 0) {
        priority_queue<pii, vector<pii>, greater<pii>> que;
        fill(begin(dist), end(dist), inf);
        dist[s] = 0;
        que.emplace(dist[s], s);
        while(!que.empty()) {
            auto p = que.top(); que.pop();
            const int v = p.second;
            for(int i = 0; i < (int)g[v].size(); ++i) {
                auto& e = g[v][i];
                if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.emplace(dist[e.to], e.to);
                }
            }
        }
        if(dist[t] == inf) return -1;
        for(int v = 0; v < (int)g.size(); ++v) {
            h[v] += dist[v];
        }

        int d = f;
        for(int v = t; v != s; v = prevv[v]) {
            d = min(d, g[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * h[t];
        for(int v = t; v != s; v = prevv[v]) {
            auto& e = g[prevv[v]][preve[v]];
            e.cap -= d;
            g[v][e.rev].cap += d;
        }
    }
    return res;
}

int main() {
    int T; cin >> T;
    while(T--) {
        int n, m; cin >> n >> m;
        graph g(n + 2);
        const int source = n, sink = n + 1;
        for(int i = 0; i < m; ++i) {
            int x, y; cin >> x >> y;
            add_edge(g, x - 1, y - 1, inf, 1);
            add_edge(g, y - 1, x - 1, inf, 1);
        }
        vector<int> col(n), coin(n);
        int bnum = 0;
        for(int i = 0; i < n; ++i) {
            cin >> col[i];
            bnum += col[i] == 1;
        }
        for(int i = 0; i < n; ++i) {
            cin >> coin[i];
        }
        for(int i = 0; i < n; ++i) {
            if(col[i] == 1) {
                add_edge(g, source, i, 1, 0);
            }
            if(coin[i] == 1) {
                add_edge(g, i, sink, 1, 0);
            }
        }

        cout << min_cost_flow(g, source, sink, bnum) << endl;
    }
}
