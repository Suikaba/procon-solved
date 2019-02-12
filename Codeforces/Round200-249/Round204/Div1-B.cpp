#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    int inv_cnt = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            inv_cnt += p[i] > p[j];
        }
    }

    vector<double> dp(inv_cnt + 1, -1);
    dp[0] = 0;
    if(inv_cnt != 0) dp[1] = 1;
    function<double(int)> rec = [&] (int x) {
        if(dp[x] >= 0) return dp[x];
        return dp[x] = rec(x - 2) + 4;
    };
    cout << fixed << setprecision(10) << rec(inv_cnt) << endl;
}