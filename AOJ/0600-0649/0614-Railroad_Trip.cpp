// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0614

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, m; cin >> n >> m;
    vector<int> p(m);
    for(int i = 0; i < m; ++i) {
        cin >> p[i];
    }
    vector<int> a(n - 1), b(n - 1), c(n - 1);
    for(int i = 0; i < n - 1; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }

    vector<int> sum(n);
    for(int i = 0; i + 1 < m; ++i) {
        const int l = min(p[i], p[i + 1]), r = max(p[i], p[i + 1]);
        sum[l - 1] += 1, sum[r - 1] -= 1;
    }
    for(int i = 0; i + 1 < n; ++i) {
        sum[i + 1] += sum[i];
    }

    ll ans = 0;
    for(int i = 0; i < n - 1; ++i) {
        ans += min(1LL * a[i] * sum[i], 1LL * b[i] * sum[i] + c[i]);
    }
    cout << ans << endl;
}
