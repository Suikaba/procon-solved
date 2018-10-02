// http://codeforces.com/contest/1041/problem/D

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll = long long;

int main() {
    int n, h; cin >> n >> h;
    vector<int> l(n), r(n), xs = {2000000001};
    for(int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        xs.push_back(l[i]);
        xs.push_back(r[i]);
    }
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    const int m = xs.size();
    vector<int> z(m, 1), sum(m);
    for(int i = 0; i < n; ++i) {
        l[i] = lower_bound(begin(xs), end(xs), l[i]) - begin(xs);
        r[i] = lower_bound(begin(xs), end(xs), r[i]) - begin(xs);
        z[l[i]] = 0;
    }
    for(int i = 0; i + 1 < m; ++i) {
        sum[i + 1] = sum[i] + z[i] * (xs[i + 1] - xs[i]);
    }

    int ans = 0;
    for(int i = 0; i + 1 < m; ++i) {
        const int idx = lower_bound(begin(sum), end(sum), sum[i] + h) - begin(sum) - 1;
        ans = max(ans, xs[idx] - xs[i] + h - (sum[idx] - sum[i]));
    }

    cout << ans << endl;
}
