
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0341

#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

int main() {
    string t, b;
    cin >> t >> b;
    const int n = t.size(), m = b.size();

    vector<int> dp(m + 1);
    dp[0] = 1;
    for(int i = 0; i < n; ++i) {
        vector<int> nxt(m + 1);
        for(int j = 0; j < m; ++j) {
            if(t[i] == b[j]) {
                (nxt[j + 1] += dp[j]) %= mod;
            }
            (nxt[j] += dp[j]) %= mod;
        }
        (nxt[m] += dp[m]) %= mod;
        dp = move(nxt);
    }
    cout << dp.back() << endl;
}
