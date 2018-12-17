#include <bits/stdc++.h>
using namespace std;

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

    void path_query(int u, int v, std::function<void(int, int)> f) { // vertex
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

struct RURS {
    struct type1 {
        int val, size;
        type1(int v, int s) : val(v), size(s) {}
    };
    using type2 = int;

    static type1 id1() { return type1(0, 0); } // initialize: seg<RURS>(n, type1(0, 1))
    static type2 id2() { return std::numeric_limits<type2>::min() / 2; }

    static type1 op1(type1 const& l, type1 const& r) {
        return type1(l.val + r.val, l.size + r.size);
    }
    static type1 op2(type1 const& l, type2 const& r) {
        return r != id2() ? type1(r * l.size, l.size) : l;
    }
    static type2 op3(type2 const& l, type2 const& r) {
        return r != id2() ? r : l;
    }
};


template <typename Monoid>
class lazy_segment_tree {
    using T1 = typename Monoid::type1;
    using T2 = typename Monoid::type2;

public:
    lazy_segment_tree(std::vector<T1> const& init)
        : sz(init.size()), n(expand(init.size())), h(std::ceil(std::log2(init.size()))),
          data(n * 2, Monoid::id1()), lazy(n * 2, Monoid::id2())
    {
        std::copy(std::begin(init), std::end(init), std::begin(data) + n);
        for(int i = n - 1; i >= 1; --i) {
            data[i] = Monoid::op1(data[i * 2], data[i * 2 + 1]);
        }
    }
    lazy_segment_tree(int n_, T1 init = Monoid::id1())
        : lazy_segment_tree(std::vector<T1>(n_, init))
    {}

    T1 query(int l, int r) {
        l += n, r += n;
        for(int i = h; i > 0; --i) {
            push(l >> i), push(r >> i);
        }
        T1 res1 = Monoid::id1(), res2 = Monoid::id1();
        while(l < r) {
            if(l & 1) res1 = Monoid::op1(res1, Monoid::op2(data[l], lazy[l])), ++l;
            if(r & 1) --r, res2 = Monoid::op1(res2, Monoid::op2(data[r], lazy[r]));
            l /= 2, r /= 2;
        }
        return Monoid::op1(res1, res2);
    }

    void update(int l, int r, T2 val) {
        assert(0 <= l && l <= r && r <= sz);
        l += n, r += n;
        for(int i = h; i > 0; --i) {
            push(l >> i), push(r >> i);
        }
        int tl = l, tr = r;
        while(l < r) {
            if(l & 1) lazy[l] = Monoid::op3(lazy[l], val), ++l;
            if(r & 1) --r, lazy[r] = Monoid::op3(lazy[r], val);
            l /= 2, r /= 2;
        }
        while(tr /= 2, tl /= 2) {
            if(lazy[tl] == Monoid::id2()) update(tl);
            if(lazy[tr] == Monoid::id2()) update(tr);
        }
    }

private:
    int expand(int n_) const {
        int res = 1;
        while(res < n_) res <<= 1;
        return res;
    }

    void push(int node) {
        if(lazy[node] == Monoid::id2()) return;
        if(node < n) {
            lazy[node * 2] = Monoid::op3(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = Monoid::op3(lazy[node * 2 + 1], lazy[node]);
        }
        data[node] = Monoid::op2(data[node], lazy[node]);
        lazy[node] = Monoid::id2();
    }

    void update(int node) {
        if(node * 2 + 1 >= (int)data.size()) return; // for n == max_r
        data[node] = Monoid::op1(Monoid::op2(data[node * 2], lazy[node * 2]),
                                 Monoid::op2(data[node * 2 + 1], lazy[node * 2 + 1]));
    }

private:
    int const sz, n, h;
    std::vector<T1> data;
    std::vector<T2> lazy;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    heavy_light_decomposition hld(n);
    lazy_segment_tree<RURS> seg(n, RURS::type1(0, 1));
    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b; a--, b--;
        hld.add_edge(a, b);
    }
    hld.build();
    int q; cin >> q;
    for(int i = 0; i < q; ++i) {
        int c, v; cin >> c >> v;
        v--;
        if(c == 1) {
            hld.subtree_query(v, [&] (int l, int r) { seg.update(l, r, 1); });
        } else if(c == 2) {
            hld.path_query(0, v, [&] (int l, int r) { seg.update(l, r, 0); });
        } else {
            const int id = hld.get_id(v);
            cout << seg.query(id, id + 1).val << "\n";
        }
    }
}
