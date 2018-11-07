#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 1e9 + 7;

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    int root(int x) {
        return par[x] < 0 ? x : par[x] = root(par[x]);
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    int& operator[](int i) {
        return par[i];
    }

private:
    vector<int> par;
};

ll mul(ll a, ll b) {
    a %= mod, b %= mod;
    return a * b % mod;
}

ll add(ll a, ll b) {
    a %= mod, b %= mod;
    return (a + b) % mod;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    const int pow_sz = max(n + 2, k + 2);
    vector<ll> pow2(pow_sz, 1);
    for(int i = 0; i + 1 < pow_sz; ++i) {
        pow2[i + 1] = mul(pow2[i], 2);
    }
    vector<ll> c(n);
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    map<ll, vector<pair<int, int>>> g;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        a--, b--;
        assert(c[a] != c[b]);
        g[c[a] ^ c[b]].emplace_back(a, b);
    }
    ll ans = mul(pow2[k], pow2[n]);
    union_find uf(n);
    for(auto& p : g) {
        int cnt = n;
        for(auto& e : p.second) {
            cnt -= uf.unite(e.first, e.second);
        }
        ans = add(ans, mod - pow2[n] + pow2[cnt]);
        for(auto& e : p.second) {
            uf[e.first] = uf[e.second] = -1;
        }
    }

    cout << ans << endl;
}
