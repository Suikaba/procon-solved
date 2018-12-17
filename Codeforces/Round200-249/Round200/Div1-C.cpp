#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, m; cin >> n >> m;
    deque<ll> h(n), p(m);
    for(int i = 0; i < n; ++i) cin >> h[i];
    for(int i = 0; i < m; ++i) cin >> p[i];

    auto check = [&] (ll t) {
        auto tp = p;
        for(int i = 0; i < n && !tp.empty(); ++i) {
            if(!tp.empty() && h[i] - tp[0] > t) return false;
            const ll left = max(h[i] - tp[0], 0LL);
            const ll rest = max(t - left * 2, (t - left) / 2);
            const int nxt = upper_bound(begin(tp), end(tp), h[i] + rest) - begin(tp);
            for(int j = 0; j < nxt; ++j) {
                tp.pop_front();
            }
        }
        return tp.empty();
    };
    ll lb = -1, ub = 1e18;
    while(ub - lb > 1) {
        const auto mid = (lb + ub) >> 1;
        (check(mid) ? ub : lb) = mid;
    }

    cout << ub << endl;
}
