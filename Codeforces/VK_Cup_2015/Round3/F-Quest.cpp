
// http://codeforces.com/contest/542/problem/F

// 反省点
// 普通に詰めきれなかった．DPパート自体はできてたけど，
// 各高さではその高さギリギリのやつだけしか見る必要がないことに気が付かなかった．

#include <bits/stdc++.h>
using namespace std;

// O(n^2 T)
//int main() {
//    int n, T;
//    cin >> n >> T;
//    vector<int> t(n), q(n);
//    vector<vector<int>> vs(T);
//    for(int i = 0; i < n; ++i) {
//        cin >> t[i] >> q[i];
//        vs[T - t[i]].push_back(q[i]);
//    }
//
//    vector<vector<int>> dp(T, vector<int>(n + 1));
//    if(!vs[0].empty()) {
//        dp[0][1] = *max_element(begin(vs[0]), end(vs[0]));
//    }
//    for(int i = T - 1; i >= 1; --i) {
//        sort(rbegin(vs[i]), rend(vs[i]));
//        const int m = vs[i].size();
//        vector<int> sum(m + 1);
//        for(int j = 0; j < m; ++j) {
//            sum[j + 1] = sum[j] + vs[i][j];
//        }
//        for(int j = 0; j <= n; ++j) {
//            for(int k = 0; k <= m; ++k) {
//                if((j + k + 1) / 2 > n) continue;
//                dp[i - 1][(j + k + 1) / 2] = max(dp[i - 1][(j + k + 1) / 2], dp[i][j] + sum[k]);
//            }
//        }
//    }
//
//    cout << dp[0][1] << endl;
//}

// O(nlogn + T)
int main() {
    int n, T;
    cin >> n >> T;
    vector<vector<int>> ts(T);
    for(int i = 0; i < n; ++i) {
        int t, q;
        cin >> t >> q;
        ts[T - t].push_back(q);
    }

    for(int i = T - 1; i >= 1; --i) {
        if(ts[i].size() % 2 == 1) {
            ts[i].push_back(0);
        }
        sort(begin(ts[i]), end(ts[i]));
        const int m = ts[i].size();
        for(int j = 0; j < m / 2; ++j) {
            ts[i - 1].push_back(ts[i][2 * j] + ts[i][2 * j + 1]);
        }
    }

    cout << *max_element(begin(ts[0]), end(ts[0])) << endl;
}
