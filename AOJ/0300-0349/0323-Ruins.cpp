// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0323

#include <bits/stdc++.h>
using namespace std;

using ld = long double;

int main() {
    int n; cin >> n;
    vector<ld> x(n), r(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> r[i];
    }

    auto check = [&] (ld y) {
        ld mini = -1e18, maxi = 1e18;
        for(int i = 0; i < n; ++i) {
            const auto d = sqrt(r[i] * r[i] - y * y);
            mini = max(mini, x[i] - d);
            maxi = min(maxi, x[i] + d);
        }
        return mini <= maxi;
    };
    ld lb = 0, ub = *min_element(begin(r), end(r));
    for(int lp = 0; lp <= 100; ++lp) {
        const auto mid = (lb + ub) / 2;
        (check(mid) ? lb : ub) = mid;
    }
    cout << setprecision(10) << fixed << lb << endl;
}
