
// http://codeforces.com/contest/552/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n; cin >> n;
    ll ans = 0, d = 1, cnt = 1;
    while(n > 0) {
        ans += min(n, d * 9) * cnt;
        n -= min(n, d * 9);
        d *= 10;
        cnt += 1;
    }
    cout << ans << endl;
}
