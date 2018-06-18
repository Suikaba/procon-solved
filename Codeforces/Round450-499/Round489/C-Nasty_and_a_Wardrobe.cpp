#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/992/problem/C

// 反省点
// mod とりわすれ && 場合分けを mod とったあとに付け加えたせいで x == mod がコーナーケースに．
// 最初からコーナーケースを考えましょう．特に見た目数学はコーナーケースが大切．

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
    ll x, k;
    cin >> x >> k;
    if(x == 0) {
        cout << 0 << endl;
        return 0;
    }
    x %= mod;
    if(k == 0) {
        cout << (2 * x) % mod << endl;
    } else if(k == 1) {
        ll res = (4 * x - 1) % mod;
        (res += mod) %= mod;
        cout << res << endl;
    } else {
        ll ans = (modpow(2, k + 1) * x - (modpow(2, k - 1) - 1 + mod) * 2) % mod;
        (ans += mod) %= mod;
        (ans = ans - 1 + mod) %= mod;
        cout << ans << endl;
    }
}
