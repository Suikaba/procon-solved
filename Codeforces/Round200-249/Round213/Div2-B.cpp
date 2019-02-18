#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> dp(n + 1, 2);
    dp[0] = 0, dp[1] = 1;
    for(int i = 0; i < n; ++i) {
        dp[i + 1] = max(dp[i + 1], (dp[i] < 2 || a[i] == a[i - 1] + a[i - 2] ? dp[i] + 1 : 0));
    }

    cout << *max_element(begin(dp), end(dp)) << endl;
}
