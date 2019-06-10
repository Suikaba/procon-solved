#include <bits/stdc++.h>
using namespace std;

const double g = (sqrt(5) + 1) / 2.0;
const double pi = acos(-1.0);

template <typename F>
double search(F f, double lb, double ub, int cnt) {
    double x1 = (ub - lb) / (g + 1) + lb;
    double x2 = (ub - lb) * g / (g + 1) + lb;
    double v1 = f(x1), v2 = f(x2);
    for(int i = 0; i < cnt; ++i) {
        if(v1 < v2) {
            ub = x2;
            x2 = x1;
            v2 = v1;
            x1 = (ub - lb) / (g + 1) + lb;
            v1 = f(x1);
        } else {
            lb = x1;
            x1 = x2;
            v1 = v2;
            x2 = (ub - lb) * g / (g + 1) + lb;
            v2 = f(x2);
        }
    }
    return (lb + ub) / 2;
}

int main() {
    ifstream ifs("dome.in");
    int n; ifs >> n;
    vector<double> x(n), y(n), z(n);
    for(int i = 0; i < n; ++i) {
        ifs >> x[i] >> y[i] >> z[i];
    }

    auto calc_volume = [&] (double r) {
        double h = 0;
        for(int i = 0; i < n; ++i) {
            h = max(h, r * z[i] / (r - hypot(x[i], y[i])));
        }
        return r * r * pi * h / 3;
    };
    double lb = 0, ub = 1e9;
    for(int i = 0; i < n; ++i) {
        lb = max(lb, hypot(x[i], y[i]));
    }
    lb += 1e-10;
    const auto r = search(calc_volume, lb, ub, 100);
    const auto vol = calc_volume(r);
    const auto h = vol * 3 / (r * r * pi);
    ofstream ofs("dome.out");
    ofs << fixed << setprecision(3);
    ofs << h << " " << r << endl;
}
