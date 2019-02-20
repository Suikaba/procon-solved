#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to, l, r;
};

using edges = vector<edge>;
using graph = vector<edges>;

void add_edge(graph& g, int from, int to, int l, int r) {
    g[from].push_back(edge{to, l, r});
    g[to].push_back(edge{from, l, r});
}

int main() {
    int n, m; cin >> n >> m;
    vector<int> xs;
    graph g(n);
    for(int i = 0; i < m; ++i) {
        int a, b, l, r; cin >> a >> b >> l >> r;
        a--, b--, ++r;
        add_edge(g, a, b, l, r);
        xs.push_back(l);
        xs.push_back(r);
    }
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    for(auto& es : g) {
        for(auto& e : es) {
            e.l = lower_bound(begin(xs), end(xs), e.l) - begin(xs);
            e.r = lower_bound(begin(xs), end(xs), e.r) - begin(xs);
        }
    }

    auto can_pass = [] (const edge& e, int l, int r) {
        return e.l <= l && r <= e.r;
    };

    const int sz = xs.size();
    int ans = 0;
    for(int l = 0; l < sz - 1; ++l) {
        auto check = [&] (const int r) -> bool {
            vector<bool> vis(n);
            function<void(int)> dfs = [&] (int v) {
                vis[v] = true;
                for(auto const& e : g[v]) {
                    if(vis[e.to] || !can_pass(e, l, r)) continue;
                    dfs(e.to);
                }
            };
            dfs(0);
            return vis[n - 1];
        };
        int lb = l, ub = sz + 1;
        while(ub - lb > 1) {
            const int mid = (ub + lb) >> 1;
            (check(mid) ? lb : ub) = mid;
        }
        ans = max(ans, xs[lb] - xs[l]);
    }

    if(ans == 0) {
        cout << "Nice work, Dima!" << endl;
    } else {
        cout << ans << endl;
    }
}
