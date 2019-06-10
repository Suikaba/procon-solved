#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct edge {
    int to;
    ll cost;
    edge(int t, ll c) : to(t), cost(c) {}
};

using graph = vector<vector<edge>>;

int main() {
    int n, m; cin >> n >> m;
    graph g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b, c; cin >> a >> b >> c;
        g[a - 1].emplace_back(b - 1, c);
        g[b - 1].emplace_back(a - 1, c);
    }
    vector<ll> s(n);
    for(auto& ss : s) cin >> ss;

    vector<ll> cs;
    function<ll(int, int, ll)> dfs = [&] (int v, int p, ll st) {
        if(p != -1 && g[v].size() == 1u) return 0LL; // leaf
        vector<ll> ch;
        for(auto const& e : g[v]) {
            if(e.to == p) continue;
            ch.push_back(dfs(e.to, v, st) + st * e.cost);
        }
        const int idx = max_element(begin(ch), end(ch)) - begin(ch);
        for(int i = 0; i < (int)ch.size(); ++i) {
            if(i == idx) continue;
            cs.push_back(ch[i]);
        }
        if(p == -1) { // root
            cs.push_back(ch[idx]);
        }
        return ch[idx];
    };
    for(int i = 0; i < n; ++i) {
        dfs(i, -1, s[i]);
    }
    sort(begin(cs), end(cs), greater<>{});

    cout << accumulate(begin(cs), begin(cs) + min((int)cs.size(), m), 0LL) << endl;
}

