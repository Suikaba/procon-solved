#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        vector<vector<int>> a(2, vector<int>(n));
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < n; ++j) {
                cin >> a[i][j];
            }
        }
        vector<int> dp(3);
        for(int i = 0; i < n; ++i) {
            vector<int> nxt(3);
            nxt[0] = max({dp[0], dp[1], dp[2]});
            nxt[1] = max({dp[0] + a[0][i], dp[2] + a[0][i]});
            nxt[2] = max({dp[0] + a[1][i], dp[1] + a[1][i]});
            dp = move(nxt);
        }
        cout << max({dp[0], dp[1], dp[2]}) << endl;
    }
}
