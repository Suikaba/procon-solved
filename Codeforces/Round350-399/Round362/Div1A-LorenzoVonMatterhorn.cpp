#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/696/problem/A

using ll = long long;
using pll = pair<ll, ll>;

int main() {
    int q;
    cin >> q;
    map<pll, ll> cost;
    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            ll u, v, w;
            cin >> u >> v >> w;
            while(u != v) {
                if(u < v) swap(u, v);
                cost[make_pair(u / 2, u)] += w;
                u /= 2;
            }
        } else {
            ll v, u;
            cin >> v >> u;
            ll ans = 0;
            while(v != u) {
                if(u < v) swap(u, v);
                ans += cost[make_pair(u / 2, u)];
                u /= 2;
            }
            cout << ans << endl;
        }
    }
}
