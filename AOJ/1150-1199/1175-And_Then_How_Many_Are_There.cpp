#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1175&lang=jp

// 反省点
// 実装方針で迷走しすぎ．大反省．
// on[i] を作れば普通に bitDP できるのに，dfs しながら使わないときの使用不可マスクを作る
// みたいな実装していて最悪．頭悪すぎ．

int main() {
    int n;
    while(cin >> n, n) {
        vector<int> x(n), y(n), r(n), c(n);
        for(int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i] >> r[i] >> c[i];
        }
        auto isis_cc = [&] (int i, int j) {
            return (r[i] + r[j]) * (r[i] + r[j]) > (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
        };
        vector<int> on(n);
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                if(isis_cc(i, j)) on[j] |= (1 << i);
            }
        }
        int ans = 0;
        vector<bool> dp(1 << n);
        dp[0] = true;
        for(int S = 0; S < 1 << n; ++S) {
            if(!dp[S]) continue;
            for(int i = 0; i < n; ++i) {
                if(S & (1 << i)) continue;
                for(int j = i + 1; j < n; ++j) {
                    if(S & (1 << j)) continue;
                    if((S & on[i]) == on[i] && (S & on[j]) == on[j] && c[i] == c[j]) {
                        dp[S | (1 << i) | (1 << j)] = true;
                        ans = max(ans, __builtin_popcount(S) + 2);
                    }
                }
            }
        }
        cout << ans << endl;
    }
}
