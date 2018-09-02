
// http://codeforces.com/contest/557/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, w; cin >> n >> w;
    vector<int> a(n * 2);
    for(int i = 0; i < n * 2; ++i) {
        cin >> a[i];
    }
    sort(begin(a), end(a));

    auto check = [&] (double w) {
        const double g = w / 3 / n;
        const double m = w * 2 / 3 / n;
        bool res = true;
        for(int i = 0; i < n; ++i) {
            res &= a[i] >= g;
        }
        for(int i = n; i < 2 * n; ++i) {
            res &= a[i] >= m;
        }
        return res;
    };

    double lb = 0, ub = w;
    for(int lp = 0; lp < 100; ++lp) {
        const auto mid = (lb + ub) / 2;
        (check(mid) ? lb : ub) = mid;
    }

    cout << setprecision(10) << fixed << lb << endl;
}
