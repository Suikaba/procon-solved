#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename Edge>
class graph {
    using graph_t = std::vector<std::vector<Edge>>;
public:
    using reference = std::vector<Edge>&;
    using const_reference = std::vector<Edge> const&;
    using iterator = typename graph_t::iterator;
    using const_iterator = typename graph_t::const_iterator;
    using reverse_iterator = typename graph_t::reverse_iterator;

    graph() : g() {}
    graph(int n) : g(n) {}

    reference operator[](int x) { return g[x]; }
    const_reference operator[](int x) const { return g[x]; }

    iterator begin() { return std::begin(g); }
    const_iterator begin() const { return std::begin(g); }
    iterator end() { return std::end(g); }
    const_iterator end() const { return std::end(g); }
    reverse_iterator rbegin() { return std::rbegin(g); }
    reverse_iterator rend() { return std::rend(g); }

    int size() const { return g.size(); }

    void add_node(std::vector<Edge> es) {
        g.push_back(std::move(es));
    }

private:
    std::vector<std::vector<Edge>> g;
};

struct bidirected_edge {
    bidirected_edge(int f, int t) : from(f), to(t) {}
    int from, to;
};

using bidirected_graph = graph<bidirected_edge>;

void add_edge(bidirected_graph& g, int u, int v) {
    g[u].emplace_back(u, v);
    g[v].emplace_back(v, u);
}

class lowest_common_ancestor {
public:
    template <typename Edge>
    lowest_common_ancestor(graph<Edge> const& g, int root)
        : sz(g.size()), log_sz(0), depth(sz, 0)
    {
        for(int v = sz; v > 0; v >>= 1) ++log_sz;
        parent.assign(log_sz, std::vector<int>(sz));
        dfs(g, root, -1, 0);
        for(int k = 0; k < log_sz - 1; ++k) {
            for(int v = 0; v < sz; ++v) {
                if(parent[k][v] < 0) {
                    parent[k + 1][v] = -1;
                } else {
                    parent[k + 1][v] = parent[k][parent[k][v]];
                }
            }
        }
    }

    int query(int u, int v) const {
        if(depth[u] > depth[v]) std::swap(u, v);
        for(int k = 0; k < log_sz; ++k) {
            if(((depth[v] - depth[u]) >> k) & 1) {
                v = parent[k][v];
            }
        }
        if(u == v) return u;
        for(int k = log_sz - 1; k >= 0; --k) {
            if(parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    int dist(int u, int v) const {
        const int l = query(u, v);
        return depth[u] + depth[v] - 2 * depth[l];
    }

private:
    template <typename Edge>
    void dfs(graph<Edge> const& g, int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        for(auto const& e : g[v]) {
            if(e.to == p) continue;
            dfs(g, e.to, v, d + 1);
        }
    }

private:
    const int sz;
    int log_sz;
    std::vector<std::vector<int>> parent;
    std::vector<int> depth;
};

int main() {
    int n; cin >> n;
    bidirected_graph g(n);
    for(int i = 1; i < n; ++i) {
        int p; cin >> p;
        add_edge(g, i, p);
    }
    vector<int> a(n), pos(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    lowest_common_ancestor lca(g, 0);
    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        ans += lca.dist(i, pos[i]);
    }
    cout << ans / 2 << endl;
}