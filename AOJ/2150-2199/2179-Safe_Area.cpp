#include <bits/stdc++.h>
using namespace std;

using ld = double;
using point = std::complex<ld>;
using polygon = std::vector<point>;

constexpr ld eps = 1e-7;
const ld pi = std::acos(-1.0);

ld dot(point const& a, point const& b) {
    return std::real(std::conj(a) * b);
}
ld cross(point const& a, point const& b) {
    return std::imag(std::conj(a) * b);
}

struct line {
    line() : a(0, 0), b(0, 0) {}
    line(point a_, point b_) : a(a_), b(b_) {}
    point a, b;
};

bool isis_ll(line l, line m) {
    return cross(l.b - l.a, m.b - m.a) != 0;
}

point is_ll(line s, line t) {
    point sv = s.b - s.a, tv = t.b - t.a;
    assert(cross(sv, tv) != 0);
    return s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv);
}

point proj(line l, point p) {
    ld t = dot(p - l.a, l.a - l.b) / std::norm(l.a - l.b);
    return l.a + t * (l.a - l.b);
}

long double dist_lp(line l, point p) {
    return std::abs(p - proj(l, p));
}

int main() {
    int w, h, n, r;
    while(cin >> w >> h >> n >> r, w) {
        vector<vector<line>> ls(n);
        vector<line> ls2;
        ls2.emplace_back(point{0, -(ld)h}, point{0, (ld)h * 2});
        ls2.emplace_back(point{-(ld)w, 0}, point{(ld)w * 2, 0});
        ls2.emplace_back(point{(ld)w, -(ld)h}, point{(ld)w, (ld)h * 2});
        ls2.emplace_back(point{-(ld)w, (ld)h}, point{(ld)w * 2, (ld)h});
        for(int i = 0; i < n; ++i) {
            ld x1, y1, x2, y2, t; cin >> x1 >> y1 >> x2 >> y2 >> t;
            point a{x1, y1}, b{x2, y2};
            const auto vec = (a - b) / abs(a - b) * t * point(0, 1);
            ls[i].emplace_back(a - vec, b - vec);
            ls[i].emplace_back(a + vec, b + vec);
            ls2.emplace_back(a - vec, b - vec);
            ls2.emplace_back(a + vec, b + vec);
        }

        auto create_circles = [&] (int i, int j) {
            const auto ip = is_ll(ls2[i], ls2[j]);
            auto ps1 = {ls2[i].a, ls2[i].b}, ps2 = {ls2[j].a, ls2[j].b};
            vector<point> res;
            for(auto const& p1 : ps1) {
                for(auto const& p2 : ps2) {
                    const auto v1 = (p1 - ip) / abs(p1 - ip);
                    const auto v2 = (p2 - ip) / abs(p2 - ip);
                    auto p = (v1 + v2) * 0.5;
                    const ld rr = abs(p) * sin(abs(arg(p / v1)));
                    res.push_back(ip + p * (ld)r / rr);
                }
            }
            return res;
        };
        const int m = ls2.size();
        bool ans = false;
        for(int i = 0; i < m && !ans; ++i) {
            for(int j = i + 1; j < m && !ans; ++j) {
                if(!isis_ll(ls2[i], ls2[j])) continue;
                for(auto&& p : create_circles(i, j)) {
                    bool check = -eps <= real(p) - r && real(p) + r <= w + eps && -eps <= imag(p) - r && imag(p) + r <= h + eps;
                    for(int k = 0; k < 4 && check; ++k) {
                        check &= dist_lp(ls2[k], p) >= r - eps;
                    }
                    for(int k = 0; k < n && check; ++k) {
                        check &= dist_lp(ls[k][0], p) >= r - eps && dist_lp(ls[k][1], p) >= r - eps;
                        const ld c1 = cross(p - ls[k][0].a, p - ls[k][0].b);
                        const ld c2 = cross(p - ls[k][1].a, p - ls[k][1].b);
                        check &= c1 * c2 >= 0;
                    }
                    ans |= check;
                }
            }
        }

        cout << (ans ? "Yes" : "No") << endl;
    }
}
