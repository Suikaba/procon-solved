#include <bits/stdc++.h>
using namespace std;

// 解法
// ある部分木に注目した時、その部分木の値をどれだけ細かい粒度で変動させられるか、が重要
// 実のところ、v の子の部分木を最小変動量を l[0], ..., l[k - 1] とすれば、
// lcm(l[0], ..., l[k - 1]) * k が v の最小変動量である（少し考えればわかる）。
// なので、各部分木を調べたら、最小変動量の倍数で可能な限り大きい数だけ残せばよい。
// lcm とかは ll を超えうるので、適当に inf で抑えよう

using ll = long long;

constexpr ll inf = 1e18;

ll lcm(ll a, ll b) {
    const ll g = __gcd(a, b);
    a /= g, b /= g;
    if(inf / a / g <= b) return inf;
    return a * b * g;
}

ll mul(ll a, ll b) {
    if(inf / a <= b) return inf;
    return a * b;
}

int main() {
    int n; cin >> n;
    vector<ll> a(n);
    ll sum = 0;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int x, y; cin >> x >> y;
        g[x - 1].push_back(y - 1);
        g[y - 1].push_back(x - 1);
    }

    function<pair<ll, ll>(int, int)> dfs = [&] (int v, int p) {
        if(p != -1 && g[v].size() == 1u) {
            return make_pair(a[v], 1LL);
        }
        vector<pair<ll, ll>> ch;
        ll l = 1;
        for(auto to : g[v]) {
            if(to == p) continue;
            ch.push_back(dfs(to, v));
            l = lcm(l, ch.back().second);
        }
        ll t = inf; // target
        for(auto& c : ch) {
            t = min(t, c.first / l * l);
        }
        return make_pair(t * (ll)ch.size(), mul(l, ch.size()));
    };
    sum -= dfs(0, -1).first;

    cout << sum << endl;
}
