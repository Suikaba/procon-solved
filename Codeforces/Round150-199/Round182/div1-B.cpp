#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, d; cin >> n >> d;
    vector<int> a(n);
    for(int i = 1; i < n - 1; ++i) {
        cin >> a[i];
    }
    vector<int> x(n), y(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    auto calc_cost = [&] (int i, int j) {
        return d * (abs(x[i] - x[j]) + abs(y[i] - y[j]));
    };
    auto check = [&] (int val) {
        vector<int> dp(n, -inf);
        dp[0] = val;
        for(int lp = 0; lp < n + 1; ++lp) {
            for(int i = 0; i < n; ++i) { // i -> j
                for(int j = 0; j < n; ++j) {
                    if(i == j || dp[i] < 0) continue;
                    dp[j] = max(dp[j], dp[i] - calc_cost(i, j) + a[j]);
                    //cout << i << " " << j << " " << dp[j] << endl;
                }
            }
        }
        return dp.back() >= 0;
    };
    int lb = -1, ub = inf;
    while(ub - lb > 1) {
        const int mid = (ub + lb) >> 1;
        (check(mid) ? ub : lb) = mid;
    }
    cout << ub << endl;
}