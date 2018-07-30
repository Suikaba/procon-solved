
// http://codeforces.com/contest/545/problem/E

// 反省
// なんで prim で行けると思ったのか，これがわからない．流石に無思考過ぎませんか．
// 簡単な問題こそ丁寧にやらないとダメだ．
// あと最初の実装方針も良くなかった．

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e18;

struct edge {
    int from, to, id;
    ll w;
    bool operator<(edge const& e) const {
        return w < e.w;
    }
};

using edges = vector<edge>;
using graph = vector<edges>;

void add_edge(graph& g, int id, int u, int v, ll c) {
    g[u].push_back(edge{u, v, id, c});
    g[v].push_back(edge{v, u, id, c});
}

int main() {
    int n, m;
    cin >> n >> m;
    graph g(n);
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(g, i + 1, a - 1, b - 1, c);
    }
    int s; cin >> s;
    s--;

    using state = pair<ll, int>;
    priority_queue<state, vector<state>, greater<state>> que;
    vector<ll> d(n, inf);
    d[s] = 0;
    que.emplace(0, s);
    while(!que.empty()) {
        auto p = que.top();
        que.pop();
        if(d[p.second] < p.first) continue;
        for(auto& e : g[p.second]) {
            if(d[e.to] > p.first + e.w) {
                d[e.to] = p.first + e.w;
                que.emplace(d[e.to], e.to);
            }
        }
    }

    vector<pair<ll, int>> tr(n, make_pair(inf, -1));
    for(auto& es : g) {
        for(auto& e : es) {
            if(d[e.from] + e.w == d[e.to]) {
                tr[e.to] = min(tr[e.to], make_pair(e.w, e.id));
            }
        }
    }
    ll ans = 0;
    vector<int> ids;
    for(int i = 0; i < n; ++i) {
        if(tr[i].second != -1) {
            ans += tr[i].first;
            ids.push_back(tr[i].second);
        }
    }
    cout << ans << endl;
    sort(begin(ids), end(ids));
    for(int i = 0; i < (int)ids.size(); ++i) {
        cout << ids[i] << " \n"[i + 1 == (int)ids.size()];
    }
}
