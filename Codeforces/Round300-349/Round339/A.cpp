#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using point = std::complex<ld>;
using polygon = std::vector<point>;

constexpr ld eps = 1e-10;
const ld pi = std::acos(-1.0);
const ld inf = 1e18;

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

struct segment {
    segment() : a(0, 0), b(0, 0) {}
    segment(point a, point b) : a(a), b(b) {}
    point a, b;
};

struct line {
    line() : a(0, 0), b(0, 0) {}
    line(point a, point b) : a(a), b(b) {}
    line(segment s) : a(s.a), b(s.b) {}
    point a, b;
};

point proj(line l, point p) {
    long double t = dot(p - l.a, l.a - l.b) / std::norm(l.a - l.b);
    return l.a + t * (l.a - l.b);
}

bool isis_sp(segment s, point p) {
    return (std::abs(s.a - p) + std::abs(s.b - p) - std::abs(s.b - s.a) < eps);
}

long double dist_sp(segment s, point p) {
    point r = proj(line(s), p);
    return isis_sp(s, r) ? std::abs(r - p) : std::min(std::abs(s.a - p), std::abs(s.b - p));
}

int main() {
    double cx, cy;
    int n; cin >> n >> cx >> cy;
    auto c = point(cx, cy);
    polygon ps;
    ld d1 = inf, d2 = 0;
    for(int i = 0; i < n; ++i) {
        ld x, y; cin >> x >> y;
        ps.emplace_back(x, y);
        d2 = max(d2, hypot(x - cx, y - cy));
    }
    for(int i = 0; i < n; ++i) {
        const int j = (i + 1) % n;
        d1 = min(d1, dist_sp({ps[i], ps[j]}, c));
    }

    cout << fixed << setprecision(10);
    cout << (d2 * d2 - d1 * d1) * pi << endl;
}