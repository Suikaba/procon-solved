#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int inf = 1e9;
using graph = std::vector<std::vector<int>>;

class strongly_connected_component {
public:
    strongly_connected_component(int n) : g(n), rg(n), cmp(n), K(0) {}

    void add_edge(int s, int t) {
        g[s].push_back(t);
        rg[t].push_back(s);
    }

    void build() {
        const int n = g.size();
        std::vector<bool> used(n);
        for(int v = 0; v < n; ++v) {
            if(!used[v]) dfs(v, used);
        }
        std::fill(std::begin(used), std::end(used), false);
        int k = 0;
        for(int i = (int)vs.size() - 1; i >= 0; --i) {
            if(!used[vs[i]]) rdfs(vs[i], k++, used);
        }
        K = k;
    }

    int belongs(int v) const {
        return cmp[v];
    }

    graph build_graph() { // also call build()
        build();
        int const V = g.size();
        std::vector<std::set<int>> s(K);
        graph res(K);
        for(int v = 0; v < V; ++v) {
            for(const auto to : g[v]) {
                s[cmp[v]].insert(cmp[to]);
            }
        }
        for(int i = 0; i < K; ++i) { // remove self-loop edge
            for(auto j : s[i]) {
                if(i != j) res[i].push_back(j);
            }
        }
        return res;
    }

private:
    void dfs(int v, std::vector<bool>& used) {
        used[v] = true;
        for(const auto to : g[v]) {
            if(!used[to]) dfs(to, used);
        }
        vs.push_back(v);
    }
    void rdfs(int v, int k, std::vector<bool>& used) {
        used[v] = true;
        cmp[v] = k;
        for(auto to : rg[v]) {
            if(!used[to]) rdfs(to, k, used);
        }
    }

private:
    graph g, rg;
    std::vector<int> cmp, vs;
    int K;
};

using pii = pair<int, int>;


class union_find {
public:
    union_find(int n)
        : par_(n, -1)
    {}
    void init(int n) {
        par_.assign(n, -1);
    }

    int root(int x) {
        return par_[x] < 0 ? x : par_[x] = root(par_[x]);
    }

    bool unite(int x, int y) {
        x = root(x); y = root(y);
        if(x == y) {
            return false;
        } else {
            if(par_[x] < par_[y]) {
                par_[x] += par_[y];
                par_[y] = x;
            } else {
                par_[y] += par_[x];
                par_[x] = y;
            }
            return true;
        }
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    int size(int x) {
        return -par_[root(x)];
    }

private:
    std::vector<int> par_;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    map<pii, int> tmp;
    vector<int> tu(m), tv(m), tc(m);
    for(int i = 0; i < m; ++i) {
        int u, v, c; cin >> u >> v >> c;
        u--, v--;
        tu[i] = u, tv[i] = v, tc[i] = c;
        tmp[make_pair(u, v)] = max(tmp[make_pair(u, v)], c);
    }

    vector<int> u, v, c;
    for(auto& p : tmp) {
        u.push_back(p.first.first);
        v.push_back(p.first.second);
        c.push_back(p.second);
    }

    const int m2 = u.size();

    auto check = [&] (int ub) {
        strongly_connected_component scc(n);
        for(int i = 0; i < m2; ++i) {
            if(c[i] > ub) {
                scc.add_edge(u[i], v[i]);
            }
        }
        return scc;
    };
    int lb = -1, ub = inf + 1;
    strongly_connected_component scc(1);
    while(ub - lb > 1) {
        const auto mid = (lb + ub) >> 1;
        scc = check(mid);
        const int sz = scc.build_graph().size();
        (sz == n ? ub : lb) = mid;
    }

    scc = check(ub); // create scc
    scc.build();
    vector<int> ans;
    union_find uf(n);
    for(int i = 0; i < m; ++i) {
        if(tc[i] > ub) { // remain
            uf.unite(tu[i], tv[i]);
        }
    }
    for(int i = 0; i < m; ++i) {
        if(tc[i] <= ub) {
            if(uf.same(tu[i], tv[i])) {
                if(scc.belongs(tu[i]) > scc.belongs(tv[i])) {
                    ans.push_back(i + 1);
                }
            } else {
                if(uf.root(tu[i]) > uf.root(tv[i])) {
                    ans.push_back(i + 1);
                }
            }
        }
    }
    sort(begin(ans), end(ans));
    cout << ub << ' ' << ans.size() << endl;
    for(int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
    }
}
