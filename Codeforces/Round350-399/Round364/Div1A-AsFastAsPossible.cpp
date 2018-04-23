#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/700/problem/A

constexpr double eps = 1e-10;

int main() {
    int n, k;
    double l, v1, v2;
    cin >> n >> l >> v1 >> v2 >> k;
    double lb = 0, ub = 1e18;
    for(int loop = 0; loop < 100; ++loop) {
        const auto mid = (lb + ub) / 2;
        int m = n;
        double t = 0, pos = 0;
        while(m > 0 && t <= mid) {
            double pass = max((l - pos - v1 * (mid - t)) / (v2 - v1), 0.0);
            if(pass == 0) {
                m = 0;
                break;
            }
            t += pass;
            if(t > mid + eps) break;
            double more_t = (v2 - v1) * pass / (v1 + v2);
            pos += v1 * pass;
            pos += more_t * v1;
            t += more_t;
            m -= k;
        }

        if(m <= 0) {
            ub = mid;
        } else {
            lb = mid;
        }
    }

    cout << fixed << setprecision(10) << lb << endl;
}
