// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0626

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    string s; cin >> s;
    vector<vector<ll>> sum(n + 1, vector<ll>(3));
    auto to_i = [] (char c) {
                    if(c == 'J') return 0;
                    if(c == 'O') return 1;
                    if(c == 'I') return 2;
                    return -1;
                };
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 3; ++j) {
            sum[i + 1][j] = sum[i][j];
        }
        sum[i + 1][to_i(s[i])] += 1;
    }
    auto solve =
        [&to_i] (const string& t) {
            const int m = t.size();
            vector<ll> dp(4); dp[0] = 1;
            for(int i = 0; i < m; ++i) {
                dp[to_i(t[i]) + 1] += dp[to_i(t[i])];
            }
            return dp.back();
        };
    ll ans = max(solve("J" + s), solve(s + "I"));
    {
        ll tmp = solve(s);
        for(int i = 1; i < n; ++i) {
            ans = max(ans, tmp + (sum[i][0] * (sum[n][2] - sum[i][2])));
        }
    }
    cout << ans << endl;
}
