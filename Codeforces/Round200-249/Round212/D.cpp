#include <bits/stdc++.h>
using namespace std;

// tag: 貪欲(greedy)
// 解法
// 結局以下の問題が解ければ良い。
//   サイズ v_1, ... v_n が与えられて、k 回マージするとする。
//   v_i と v_j をマージしたときのコストは、v_i + v_j + 1 であり、かつマージ後のサイズは 2 * (v_i + v_j) + 1 になる。
//   最小コストは？
// これはサイズの小さい方から2つ貪欲に選ぶのが最適。

using ll = long long;
using pll = pair<ll, int>;

struct edge {
    int to;
    ll cost;
};

using edges = vector<edge>;
using graph = vector<edges>;

int main() {
    int n, m, p, q; cin >> n >> m >> p >> q;
    graph g(n);
    int e1 = -1, e2 = -1;
    for(int i = 0; i < m; ++i) {
        int x, y, l; cin >> x >> y >> l;
        g[x - 1].push_back({y - 1, l});
        g[y - 1].push_back({x - 1, l});
        e1 = x - 1, e2 = y - 1;
    }

    vector<bool> vis(n);
    function<ll(int)> dfs = [&] (int v) {
        vis[v] = true;
        ll res = 0;
        for(const auto& e : g[v]) {
            res += e.cost;
            if(vis[e.to]) continue;
            res += dfs(e.to);
        }
        return res;
    };
    priority_queue<pll, vector<pll>, greater<>> que;
    for(int i = 0; i < n; ++i) {
        if(vis[i]) continue;
        que.emplace(dfs(i) / 2, i);
    }

    if((int)que.size() < q || (int)que.size() - p > q) {
        cout << "NO" << endl;
        return 0;
    }

    vector<int> u, v;
    for(int i = 0; p > 0 && que.size() >= 2u && que.size() - q > 0; ++i, --p) {
        const auto p1 = que.top(); que.pop();
        const auto p2 = que.top(); que.pop();
        que.emplace(2 * (p1.first + p2.first) + 1, p1.second);
        u.push_back(p1.second);
        v.push_back(p2.second);
        e1 = p1.second, e2 = p2.second;
    }

    if(p > 0 && e1 == -1) {
        cout << "NO" << endl;
        return 0;
    }
    while(p--) {
        u.push_back(e1);
        v.push_back(e2);
    }

    cout << "YES" << endl;
    for(int i = 0; i < (int)u.size(); ++i) {
        cout << u[i] + 1 << ' ' << v[i] + 1 << "\n";
    }
}
