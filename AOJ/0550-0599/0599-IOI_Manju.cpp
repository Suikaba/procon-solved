// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0599

#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n; cin >> m >> n;
    vector<int> p(m), sum(m + 1);
    for(int i = 0; i < m; ++i) {
        cin >> p[i];
    }
    sort(rbegin(p), rend(p));
    for(int i = 0; i < m; ++i) {
        sum[i + 1] = sum[i] + p[i];
    }
    vector<int> c(n), e(n);
    for(int i  = 0;  i < n; ++i) {
        cin >> c[i] >> e[i];
    }

    vector<int> dp(m + 1);
    for(int i = 0; i < n; ++i) {
        auto nxt = dp;
        for(int j = 0; j < m; ++j) {
            const int k = min(j + c[i], m);
            nxt[k] = max(nxt[k], dp[j] + sum[k] - sum[j] - e[i]);
        }
        dp = move(nxt);
    }

    cout << *max_element(begin(dp), end(dp)) << endl;
}
