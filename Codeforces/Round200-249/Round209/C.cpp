#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
    ios_base::sync_with_stdio(false); cin.tie(0);

    ll n, x; cin >> n >> x;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    const ll an = a.back();

    ll ans = modpow(x, accumulate(begin(a), end(a) - 1, 0LL));
    ll m = 0;
    map<ll, ll> cnt;
    for(int i = 0; i < n; ++i) {
        cnt[an - a[i]] += 1;
    }
    int last = 0;
    while(true) {
        auto p = *cnt.begin();
        //cout << p.first << ' ' << p.second << endl;
        cnt.erase(begin(cnt));
        if(p.second % x == 0) {
            cnt[p.first + 1] += p.second / x;
            last = p.first + 1;
        } else {
            m = min(an, m + last);
            break;
        }
    }
    ans = (ans * modpow(x, m)) % mod;
    cout << ans << endl;
}
