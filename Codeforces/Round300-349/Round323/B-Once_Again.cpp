// http://codeforces.com/contest/582/problem/B

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, t; cin >> n >> t;
    vector<int> a(n), cnt(301);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        cnt[a[i]] += 1;
    }
    if(t <= 1002) {
        auto cp = a;
        for(int i = 0; i < t - 1; ++i) {
            for(int j = 0; j < n; ++j) {
                a.push_back(cp[j]);
            }
        }
        n = a.size();
        vector<int> dp(n + 1, inf);
        for(int i = 0; i < n; ++i) {
            *upper_bound(begin(dp), end(dp), a[i]) = a[i];
        }
        cout << (find(begin(dp), end(dp), inf) - begin(dp)) << endl;
        return 0;
    }

    {
        auto cp = a;
        for(int i = 0; i < n - 1; ++i) {
            for(int j = 0; j < n; ++j) {
                a.push_back(cp[j]);
            }
        }
    }
    const int m = a.size();
    const int mid = t - m / n * 2;

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        vector<int> dp1(m, inf), dp2(m, inf);
        for(int j = 0; j < m; ++j) {
            if(a[j] <= a[i]) {
                *upper_bound(begin(dp1), end(dp1), a[j]) = a[j];
            }
        }
        for(int j = 0; j < m; ++j) {
            if(a[i] <= a[j]) {
                *upper_bound(begin(dp2), end(dp2), a[j]) = a[j];
            }
        }
        const int len1 = find(begin(dp1), end(dp1), inf) - begin(dp1);
        const int len2 = find(begin(dp2), end(dp2), inf) - begin(dp2);
        ans = max(ans, len1 + len2 + cnt[a[i]] * mid);
    }

    cout << ans << endl;
}
