#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);

int main() {
    cout << fixed << setprecision(10);

    int n; double r; cin >> n >> r;

    auto too_large = [&] (double R) {
        double rad = asin(R / (r + R));
        return pi - n * rad <= 0;
    };
    double lb = 0, ub = 1e9;
    for(int lp = 0; lp < 60; ++lp) {
        const auto mid = (lb + ub) / 2;
        (too_large(mid) ? ub : lb) = mid;
    }

    cout << ub << endl;
}
