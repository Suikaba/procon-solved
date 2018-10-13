// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2906

#include <bits/stdc++.h>
using namespace std;

int main() {
    int c, n, m; cin >> c >> n >> m;
    vector<int> dp(c + 1);
    vector<int> s(n), p(n);
    for(int i = 0; i < n; ++i) {
        cin >> s[i] >> p[i];
    }
    for(int i = 0; i < n; ++i) {
        auto nxt = dp;
        for(int j = 0; j + s[i] <= c; ++j) {
            nxt[j + s[i]] = max(nxt[j + s[i]], dp[j] + p[i]);
        }
        dp = move(nxt);
    }
    for(int k = 1; k <= m; ++k) {
        cout << dp[c / k] * k << endl;
    }
}
