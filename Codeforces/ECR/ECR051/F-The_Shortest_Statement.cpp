#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pli = pair<ll, int>;

constexpr ll inf = 1e18;

struct edge {
    int from, to;
    ll cost;
};

using edges = std::vector<edge>;
using graph = std::vector<edges>;

void add_edge(graph& g, int from, int to, ll cost) {
    g[from].push_back(edge{from, to, cost});
    g[to].push_back(edge{to, from, cost});
}

vector<ll> dijkstra(graph& g, int s) {
    vector<ll> d(g.size(), inf);
    priority_queue<pli, vector<pli>, greater<>> que;
    que.emplace(0, s);
    d[s] = 0;
    while(!que.empty()) {
        const auto p = que.top(); que.pop();
        const int v = p.second;
        if(d[v] < p.first) continue;
        for(auto& e : g[v]) {
            if(d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.emplace(d[e.to], e.to);
            }
        }
    }
    return d;
}

class lowest_common_ancestor {
public:
    lowest_common_ancestor(graph const& g, int root)
        : n(g.size()), log_n(std::ceil(std::log2(g.size())) + 1),
          parent(log_n, std::vector<int>(n, -1)), depth_(n)
    {
        dfs(g, root, -1, 0);
        for(int k = 0; k + 1 < log_n; ++k) {
            for(int v = 0; v < n; ++v) {
                if(parent[k][v] < 0) parent[k + 1][v] = -1;
                else                 parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    int query(int u, int v) const {
        if(depth_[u] > depth_[v]) {
            std::swap(u, v);
        }
        for(int k = 0; k < log_n; ++k) {
            if((depth_[v] - depth_[u]) >> k & 1) {
                v = parent[k][v];
            }
        }
        if(u == v) {
            return u;
        }
        for(int k = log_n - 1; k >= 0; --k) {
            if(parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

private:
    void dfs(graph const& g, int v, int p, int d) {
        parent[0][v] = p;
        depth_[v] = d;
        for(auto& e : g[v]) {
            if(e.to != p) {
                dfs(g, e.to, v, d + 1);
            }
        }
    }

private:
    int const n, log_n;
    std::vector<std::vector<int>> parent;
    std::vector<int> depth_;
};

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    int root(int x) {
        return par[x] < 0 ? x : par[x] = root(par[x]);
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

private:
    vector<int> par;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    graph g(n), tg(n);
    union_find uf(n);
    vector<int> vs;
    for(int i = 0; i < m; ++i) {
        int u, v, d; cin >> u >> v >> d;
        u--, v--;
        add_edge(g, u, v, d);
        if(uf.unite(u, v)) {
            add_edge(tg, u, v, d);
        } else {
            vs.push_back(u);
            vs.push_back(v);
        }
    }
    sort(begin(vs), end(vs));
    vs.erase(unique(begin(vs), end(vs)), end(vs));

    lowest_common_ancestor lca(tg, 0);
    vector<ll> d(n);
    {
        function<void(int, int, ll)> dfs = [&] (int v, int p, ll sum) {
            d[v] = sum;
            for(auto& e : tg[v]) {
                if(e.to == p) continue;
                dfs(e.to, v, sum + e.cost);
            }
        };
        dfs(0, -1, 0);
    }
    auto dist = [&] (int u, int v) {
        return d[u] + d[v] - 2 * d[lca.query(u, v)];
    };
    vector<vector<ll>> ds(vs.size());
    for(int i = 0; i < (int)vs.size(); ++i) {
        ds[i] = dijkstra(g, vs[i]);
    }

    int q; cin >> q;
    while(q--) {
        int u, v; cin >> u >> v;
        u--, v--;
        ll ans = dist(u, v);
        for(auto& d2 : ds) {
            ans = min(ans, d2[u] + d2[v]);
        }
        cout << ans << endl;
    }
}
