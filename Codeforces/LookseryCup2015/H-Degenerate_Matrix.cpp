#include <bits/stdc++.h>
using namespace std;

constexpr double inf = 1e36;

int main() {
    vector<double> A(4);
    for(int i = 0; i < 4; ++i) {
        cin >> A[i];
    }
    auto get_range = [] (vector<double> v1, vector<double> v2) {
        double mini = inf, maxi = -inf;
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                const auto val = v1[i] * v2[j];
                mini = min(mini, val);
                maxi = max(maxi, val);
            }
        }
        return make_pair(mini, maxi);
    };
    auto check = [&] (double X) {
        vector<double> l(4), r(4);
        for(int i = 0; i < 4; ++i) {
            l[i] = A[i] - X, r[i] = A[i] + X;
        }
        const auto r1 = get_range({l[0], r[0]}, {l[3], r[3]});
        const auto r2 = get_range({l[1], r[1]}, {l[2], r[2]});
        return (r2.first <= r1.first && r1.first <= r2.second)
               || (r2.first <= r1.second && r1.second <= r2.second)
               || (r1.first <= r2.first && r2.first <= r1.second)
               || (r1.first <= r2.second && r2.second <= r1.second);
    };
    double lb = 0, ub = 1e18;
    for(int lp = 0; lp < 100; ++lp) {
        const auto mid = (lb + ub) / 2;
        (check(mid) ? ub : lb) = mid;
    }
    cout << fixed << setprecision(10) << lb << endl;
}
