#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    const int m = n;
    map<ll, int> cnt;
    for(int t = 2; t * t <= n; ++t) {
        while(n % t == 0) {
            cnt[t] += 1;
            n /= t;
        }
    }
    if(n > 1) cnt[n] += 1;
    bool ans = true;
    for(auto [v, c] : cnt) {
        ll cur = v;
        int tc = 0;
        while(cur <= m) {
            tc += m / cur;
            cur *= v;
        }
        ans &= tc >= c * 2;
    }

    cout << (ans ? "YES" : "NO") << endl;
}
