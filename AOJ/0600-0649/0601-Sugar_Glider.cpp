// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0601

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e18;

struct edge {
    int to;
    ll cost;
};

using graph = vector<vector<edge>>;

void add_edge(graph& g, int from, int to, int cost) {
    g[from].push_back(edge{to, cost});
    g[to].push_back(edge{from, cost});
}

int main() {
    int n, m, x; cin >> n >> m >> x;
    vector<int> h(n);
    for(int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    graph g(n);
    for(int i = 0; i < m; ++i) {
        int a, b, t; cin >> a >> b >> t;
        add_edge(g, a - 1, b - 1, t);
    }

    vector<ll> d(n, inf);
    d[0] = 0;
    using state = tuple<ll, ll, int>;
    priority_queue<state, vector<state>, greater<>> que;
    que.emplace(0, x, 0);
    ll ans = -1;
    while(!que.empty()) {
        ll cur_t, cur_h; int v;
        tie(cur_t, cur_h, v) = que.top(); que.pop();
        if(v == n - 1) {
            ans = cur_t + abs(cur_h - h[n - 1]);
            break;
        }
        if(d[v] < cur_t) continue;
        for(auto& e : g[v]) {
            ll nh = cur_h - e.cost, nt = cur_t + e.cost;
            if(nh < 0) {
                ll up = -nh;
                if(cur_h + up > h[v]) continue;
                nh = 0;
                nt += up;
            }
            if(nh > h[e.to]) {
                ll down = nh - h[e.to];
                nt += down;
                nh = h[e.to];
            }
            if(d[e.to] <= nt) continue;
            que.emplace(nt, nh, e.to);
            d[e.to] = nt;
        }
    }

    cout << ans << endl;
}
