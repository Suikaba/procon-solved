#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2434

// 反省
// うーん特に無い．dpテーブルの初期化に1回失敗したけどすぐ気づけるミスだったしなあ．
// 実装時間計り忘れましたね……．

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> vi(n), da(n), vo(n);
    for(int i = 0; i < n; ++i) {
        cin >> vi[i] >> da[i] >> vo[i];
    }

    vector<double> p(m + 1, 0);
    p[0] = 1;
    for(int i = 0; i < m; ++i) {
        vector<double> nxt(m + 1);
        for(int i = 0; i <= m; ++i) {
            nxt[i] += p[i] * 2 / 3.0;
            if(i != m) {
                nxt[i + 1] += p[i] / 3.0;
            }
        }
        p = move(nxt);
    }
    for(int i = 0; i < m; ++i) {
        p[i + 1] += p[i];
    }

    auto calc = [&](vector<int> const& v) {
        vector<vector<double>> dp(m + 1, vector<double>(4));
        for(int i = 0; i < m + 1; ++i) {
            dp[i][0] = dp[i][3] = 1;
        }
        for(int i = 1; i < n; ++i) {
            vector<vector<double>> nxt(m + 1, vector<double>(4));
            for(int j = 0; j <= m; ++j) {
                const int t = v[0] * j;
                const int cnt = (t + v[i] - 1) / v[i];
                const double win = p[min(m, cnt - 1)];
                for(int k = 0; k < 3; ++k) {
                    nxt[j][k] += (cnt == 0 ? 0 : dp[j][k] * win); // win
                    if(k + 1 < 3) {
                        nxt[j][k + 1] += (cnt == 0 ? dp[j][k] : dp[j][k] * (1 - win)); // lose
                    }
                }
                nxt[j][3] += dp[j][3] * (1 - win);
            }
            dp = move(nxt);
        }
        return dp;
    };
    auto dp1 = calc(vi);
    auto dp2 = calc(da);
    auto dp3 = calc(vo);

    double ans = -1e9;
    for(int i = 0; i <= m; ++i) {
        for(int j = 0; j + i <= m; ++j) {
            int k = m - i - j;
            double t = (dp1[i][0] + dp1[i][1] + dp1[i][2]) * 5;
            t += (dp2[j][0] + dp2[j][1] + dp2[j][2]) * 3;
            t += (dp3[k][0] + dp3[k][1] + dp3[k][2]) * 2;
            t -= (dp1[i][3] + dp2[j][3] + dp3[k][3]);
            ans = max(ans, t);
        }
    }

    cout << fixed << setprecision(10) << ans << endl;
}
