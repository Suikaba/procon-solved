
// http://codeforces.com/contest/1015/problem/F

#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

int dp[256][256][256];

int main() {
    int n;
    string s;
    cin >> n >> s;
    const int m = s.size();
    vector<vector<int>> match(m + 1, vector<int>(2)); // failed on [1..i] (1-indexed) -> match [1..match[i]]
    for(int i = 0; i < m; ++i) {
        for(int tl = 0; tl < 2; ++tl) {
            auto t = s.substr(0, i); // [0..i]
            t += tl == 0 ? '(' : ')';
            const int len = i + 1;
            string s1, s2;
            for(int j = 0; j < len; ++j) {
                s1 += s[j];
                s2 = t[i - j] + s2;
                if(s1 == s2) {
                    match[i][tl] = j + 1;
                }
            }
        }
    }
    match[m][0] = match[m][1] = m; // accept

    dp[0][0][0] = 1;
    for(int i = 0; i < 2 * n; ++i) {
        for(int j = 0; j <= m; ++j) {
            for(int k = 0; k < 2 * n; ++k) {
                (dp[i + 1][match[j][0]][k + 1] += dp[i][j][k]) %= mod;
                if(k != 0) {
                    (dp[i + 1][match[j][1]][k - 1] += dp[i][j][k]) %= mod;
                }
            }
        }
    }

    cout << dp[2 * n][m][0] << endl;
}
