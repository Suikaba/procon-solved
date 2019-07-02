#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using point = std::complex<ld>;
using polygon = std::vector<point>;

constexpr ld eps = 1e-10;

ld dot(point const& a, point const& b) {
    return std::real(std::conj(a) * b);
}
ld cross(point const& a, point const& b) {
    return std::imag(std::conj(a) * b);
}

int ccw(point a, point b, point c) {
    b -= a; c -= a;
    if(cross(b, c) > eps) return 1;            // a -> b -> c : counterclockwise
    if(cross(b, c) < -eps) return -1;          // a -> b -> c : clockwise
    if(dot(b, c) < 0) return 2;                // c -> a -> b : line
    if(std::norm(b) < std::norm(c)) return -2; // a -> b -> c : line
    return 0;                                  // a -> c -> b : line
}

struct line {
    line() : a(0, 0), b(0, 0) {}
    line(point a, point b) : a(a), b(b) {}
    point a, b;
};

point is_ll(line s, line t) {
    point sv = s.b - s.a, tv = t.b - t.a;
    assert(cross(sv, tv) != 0);
    return s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv);
}

// left side
polygon convex_cut(polygon const& p, line l) {
    const int N = p.size();
    polygon res;
    for(int i = 0; i < N; ++i) {
        auto a = p[i], b = p[(i + 1) % N];
        if(ccw(l.a, l.b, a) != -1) {
            res.push_back(a);
        }
        if(ccw(l.a, l.b, a) * ccw(l.a, l.b, b) < 0) {
            if(cross(a - b, l.a - l.b) == 0) continue; // cut line が辺に覆いかぶさる
            res.push_back(is_ll(line(a, b), l));
        }
    }
    return res;
}

ld area(polygon const& p) {
    const int N = p.size();
    ld res = 0;
    for(int i = 0; i < N; ++i) {
        res += cross(p[i], p[(i + 1) % N]);
    }
    return res / 2;
}

line separate_line(point const& p1, point const& p2) {
    const auto mid = (p1 + p2) * 0.5L;
    return line{mid, mid + (mid - p1) * point(0, 1)};
}

int main() {
    int m, n; cin >> m >> n;
    polygon ps(m), shelter(n);
    for(int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        ps[i] = point(x, y);
    }
    for(int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        shelter[i] = point(x, y);
    }

    ld ans = 0;
    for(int i = 0; i < n; ++i) {
        auto range = ps;
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;
            auto l = separate_line(shelter[i], shelter[j]);
            if(cross(shelter[i] - l.a, l.b - l.a) > 0) {
                swap(l.a, l.b);
            }
            range = convex_cut(range, move(l));
        }
        const int sz = range.size();
        const auto a = real(shelter[i]), b = imag(shelter[i]);
        for(int j = 0; j < sz; ++j) {
            const ld x1 = real(range[j]), y1 = imag(range[j]);
            const ld x2 = real(range[(j + 1) % sz]), y2 = imag(range[(j + 1) % sz]);
            const ld t1 = (x2 - x1) * (pow(y2 - y1, 3) / 4 + pow(y2 - y1, 2) * (y1 - b) + 1.5 * (y2 - y1) * pow(y1 - b, 2) + pow(y1 - b, 3));
            const ld t2 = (y2 - y1) * (pow(x2 - x1, 3) / 4 + pow(x2 - x1, 2) * (x1 - a) + 1.5 * (x2 - x1) * pow(x1 - a, 2) + pow(x1 - a, 3));
            ans += t2 - t1;
        }
    }
    ans /= 3 * area(ps);

    cout << fixed << setprecision(10) << ans << endl;
}
