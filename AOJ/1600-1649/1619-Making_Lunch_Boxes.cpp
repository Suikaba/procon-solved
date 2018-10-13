// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1619

#include <bits/stdc++.h>
using namespace std;

string xor_s(string lhs, string const& rhs) {
    const int m = lhs.size();
    for(int i = 0; i < m; ++i) {
        if(rhs[i] == '1') {
            lhs[i] = (lhs[i] == '0' ? '1' : '0');
        }
    }
    return lhs;
}

int main() {
    int n, m;
    while(cin >> n >> m, n) {
        vector<string> v(n);
        for(int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        if(m <= 16) {
            vector<int> w(n);
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < m; ++j) {
                    w[i] |= (v[i][j] == '1') << j;
                }
            }
            vector<int> dp(1 << m, -1);
            dp[0] = 0;
            for(int i = 0; i < n; ++i) {
                auto nxt = dp;
                for(int S = 0; S < (1 << m); ++S) {
                    if(dp[S] == -1) continue;
                    nxt[S ^ w[i]] = max(nxt[S ^ w[i]], dp[S] + 1);
                }
                dp = move(nxt);
            }
            cout << dp[0] << endl;
        } else {
            const int n1 = n / 2, n2 = n - n1;
            const string z = string(m, '0');
            map<string, int> dp;
            for(int S = 0; S < (1 << n1); ++S) {
                string used = z;
                for(int i = 0; i < n; ++i) {
                    if(S & (1 << i)) {
                        used = xor_s(move(used), v[i]);
                    }
                }
                dp[used] = max(dp[used], __builtin_popcount(S));
            }
            int ans = 0;
            for(int S = 0; S < (1 << n2); ++S) {
                string used = z;
                for(int i = 0; i < n2; ++i) {
                    if(S & (1 << i)) {
                        used = xor_s(move(used), v[i + n1]);
                    }
                }
                if(dp.count(used) != 0) {
                    ans = max(ans, dp[used] + __builtin_popcount(S));
                }
            }
            cout << ans << endl;
        }
    }
}
