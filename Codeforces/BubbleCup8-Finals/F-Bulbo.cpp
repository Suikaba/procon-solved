// http://codeforces.com/contest/575/problem/F

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e18;

int main() {
    int n, x; cin >> n >> x;
    vector<int> xs = {x}, l(n), r(n);
    for(int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        xs.push_back(l[i]);
        xs.push_back(r[i]);
    }
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    const int m = xs.size();
    x = lower_bound(begin(xs), end(xs), x) - begin(xs);
    for(int i = 0; i < n; ++i) {
        l[i] = lower_bound(begin(xs), end(xs), l[i]) - begin(xs);
        r[i] = lower_bound(begin(xs), end(xs), r[i]) - begin(xs);
    }

    vector<ll> dp(m, inf);
    dp[x] = 0;
    for(int i = 0; i < n; ++i) {
        vector<ll> nxt(m, inf);
        vector<ll> left(m, inf), right(m, inf);
        for(int j = 0; j < m; ++j) {
            left[j] = min(j != 0 ? left[j - 1] + (xs[j] - xs[j - 1]) : inf, dp[j]);
        }
        for(int j = m - 1; j >= 0; --j) {
            right[j] = min(j != m - 1 ? right[j + 1] + (xs[j + 1] - xs[j]) : inf, dp[j]);
        }
        for(int j = 0; j < m; ++j) {
            ll cost = min(abs(xs[j] - xs[l[i]]), abs(xs[j] - xs[r[i]]));
            if(l[i] <= j && j <= r[i]) cost = 0;
            nxt[j] = min(left[j], right[j]) + cost;
        }
        dp = move(nxt);
    }

    cout << *min_element(begin(dp), end(dp)) << endl;
}
