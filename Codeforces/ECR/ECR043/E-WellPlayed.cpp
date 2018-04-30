#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll inf = 1e18;

ll mypow(ll x, ll n) {
    ll res = 1;
    while(n > 0) {
        if(n & 1) res = x * res;
        x *= x;
        n >>= 1;
    }
    return res;
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    b = min(b, n);
    ll pow2 = mypow(2, a);
    vector<ll> hp(n), dmg(n);
    vector<pair<ll, int>> v(n);
    for(int i = 0; i < n; ++i) {
        scanf("%lld %lld", &hp[i], &dmg[i]);
        v[i] = make_pair(max(0LL, hp[i] - dmg[i]), i);
    }
    sort(rbegin(v), rend(v));
    ll add_sum = 0;
    for(int i = 0; i < b; ++i) {
        add_sum += v[i].first;
    }
    ll ans = accumulate(begin(dmg), end(dmg), 0LL);
    if(b == 0) {
        cout << ans << endl;
        return 0;
    }
    ll add_max = add_sum;
    for(int i = 0; i < n; ++i) {
        ll tadd = add_sum;
        if(i < b) {
            tadd -= v[i].first;
        } else {
            tadd -= v[b - 1].first;
        }
        tadd += max(0LL, hp[v[i].second] * pow2 - dmg[v[i].second]);
        add_max = max(add_max, tadd);
    }
    cout << ans + add_max << endl;
}
