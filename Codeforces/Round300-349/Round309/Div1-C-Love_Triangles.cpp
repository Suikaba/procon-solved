
// http://codeforces.com/contest/553/problem/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

constexpr int mod = 1e9 + 7;

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
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        g[a - 1].emplace_back(b - 1, !c);
        g[b - 1].emplace_back(a - 1, !c);
    }

    vector<int> col(n, -1);
    function<bool(int, int)> coloring = [&] (int v, int c) {
        if(col[v] != -1) return col[v] != c; // is bipartite ?
        col[v] = c;
        bool res = false;
        for(auto& e : g[v]) {
            res |= coloring(e.first, c ^ e.second);
        }
        return res;
    };
    bool bipartite = true;
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(col[i] != -1) continue;
        bipartite &= !coloring(i, 0);
        cnt++;
    }

    if(!bipartite) {
        cout << 0 << endl;
    } else {
        cout << modpow(2, cnt - 1) << endl;
    }
}
