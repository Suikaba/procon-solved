http://codeforces.com/contest/584/problem/B

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
    int n; cin >> n;
    ll ans = (modpow(27, n) - modpow(7, n) + mod) % mod;
    cout << ans << endl;
}
