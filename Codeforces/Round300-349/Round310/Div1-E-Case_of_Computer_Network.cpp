
// http://codeforces.com/contest/555/problem/E

#include <bits/stdc++.h>
using namespace std;

struct edge {
    int from, to;
};

using edges = std::vector<edge>;
using graph = std::vector<edges>;

void add_edge(graph& g, int from, int to) {
    g[from].push_back(edge{from, to});
    g[to].push_back(edge{to, from});
}

class lowlink {
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
                    bridges.push_back(edge{min(v, e.to), max(v, e.to)});
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

// require: lowlink
class biconnected_component {
public:
    biconnected_component(graph const& g_)
        : g(g_), helper(g_), belongs_(g_.size(), -1)
    {
        for(auto&& b : helper.get_bridges()) {
            add_component(b.from), add_component(b.to);
        }
        add_component(0);
    }

    graph build() { // if not connected, result is forest
        graph res(cmps.size());
        auto bridges = helper.get_bridges();
        for(auto& b : bridges) {
            add_edge(res, belongs(b.from), belongs(b.to));
        }
        return res;
    }

    int belongs(int u) const { assert(0 <= u && u < (int)belongs_.size()); return belongs_[u]; }

private:
    void fill_component(int c, int u) {
        cmps[c].emplace_back(u);
        belongs_[u] = c;
        for(auto& e : g[u]) {
            if(belongs_[e.to] >= 0 || helper.is_bridge(u, e.to)) continue;
            fill_component(c, e.to);
        }
    }
    void add_component(int u) {
        if(belongs_[u] >= 0) return;
        cmps.emplace_back();
        fill_component(cmps.size() - 1, u);
    }

private:
    graph g;
    lowlink helper;
    std::vector<int> belongs_;
    std::vector<std::vector<int>> cmps;
};

class lowest_common_ancestor {
public:
    lowest_common_ancestor(graph const& g/* int root*/)
        : n(g.size()), log_n(std::ceil(std::log2(g.size())) + 1),
          parent(log_n, std::vector<int>(n, -1)), depth_(n)
    {
        for(int i = 0; i < n; ++i) {
            if(parent[0][i] == -1) dfs(g, i, -1, 0);
        }
        for(int k = 0; k + 1 < log_n; ++k) {
            for(int v = 0; v < n; ++v) {
                if(parent[k][v] < 0) parent[k + 1][v] = -1;
                else                 parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    int depth(int v) const {
        return depth_[v];
    }

    int dist(int u, int v) const {
        return depth(u) + depth(v) - 2 * depth(query(u, v));
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

    int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]); }

    bool same(int x, int y) { return root(x) == root(y); }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return;
        if(par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
    }

private:
    vector<int> par;
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    graph g(n);
    for(int i = 0; i < m; ++i) {
        int v, u; cin >> v >> u;
        add_edge(g, v - 1, u - 1);
    }
    vector<int> s(q), d(q);
    for(int i = 0; i < q; ++i) {
        cin >> s[i] >> d[i];
        s[i]--, d[i]--;
    }

    biconnected_component bicc(g);
    auto t = bicc.build();
    const int tn = t.size();
    lowest_common_ancestor lca(t);
    union_find uf(tn);
    for(auto& es : t) {
        for(auto& e : es) {
            uf.unite(e.from, e.to);
        }
    }
    vector<int> sum1(tn), sum2(tn), sum3(tn);
    for(int i = 0; i < q; ++i) {
        s[i] = bicc.belongs(s[i]), d[i] = bicc.belongs(d[i]);
        if(!uf.same(s[i], d[i])) {
            cout << "No" << endl;
            return 0;
        }
        sum1[s[i]] += 1, sum2[d[i]] += 1;
        sum3[lca.query(s[i], d[i])] += 1;
    }
    vector<bool> visited(tn);
    function<bool(int, int)> dfs = [&] (int v, int p) {
        bool res = true;
        visited[v] = true;
        for(auto& e : t[v]) {
            if(e.to == p) continue;
            res &= dfs(e.to, v);
        }
        return res & (sum1[v] - sum3[v] <= 0 || sum2[v] - sum3[v] <= 0);
    };
    bool ans = true;
    for(int i = 0; i < tn; ++i) {
        if(visited[uf.root(i)]) continue;
        ans &= dfs(uf.root(i), -1);
    }
    cout << (ans ? "Yes" : "No") << endl;
}
