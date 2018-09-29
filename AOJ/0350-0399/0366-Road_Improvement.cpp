// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0366

#include <bits/stdc++.h>
using namespace std;

class strongly_connected_component {
    using graph = std::vector<std::vector<int>>;
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

int main() {
    int n, m; cin >> n >> m;
    strongly_connected_component scc(n);
    for(int i = 0; i < m; ++i) {
        int s, t; cin >> s >> t;
        scc.add_edge(s, t);
    }
    auto g = scc.build_graph();
    n = g.size();
    if(n == 1) {
        cout << 0 << endl;
        return 0;
    }
    vector<int> in(n), out(n);
    for(int i = 0; i < n; ++i) {
        out[i] = g[i].size();
        for(auto to : g[i]) {
            in[to] += 1;
        }
    }
    int scnt = 0, tcnt = 0;
    for(int i = 0; i < n; ++i) {
        scnt += in[i] == 0;
        tcnt += out[i] == 0;
    }
    cout << max(scnt, tcnt) << endl;
}
