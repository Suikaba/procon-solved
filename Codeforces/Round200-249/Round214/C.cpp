#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    vector<int> dp(1 << 18, -inf);
    dp[1 << 17] = 0;
    for(int i = 0; i < n; ++i) {
        auto nxt = dp;
        for(int j = 0; j < (1 << 18); ++j) {
            if(0 <= j + a[i] - k * b[i] && j + a[i] - k * b[i] < (1 << 18)) {
                nxt[j + a[i] - k * b[i]] = max(nxt[j + a[i] - k * b[i]], dp[j] + a[i]);
            }
        }
        dp = move(nxt);
    }

    if(dp[1 << 17] == 0) {
        cout << -1 << endl;
    } else {
        cout << dp[1 << 17] << endl;
    }
}
