#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll mod = 1e9 + 7;

struct edge {
    int to, type;
    edge(int t, int ty) : to(t), type(ty) {}
};

using edges = vector<edge>;
using graph = vector<edges>;

ll modpow(ll x, ll n) {
    ll res = 1;
    while(n > 0) {
        if(n & 1) (res *= x) %= mod;
        (x *= x) %= mod;
        n >>= 1;
    }
    return res;
}

int main() {
    ll n, k; cin >> n >> k;
    graph g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b, t; cin >> a >> b >> t;
        g[a - 1].emplace_back(b - 1, t);
        g[b - 1].emplace_back(a - 1, t);
    }

    vector<bool> used(n);
    function<int(int, int)> dfs = [&] (int v, int p) {
        int res = 1;
        used[v] = true;
        for(auto const& e : g[v]) {
            if(e.to == p || e.type == 1 || used[e.to]) continue;
            res += dfs(e.to, v);
        }
        return res;
    };
    ll ans = modpow(n, k);
    for(int i = 0; i < n; ++i) {
        if(used[i]) continue;
        (ans += mod - modpow(dfs(i, -1), k)) %= mod;
    }
    cout << ans << endl;
}