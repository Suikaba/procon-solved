#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e18;

struct edge {
    int from, to;
    ll cost;
};

using edges = vector<edge>;
using graph = vector<edges>;

void add_edge(graph& g, int from, int to, ll cost) {
    g[from].push_back(edge{from, to, cost});
}

class lowlink { // multiple edges ok
public:
    lowlink(graph const& g)
        : ord(g.size()), low(g.size())
    {
        const int n = g.size();
        std::vector<bool> visited(n);
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            if(!visited[i]) {
                dfs(g, i, -1, cnt, visited);
            }
        }
    }

    std::vector<int> get_articulation_points() const { return articulation_points; }
    std::vector<edge> get_bridges() const            { return bridges; }

    bool is_bridge(int u, int v) const {
        if(ord[u] > ord[v]) std::swap(u, v);
        return ord[u] < low[v];
    }

private:
    void dfs(graph const& g, int v, int prev, int& cnt, std::vector<bool>& visited) {
        visited[v] = true;
        low[v] = ord[v] = cnt++;
        bool is_articulation = false;
        int cnt2 = 0, pcnt = 0;

        for(auto& e : g[v]) {
            if((e.to != prev || (e.to == prev && pcnt == 1)) && visited[e.to]) {
                low[v] = min(low[v], ord[e.to]);
            } else if(!visited[e.to]) {
                cnt2++;
                dfs(g, e.to, v, cnt, visited);
                low[v] = min(low[v], low[e.to]);
                if(prev != -1 && ord[v] <= low[e.to]) {
                    is_articulation = true;
                }
                if(is_bridge(v, e.to)) {
                    bridges.push_back(edge{min(v, e.to), max(v, e.to), e.cost});
                }
            }
            pcnt += e.to == prev;
        }
        is_articulation |= (prev == -1 && cnt2 > 1);
        if(is_articulation) articulation_points.push_back(v);
    }

private:
    std::vector<int> articulation_points;
    std::vector<edge> bridges;
    std::vector<int> ord, low;
};

vector<ll> djikstra(graph const& g, int s) {
    const int n = g.size();
    vector<ll> d(n, inf);
    d[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> que;
    que.emplace(0, s);
    while(!que.empty()) {
        auto now = que.top(); que.pop();
        const int v = now.second;
        if(d[v] < now.first) continue;
        for(auto& e : g[v]) {
            if(d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.emplace(d[e.to], e.to);
            }
        }
    }
    return d;
}

int main() {
    int n, m; cin >> n >> m;
    const int s = 0, t = 1;
    edges es;
    graph g(n), rg(n);
    for(int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        es.push_back(edge{a - 1, b - 1, c});
        add_edge(g, a - 1, b - 1, c);
        add_edge(rg, b - 1, a - 1, c);
    }
    auto from_s = djikstra(g, s), from_t = djikstra(rg, t);
    const ll dist = from_s[t];
    graph sg(n);
    for(auto& e : es) {
        if(from_s[e.from] + e.cost + from_t[e.to] == dist) {
            add_edge(sg, e.from, e.to, e.cost);
            add_edge(sg, e.to, e.from, e.cost);
        }
    }
    lowlink helper(sg);
    for(auto& e : es) {
        if(from_s[e.to] + from_t[e.from] + e.cost <= dist) {
            if(from_s[e.to] + from_t[e.from] + e.cost < dist) {
                cout << "HAPPY" << endl;
            } else {
                cout << "SOSO" << endl;
            }
        } else if(from_s[e.from] + from_t[e.to] + e.cost == dist && helper.is_bridge(e.from, e.to)) {
            cout << "SAD" << endl;
        } else {
            cout << "SOSO" << endl;
        }
    }
}
