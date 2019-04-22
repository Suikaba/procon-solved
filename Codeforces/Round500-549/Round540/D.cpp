#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 2e9;

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(rbegin(a), rend(a));

    auto check = [&] (int days) {
        int tm = m;
        for(int i = 0; i < n && tm > 0; ++i) {
            tm -= max(0, a[i] - (i / days));
        }
        return tm <= 0;
    };
    int lb = 0, ub = inf;
    while(ub - lb > 1) {
        const auto mid = (ub + lb) >> 1;
        (check(mid) ? ub : lb) = mid;
    }
    if(ub == inf) {
        cout << -1 << endl;
    } else {
        cout << ub << endl;
    }
}
