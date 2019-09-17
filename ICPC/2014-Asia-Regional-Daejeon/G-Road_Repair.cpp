#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to, cost, value;
};

using pii = pair<int, int>;
using graph = vector<vector<edge>>;

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
        p += n;
        //dat[p += n] = val;
        dat[p] = max(dat[p], val);
        while(p /= 2) {
            dat[p] = Monoid::op(dat[p * 2], dat[p * 2 + 1]);
        }
    }

    // [l, r)
    T query(int l, int r) const {
        assert(0 <= l && l <= r && r <= sz);
        l += n, r += n;
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

struct RMQ {
    using type = int;
    static type id() {
        return std::numeric_limits<type>::min();
    }
    static type op(type const& l, type const& r) {
        return std::max(l, r);
    }
};

int solve(vector<vector<pii>> vs, int max_c) {
    const int n = vs.size();
    vector<int> xs;
    for(int i = 0; i < n; ++i) {
        for(auto c : vs[i]) {
            xs.push_back(c.first);
        }
    }
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    const int sz = xs.size();
    segment_tree<RMQ> seg(sz);
    int res = 0;
    for(int i = 0; i < n; ++i) {
        const int m = vs[i].size();
        for(int j = 0; j < m; ++j) {
            if(vs[i][j].first > max_c) break;
            const int ub = upper_bound(begin(xs), end(xs), max_c - vs[i][j].first) - begin(xs);
            res = max(res, seg.query(0, ub) + vs[i][j].second);
        }
        for(int j = 0; j < m; ++j) {
            const int idx = lower_bound(begin(xs), end(xs), vs[i][j].first) - begin(xs);
            seg.update(idx, vs[i][j].second);
        }
    }
    return res;
}

int centroid_decomposition(graph const& g, int max_c) {
    const int n = g.size();
    int res = 0;
    vector<int> sz(n);
    vector<bool> used(n);
    function<void(int, int)> calc_sz = [&] (int v, int p) {
        sz[v] = 1;
        for(auto& e : g[v]) {
            if(e.to == p || used[e.to]) continue;
            calc_sz(e.to, v);
            sz[v] += sz[e.to];
        }
    };
    function<int(int, int, int)> find_c = [&] (int v, int p, const int nn) {
        for(auto& e : g[v]) {
            if(e.to == p || used[e.to]) continue;
            if(nn / 2 < sz[e.to]) {
                return find_c(e.to, v, nn);
            }
        }
        return v;
    };
    function<void(int)> dfs = [&] (int v) {
        calc_sz(v, -1);
        const int c = find_c(v, -1, sz[v]);
        used[c] = true;
        for(auto& e : g[c]) {
            if(used[e.to]) continue;
            dfs(e.to);
        }

        vector<vector<int>> costs = {{0}}, values = {{0}};
        vector<vector<pii>> vs = {{make_pair(0, 0)}};
        for(auto& e : g[c]) {
            if(used[e.to]) continue;
            vector<pii> tvs;
            function<void(int, int, int, int)> enumerate = [&] (int u, int p, int cost, int value) {
                if(cost > max_c) return;
                tvs.emplace_back(cost, value);
                for(auto& ee : g[u]) {
                    if(ee.to == p || used[ee.to]) continue;
                    enumerate(ee.to, u, cost + ee.cost, value + ee.value);
                }
            };
            enumerate(e.to, c, e.cost, e.value);
            vs.push_back(move(tvs));
        }
        res = max(res, solve(move(vs), max_c));
        used[c] = false;
    };
    dfs(0);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        graph g(n);
        for(int i = 0; i < n - 1; ++i) {
            int a, b, cost, value;
            cin >> a >> b >> cost >> value;
            g[a - 1].push_back(edge{b - 1, cost, value});
            g[b - 1].push_back(edge{a - 1, cost, value});
        }
        int max_c; cin >> max_c;
        cout << centroid_decomposition(g, max_c) << endl;
    }
}
