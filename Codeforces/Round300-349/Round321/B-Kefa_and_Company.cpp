// http://codeforces.com/contest/580/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, d; cin >> n >> d;
    vector<int> m(n), s(n);
    for(int i = 0; i < n; ++i) {
        cin >> m[i] >> s[i];
    }
    auto xs = m;
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    for(int i = 0; i < n; ++i) {
        m[i] = lower_bound(begin(xs), end(xs), m[i]) - begin(xs);
    }
    const int sz = xs.size();
    vector<ll> sum(sz + 1);
    for(int i = 0; i < n; ++i) {
        sum[m[i] + 1] += s[i];
    }
    for(int i = 0; i < sz; ++i) {
        sum[i + 1] += sum[i];
    }
    ll ans = 0;
    for(int i = 0; i < sz; ++i) {
        const int idx = lower_bound(begin(xs), end(xs), xs[i] + d) - begin(xs);
        ans = max(ans, sum[idx] - sum[i]);
    }
    cout << ans << endl;
}
