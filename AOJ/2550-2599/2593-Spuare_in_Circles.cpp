// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2593

#include <bits/stdc++.h>
using namespace std;

using pdd = pair<double, double>;

double solve(vector<double> x, vector<double> r) {
    const int n = x.size();
    auto check = [&] (double h) {
        vector<pdd> ps(n);
        for(int i = 0; i < n; ++i) {
            double x1 = x[i], x2 = x[i];
            if(h <= r[i]) {
                x1 -= sqrt(r[i] * r[i] - h * h);
                x2 += sqrt(r[i] * r[i] - h * h);
            }
            ps[i] = make_pair(x1, x2);
        }
        sort(begin(ps), end(ps));
        double lx = -1e9, rx = -2e9;
        for(int i = 0; i < n; ++i) {
            if(rx < ps[i].first) {
                if(rx - lx >= 2 * h) return true;
                lx = ps[i].first, rx = ps[i].second;
            } else {
                rx = max(rx, ps[i].second);
            }
        }
        return rx - lx >= 2 * h;
    };
    double lb = 0, ub = 2e5;
    for(int lp = 0; lp < 60; ++lp) {
        const auto mid = (lb + ub) / 2;
        (check(mid) ? lb : ub) = mid;
    }
    return lb * 2;
}

int main() {
    int n;
    while(cin >> n, n) {
        vector<double> x(n), r(n);
        for(int i = 0; i < n; ++i) {
            cin >> x[i] >> r[i];
        }
        cout << fixed << setprecision(10) << solve(move(x), move(r)) << endl;
    }
}
