// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0644

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n; cin >> n;
    vector<int> l(n), sum(n + 1);
    for(int i = 0; i < n; ++i) {
        cin >> l[i];
        sum[i + 1] = sum[i] + l[i];
    }

    const int max_l = n * 1000 + 1;
    vector<vector<int>> dp(n + 1, vector<int>(max_l, inf));
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j < i; ++j) {
            for(int mini_l = 0; mini_l < max_l; ++mini_l) {
                const int nmin = min(mini_l, sum[i] - sum[j]);
                const int nmax = max(dp[j][mini_l], sum[i] - sum[j]);
                dp[i][nmin] = min(dp[i][nmin], nmax);
            }
        }
        if(i != n) {
            dp[i][sum[i]] = sum[i];
        }
    }

    int ans = inf;
    for(int i = 0; i < max_l; ++i) {
        if(dp[n][i] == inf) continue;
        ans = min(ans, dp[n][i] - i);
    }
    cout << ans << endl;
}
