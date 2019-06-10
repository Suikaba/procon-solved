#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t, s; cin >> n >> t >> s;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }

    vector<vector<int>> dp1(n + 1, vector<int>(s + 1)), dp2(n + 1, vector<int>(t - s + 1));
    for(int i = 0; i < n; ++i) {
        dp1[i + 1] = dp1[i];
        for(int j = s - b[i]; j >= 0; --j) {
            dp1[i + 1][j + b[i]] = max(dp1[i + 1][j + b[i]], dp1[i][j] + a[i]);
        }
    }
    for(int i = n; i >= 1; --i) {
        dp2[i - 1] = dp2[i];
        for(int j = t - s - b[i]; j >= 0; --j) {
            dp2[i - 1][j + b[i]] = max(dp2[i - 1][j + b[i]], dp2[i][j] + a[i]);
        }
    }

    int ans = 0;
    for(int i = 0; i <= n; ++i) {
        ans = max(ans, dp1[i][s] + dp2[i][t - s]);
    }

    cout << ans << endl;
}
