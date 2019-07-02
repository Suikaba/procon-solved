#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
constexpr double eps = 1e-10;

struct edge {
    int to, rev, cap;
    double cost;
    edge(int t, int c, double ct, int r) : to(t), rev(r), cap(c), cost(ct) {}
};
using graph = vector<vector<edge>>;

void add_edge(graph& g, int from, int to, int cap, double cost) {
    g[from].emplace_back(to, cap, cost, g[to].size());
    g[to].emplace_back(from, 0, -cost, g[from].size() - 1);
}

double min_cost_flow(graph& g, int s, int t, int f) {
    using P = pair<double, int>;
    const double inf = 1e18;
    double res = 0;
    vector<double > h(g.size()), dist(g.size());
    vector<int> prevv(g.size()), preve(g.size());
    while(f > 0) {
        priority_queue<P, vector<P>, greater<>> que;
        fill(begin(dist), end(dist), inf);
        dist[s] = 0;
        que.emplace(0, s);
        while(!que.empty()) {
            const auto cur_d = que.top().first;
            const int v = que.top().second;
            que.pop();
            if(dist[v] < cur_d) continue;
            for(int i = 0; i < (int)g[v].size(); ++i) {
                auto& e = g[v][i];
                if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to] + eps) {
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

        auto d = f;
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
    int n; cin >> n;
    int ix, iy; cin >> ix >> iy;
    vector<int> sx(n), sy(n), gx(n), gy(n);
    for(int i = 0; i < n; ++i) {
        cin >> sx[i] >> sy[i] >> gx[i] >> gy[i];
    }

    double ans = 0;
    for(int i = 0; i < n; ++i) {
        ans += hypot(gx[i] - sx[i], gy[i] - sy[i]);
    }
    graph g(n * 2 + 2);
    const int src = n * 2, sink = n * 2 + 1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            add_edge(g, i, j + n, 1, hypot(sx[j] - gx[i], sy[j] - gy[i]));
        }
        add_edge(g, src, i, 1, 0);
        add_edge(g, i + n, sink, 1, 0);
    }
    ans += min_cost_flow(g, src, sink, n);

    cout << fixed << setprecision(10) << ans << endl;
}
