#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1, s2, virus; cin >> s1 >> s2 >> virus;
    const int n = s1.size(), m = s2.size();
    const int vlen = virus.size();

    vector<vector<int>> vnxt(vlen, vector<int>(26));
    for(int i = 0; i < vlen; ++i) {
        for(int j = 0; j < 26; ++j) {
            const auto s = virus.substr(0, i) + (char)('A' + j);
            int match = 0;
            for(int k = s.size(); k >= 1; --k) {
                const auto ss = s.substr(s.size() - k);
                const auto vs = virus.substr(0, k);
                if(ss == vs) {
                    match = k;
                    break;
                }
            }
            vnxt[i][j] = match;
        }
    }

    vector<vector<vector<string>>> dp(n + 1, vector<vector<string>>(m + 1, vector<string>(vlen + 1, "$")));
    dp[0][0][0] = "";
    auto cmp_assign = [] (string& dst, string const& s) {
        if(dst == "$" || dst.size() < s.size()) {
            dst = s;
        }
    };
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < vlen; ++k) {
                if(dp[i][j][k] == "$") continue;
                if(s1[i] == s2[j]) {
                    const int nv = vnxt[k][s1[i] - 'A'];
                    cmp_assign(dp[i + 1][j + 1][nv], dp[i][j][k] + s1[i]);
                }
                cmp_assign(dp[i + 1][j][k], dp[i][j][k]);
                cmp_assign(dp[i][j + 1][k], dp[i][j][k]);
            }
        }
    }

    string ans;
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= m; ++j) {
            for(int k = 0; k < vlen; ++k) {
                if(dp[i][j][k] == "$") continue;
                cmp_assign(ans, dp[i][j][k]);
            }
        }
    }
    if(ans.empty()) {
        cout << "0" << endl;
    } else {
        cout << ans << endl;
    }
}
