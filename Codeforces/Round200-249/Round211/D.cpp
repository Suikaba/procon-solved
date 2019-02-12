#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n, m, a; cin >> n >> m >> a;
    vector<ll> b(n), p(m);
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    for(int i = 0; i < m; ++i) {
        cin >> p[i];
    }
    sort(begin(b), end(b));
    sort(begin(p), end(p));

    auto check = [&] (int x) {
        ll sum = 0;
        for(int i = 0; i < x; ++i) {
            sum += max(0LL, p[i] - b[n - x + i]);
        }
        return sum <= a;
    };
    int lb = 0, ub = min(n, m) + 1;
    while(ub - lb > 1) {
        const int mid = (ub + lb) >> 1;
        (check(mid) ? lb : ub) = mid;
    }
    const ll r = max(0LL, accumulate(begin(p), begin(p) + lb, 0LL) - a);

    cout << lb << ' ' << r << endl;
}
