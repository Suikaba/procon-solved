#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using point = std::complex<ld>;
using polygon = std::vector<point>;

constexpr ld eps = 1e-10;
const ld pi = std::acos(-1.0);

struct circle {
    circle() : p(point(0, 0)), r(0) {}
    circle(point p_, long double r_) : p(p_), r(r_) {}
    point p;
    long double r;
};

std::vector<point> is_cc(circle const& c1, circle const& c2) {
    std::vector<point> res;
    ld d = std::abs(c1.p - c2.p);
    ld rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
    ld dfr = c1.r * c1.r - rc * rc;
    if(std::abs(dfr) < eps) {
        dfr = 0.0;
    } else if(dfr < 0.0) {
        return res;
    }

    ld rs = std::sqrt(dfr);
    point diff = (c2.p - c1.p) / d;
    res.push_back(c1.p + diff * point(rc, rs));
    if(dfr != 0.0) {
        res.push_back(c1.p + diff * point(rc, -rs));
    }
    return res;
}


int main() {
    int n;
    while(cin >> n, n) {
        vector<circle> cs;
        for(int i = 0; i < n; ++i) {
            double x, y;
            scanf("%lf,%lf", &x, &y);
            cs.emplace_back(point(x, y), 1);
        }

        int ans = 1;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                for(auto&& p : is_cc(cs[i], cs[j])) {
                    int cnt = 0;
                    for(auto const& c : cs) {
                        cnt += abs(p - c.p) <= 1;
                    }
                    ans = max(cnt, ans);
                }
            }
        }
        cout << ans << endl;
    }
}
