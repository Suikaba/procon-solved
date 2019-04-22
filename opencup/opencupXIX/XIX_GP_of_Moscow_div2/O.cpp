#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n; cin >> n;
    vector<int> d(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sort(begin(d), end(d));

    const int max_v = 100000;
    vector<int> dp(max_v + 1, inf);
    dp[0] = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j + d[i] <= max_v; ++j) {
            dp[j + d[i]] = min(dp[j + d[i]], dp[j] + 1);
        }
    }
    int ans = 0;
    for(int i = 1; i <= max_v; ++i) {
        int cnt = 0, tmp = i;
        for(int j = n - 1; j >= 0; --j) {
            cnt += tmp / d[j];
            tmp %= d[j];
        }
        if(dp[i] != inf && cnt != dp[i]) {
            ans = i;
            break;
        }
    }

    cout << ans << endl;
}