// http://codeforces.com/contest/575/problem/B

#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to, kind; // 0 := bidir, 1 := dir(legal), 2 := dir(illegal)
};

using edges = std::vector<edge>;
using graph = std::vector<edges>;

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


using ll = long long;

constexpr int mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    graph g(n);
    vector<int> up_cnt(n), down_cnt(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b, d; cin >> a >> b >> d;
        if(d == 0) {
            g[a - 1].push_back(edge{b - 1, 0});
            g[b - 1].push_back(edge{a - 1, 0});
        } else {
            g[a - 1].push_back(edge{b - 1, 1});
            g[b - 1].push_back(edge{a - 1, 2});
        }
    }

    lowest_common_ancestor lca(g, 0);

    const int max_k = 1 << 20;
    vector<int> pow2(max_k, 1);
    for(int i = 1; i < max_k; ++i) {
        pow2[i] = pow2[i - 1] * 2 % mod;
    }

    int k; cin >> k;
    int cur = 0;
    for(int i = 0; i < k; ++i) {
        int to; cin >> to;
        to--;
        if(cur == to) continue;
        const auto v = lca.query(cur, to);
        if(v != cur) {
            up_cnt[cur] += 1;
            up_cnt[v] -= 1;
        }
        if(v != to) {
            down_cnt[to] += 1;
            down_cnt[v] -= 1;
        }
        cur = to;
    }

    function<ll(int, int, int)> solve = [&] (int v, int p, int to_par_kind) {
        ll ans = 0;
        for(auto& e : g[v]) {
            if(e.to == p) continue;
            const int to_kind = (e.kind == 0 ? 0
                                             : e.kind == 1 ? 2 : 1);
            (ans += solve(e.to, v, to_kind)) %= mod;
            up_cnt[v] += up_cnt[e.to];
            down_cnt[v] += down_cnt[e.to];
        }
        if(to_par_kind == 1) {
            (ans += pow2[down_cnt[v]] - 1 + mod) %= mod;
        }
        if(to_par_kind == 2) {
            (ans += pow2[up_cnt[v]] - 1 + mod) %= mod;
        }
        return ans;
    };

    cout << solve(0, -1, 0) << endl;
}
