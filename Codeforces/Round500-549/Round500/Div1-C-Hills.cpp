
// http://codeforces.com/contest/1012/problem/C

// サイズがでかいので vector でやると TLE
// 今度から気をつけましょう．

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int dp[5001][2501][2];

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= (n + 1) / 2; ++j) {
            dp[i][j][0] = dp[i][j][1] = inf;
        }
    }
    dp[0][0][0] = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= (i + 1) / 2; ++j) {
            dp[i][j][0] = min(dp[i - 1][j][1], dp[i - 1][j][0]);

            if(j == 0) continue;
            int cost1 = 0;
            if(i != 1) cost1 += max(a[i - 2] - a[i - 1] + 1, 0) + dp[i - 2][j - 1][0];
            if(i != n) cost1 += max(a[i] - a[i - 1] + 1, 0);
            dp[i][j][1] = min(dp[i][j][1], cost1);

            if(i >= 3) {
                int cost2 = dp[i - 2][j - 1][1];
                if(i != n) cost2 += max(a[i] - a[i - 1] + 1, 0);
                int already = max(0, a[i - 2] - a[i - 3] + 1);
                cost2 += max(0, a[i - 2] - a[i - 1] + 1 - already);
                dp[i][j][1] = min(dp[i][j][1], cost2);
            }
        }
    }

    for(int i = 1; i <= (n + 1) / 2; ++i) {
        printf("%d\n", min(dp[n][i][0], dp[n][i][1]));
    }
}
