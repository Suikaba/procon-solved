// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    const int max_p = 1 << 18;

    int l, r; cin >> l >> r;

    vector<int> ns(r - l + 1);
    for(int i = 0; i <= r - l; ++i) {
        ns[i] = i + l;
    }
    vector<int> cnt(r - l + 1);
    vector<bool> is_prime(max_p, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < max_p; ++i) {
        if(is_prime[i]) {
            for(int j = i + i; j < max_p; j += i) is_prime[j] = false;
            ll x = i;
            while(x <= r) {
                for(int j = (l + x - 1) / x * x; j <= r; j += x) {
                    cnt[j - l] += 1;
                    ns[j - l] /= i;
                }
                x *= i;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < r - l + 1; ++i) {
        if(ns[i] > 1) cnt[i] += 1;
        ans += is_prime[cnt[i]];
    }
    cout << ans << endl;
}
