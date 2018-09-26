
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0367

#include <bits/stdc++.h>

using ll = long long;

class heavy_light_decomposition {
public:
    heavy_light_decomposition(int n_)
        : n(n_), g(n), par(n), head(n), in(n), out(n)
    {}
    heavy_light_decomposition(std::vector<std::vector<int>> const& g_)
        : n(g_.size()), g(g_), par(n), head(n), in(n), out(n)
    {}
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(int rt = 0) {
        dfs1(rt);
        head[rt] = rt;
        dfs2(rt);
    }

    int get_id(int v) const { return in[v]; }

    void vertex_path_query(int u, int v, std::function<void(int, int)> f) {
        while(true) {
            if(in[u] > in[v]) std::swap(u, v);
            f(std::max(in[head[v]], in[u]), in[v] + 1);
            if(head[u] == head[v]) return;
            v = par[head[v]];
        }
    }
    void edge_path_query(int u, int v, std::function<void(int, int)> f) {
        while(true) {
            if(in[u] > in[v]) std::swap(u, v);
            if(head[u] != head[v]) {
                f(std::max(in[head[v]], in[u]), in[v] + 1);
                v = par[head[v]];
            } else {
                if(u != v) f(in[u] + 1, in[v] + 1);
                break;
            }
        }
    }
    void subtree_query(int v, std::function<void(int, int)> f) {
        f(in[v], out[v]);
    }
    int get_lca(int u, int v) const {
        while(true) {
            if(in[u] > in[v]) std::swap(u, v);
            if(head[u] == head[v]) return u;
            v = par[head[v]];
        }
    }

private:
    void dfs1(int rt) {
        std::vector<int> sz(n, 1), iter(n);
        std::vector<std::pair<int, int>> st = {{rt, -1}};
        st.reserve(n);
        while(!st.empty()) {
            const int v = st.back().first;
            if(iter[v] < (int)g[v].size()) {
                if(g[v][iter[v]] != st.back().second) {
                    st.emplace_back(g[v][iter[v]], v);
                }
                ++iter[v];
                continue;
            }
            par[v] = st.back().second;
            if(par[v] != -1) {
                const int pidx = std::find(std::begin(g[v]), std::end(g[v]), par[v]) - std::begin(g[v]);
                std::swap(g[v].back(), g[v][pidx]);
                g[v].pop_back();
            }
            for(auto& u : g[v]) {
                sz[v] += sz[u];
                if(sz[u] > sz[g[v].front()]) std::swap(u, g[v].front());
            }
            st.pop_back();
        }
    }
    void dfs2(int rt) {
        int it = 0;
        std::vector<int> st = {rt}, iter(n);
        st.reserve(n);
        while(!st.empty()) {
            const int v = st.back();
            if(!iter[v]) in[v] = it++; // first visit
            if(iter[v] < (int)g[v].size()) {
                int u = g[v][iter[v]];
                head[u] = iter[v] ? u : head[v];
                st.push_back(u);
                ++iter[v];
                continue;
            }
            out[v] = it;
            st.pop_back();
        }
    }

private:
    const int n;
    std::vector<std::vector<int>> g;
    std::vector<int> par, head, in, out;
};

template<typename Monoid>
class segment_tree {
    using T = typename Monoid::type;

public:
    segment_tree(std::vector<T> const& init)
        : sz(init.size()), n(expand(init.size()))
    {
        dat.assign(n*2, Monoid::id());
        std::copy(begin(init), end(init), begin(dat) + n);
        for(int i = n - 1; i >= 0; --i) {
            dat[i] = Monoid::op(dat[i * 2], dat[i * 2 + 1]);
        }
    }

    segment_tree(int const n_, T const& init = Monoid::id())
        : segment_tree(std::vector<T>(n_, init))
    {}

    void update(int p, T val) {
        assert(0 <= p && p < sz);
        dat[p += n] = val;
        while(p /= 2) {
            dat[p] = Monoid::op(dat[p * 2], dat[p * 2 + 1]);
        }
    }

    // [l, r)
    T query(int l, int r) const {
        assert(0 <= l && l <= r && r <= sz);
        l += n; r += n;
        T res1 = Monoid::id(), res2 = Monoid::id();
        while(l != r) {
            if(l & 1) res1 = Monoid::op(res1, dat[l++]);
            if(r & 1) res2 = Monoid::op(dat[--r], res2);
            l /= 2, r /= 2;
        }
        return Monoid::op(res1, res2);
    }

private:
    int expand(int n_) const {
        assert(n_ >= 1);
        return n_ == 1 ? n_ : expand((n_ + 1) / 2) * 2;
    }

private:
    const int sz, n;
    std::vector<T> dat;
};

using namespace std;

struct AOJ0367 {
    struct node {
        node(int k_, ll lc, ll rc, ll ctp, ll tot)
            : k(k_), lcost(lc), rcost(rc), cost_to_par(ctp), total_cost(tot)
        {}
        int k;
        // lcost := left edge cost (added val by query)
        // rcost := right ...
        // cost_to_par := original edge cost to parent node
        ll lcost, rcost, cost_to_par, total_cost;
    };
    using type = node;
    static type id() {
        return node(-1, 0, 0, 0, 0);
    }
    static type op(type const& l, type const& r) {
        if(l.k == -1) return r;
        if(r.k == -1) return l;
        node res(l.k, l.lcost, r.rcost, l.cost_to_par, l.total_cost + r.total_cost);
        const ll tc = l.rcost + r.lcost + r.cost_to_par;
        res.total_cost += (tc % l.k == 0 ? 0 : tc);
        return res;
    }
};

int main() {
    int n, k; cin >> n >> k;
    heavy_light_decomposition hld(n);
    vector<int> a(n - 1), b(n - 1), c(n - 1);
    for(int i = 0; i < n - 1; ++i) {
        cin >> a[i] >> b[i] >> c[i];
        hld.add_edge(a[i], b[i]);
    }
    hld.build();
    vector<AOJ0367::node> nodes(n, AOJ0367::node(k, 0, 0, 0, 0));
    for(int i = 0; i < n - 1; ++i) {
        a[i] = hld.get_id(a[i]), b[i] = hld.get_id(b[i]);
        nodes[max(a[i], b[i])].cost_to_par = c[i];
    }
    segment_tree<AOJ0367> seg(nodes);
    int q; cin >> q;
    while(q--) {
        string type; cin >> type;
        if(type == "add") {
            int x, d; cin >> x >> d;
            x = hld.get_id(x);
            nodes[x].lcost += d;
            nodes[x].rcost += d;
            seg.update(x, nodes[x]);
        } else {
            int s, t; cin >> s >> t;
            vector<AOJ0367::node> v1, v2;
            const int lca = hld.get_lca(s, t);
            hld.vertex_path_query(s, lca, [&] (int l, int r) { v1.push_back(seg.query(l, r)); });
            hld.vertex_path_query(lca, t, [&] (int l, int r) { v2.push_back(seg.query(l, r)); });
            auto ans1 = v1.back(), ans2 = v2.back();
            for(int i = (int)v1.size() - 2; i >= 0; --i) {
                ans1 = AOJ0367::op(ans1, v1[i]);
            }
            for(int i = (int)v2.size() - 2; i >= 0; --i) {
                ans2 = AOJ0367::op(ans2, v2[i]);
            }
            cout << ans1.total_cost + ans2.total_cost << endl;
        }
    }
}
