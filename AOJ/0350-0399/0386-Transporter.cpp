// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0386

#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

int main() {
    int n; cin >> n;
    string s, t;
    cin >> s >> t;
    vector<int> dp(26);
    dp[s[0] - 'a'] = 1;
    for(int i = 1; i < n - 1; ++i) {
        (dp[s[i] - 'a'] += dp[t[i] - 'a']) %= mod;
    }
    cout << dp[t.back() - 'a'] << endl;
}
