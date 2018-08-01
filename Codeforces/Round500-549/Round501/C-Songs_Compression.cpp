
// http://codeforces.com/contest/1015/problem/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    vector<ll> sub(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        sub[i] = a[i] - b[i];
    }
    sort(rbegin(sub), rend(sub));
    ll tot = accumulate(begin(a), end(a), 0LL);
    int ans = 0;
    for(int i = 0; i < n && tot > m; ++i) {
        tot -= sub[i];
        ans += 1;
    }
    if(tot > m) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}
