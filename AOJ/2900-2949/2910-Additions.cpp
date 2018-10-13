// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2910

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 2e9;

int main() {
    int n; cin >> n;
    string s; cin >> s;
    const int m = s.size();

    vector<vector<vector<ll>>> val(m, vector<vector<ll>>(10, vector<ll>(11, inf)));
    for(int i = 0; i < m; ++i) {
        for(int len = 0; len < 10; ++len) {
            if(i - len < 0) continue;
            auto t = s.substr(i - len, len + 1);
            int need = 0;
            for(int j = 0; j <= len; ++j) {
                if(j == 0) {
                    if((len != 0 && t[j] == '0') || !isdigit(t[j])) {
                        need += 1;
                        t[j] = len == 0 ? '0' : '1';
                    }
                } else {
                    if(!isdigit(t[j])) {
                        need += 1;
                        t[j] = '0';
                    }
                }
            }
            auto check =
                [&] (int p) {
                    return ((p == 0 && t[p] == (len == 0 ? '0' : '1')) || (p != 0 && t[p] == '0'));
                };
            int idx = 0;
            val[i][len][need] = stol(t);
            while(idx < (int)t.size()) {
                while(idx < (int)t.size() && check(idx)) idx++;
                if(idx < (int)t.size()) {
                    need += 1;
                    t[idx] = (len != 0 && idx == 0) ? '1' : '0';
                    val[i][len][need] = stol(t);
                }
                idx++;
            }
        }
    }
    //cout << val[9][9][10] << endl;
    // 0: => //, 1: => +
    vector<vector<vector<ll>>> dp(m + 1, vector<vector<ll>>(m + 1, vector<ll>(2, inf)));
    dp[0][0][1] = 0;
    for(int i = 0; i < m; ++i) {
        for(int cnt = 0; cnt <= m; ++cnt) {
            for(int pre = 0; pre <= 9; ++pre) {
                for(int x = 0; x <= pre + 1; ++x) {
                    if(i - pre < 0 || cnt + x > m) continue;
                    dp[i + 1][cnt + x][0] = min(dp[i + 1][cnt + x][0], dp[i - pre][cnt][1] + val[i][pre][x]);
                }
            }
            const int add = (s[i] != '+');
            if(cnt + add <= m) {
                dp[i + 1][cnt + add][1] = min(dp[i + 1][cnt + add][1], dp[i][cnt][0]);
            }
        }
    }
    ll ans = -1;
    for(int i = 0; i <= m; ++i) {
        if(dp[m][i][0] <= n) {
            ans = i;
            break;
        }
    }
    cout << ans << endl;
}
