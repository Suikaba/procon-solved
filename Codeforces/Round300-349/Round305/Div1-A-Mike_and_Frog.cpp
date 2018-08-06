#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll inf = 1e18;

int main() {
    int m;
    vector<ll> h(2), a(2), x(2), y(2);
    cin >> m;
    for(int i = 0; i < 2; ++i) {
        cin >> h[i] >> a[i] >> x[i] >> y[i];
    }

    vector<ll> t(2), cycle_sz(2);
    bool on_cycle = false;
    for(int i = 0; i < 2; ++i) {
        vector<ll> d(m, inf);
        d[h[i]] = 0;
        ll cur = h[i];
        while(true) {
            const ll nxt = (x[i] * cur + y[i]) % m;
            if(d[nxt] != inf) {
                cycle_sz[i] = (d[cur] - d[nxt] + 1);
                if(i == 0) {
                    on_cycle = d[a[i]] != inf && d[a[i]] >= d[nxt];
                }
                break;
            }
            d[nxt] = d[cur] + 1;
            cur = nxt;
        }
        t[i] = d[a[i]];
    }

    if(t[0] == inf || t[1] == inf) {
        cout << -1 << endl;
        return 0;
    }
    if(t[0] == t[1]) {
        cout << t[0] << endl;
        return 0;
    }
    if(!on_cycle) {
        cout << -1 << endl;
        return 0;
    }

    ll A = 1, B = 0; // calc (f^cycle[0])(x) = Ax + B
    for(int i = 0; i < cycle_sz[0]; ++i) {
        auto nA = (A * x[1]) % m;
        auto nB = (y[1] + x[1] * B) % m;
        A = nA, B = nB;
    }

    ll cur_h2 = h[1];
    for(int i = 0; i < t[0]; ++i) {
        cur_h2 = (x[1] * cur_h2 + y[1]) % m;
    }

    ll cnt = 0;
    while(cur_h2 != a[1] && cnt < m) {
        cur_h2 = (cur_h2 * A + B) % m;
        cnt += 1;
    }

    if(cnt < m && cur_h2 == a[1]) {
        cout << t[0] + cycle_sz[0] * cnt << endl;
    } else {
        cout << -1 << endl;
    }
}
