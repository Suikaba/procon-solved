#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e10;

int main() {
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    auto check = [&] (ll x) {
        vector<int> dp(n);
        for(int i = 0; i < n; ++i) {
            dp[i] = i;
        }
        for(int i = 0; i < n; ++i) {
            ll lb = a[i] - x, ub = a[i] + x;
            for(int j = i + 1; j < n; ++j) {
                if(lb <= a[j] && a[j] <= ub) {
                    dp[j] = min(dp[j], dp[i] + (j - i - 1));
                }
                lb = max(-inf, lb - x);
                ub = min(inf, ub + x);
            }
        }

        for(int i = 0; i < n; ++i) {
            if(dp[i] + n - i - 1 <= k) return true;
        }
        return false;
    };

    ll lb = -1, ub = inf;
    while(ub - lb > 1) {
        const auto mid = (ub + lb) >> 1;
        (check(mid) ? ub : lb) = mid;
    }

    cout << ub << endl;
}
