#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2635

// 反省点
// 実装するとこ（ライブラリ除く）ほぼ無いし特になし．

using ld = long double;
using point = std::complex<ld>;
using polygon = std::vector<point>;

constexpr ld eps = 1e-10;
constexpr ld pi = std::acos(-1.0);

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

polygon convex_hull(std::vector<point> ps) {
    std::sort(std::begin(ps), std::end(ps),
              [](point const& p1, point const& p2) {
                  return std::real(p1) < std::real(p2)
                         || (std::real(p1) <= std::real(p2) && std::imag(p1) < std::imag(p2));
              });
    const int n = ps.size();
    int k = 0;
    polygon qs(2 * n);
    for(int i = 0; i < n; ++i) {
        while(k > 1 && ccw(qs[k - 2], qs[k - 1], ps[i]) <= 0) k--;
        qs[k++] = ps[i];
    }
    for(int i = n - 2, t = k; i >= 0; --i) {
        while(k > t && ccw(qs[k - 2], qs[k - 1], ps[i]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}

ld area(polygon const& poly) {
    const int n = poly.size();
    ld res = 0;
    for(int i = 0; i < n; ++i) {
        res += cross(poly[i], poly[(i + 1) % n]);
    }
    return res / 2;
}

int main() {
    int n;
    cin >> n;
    vector<point> ps(n);
    for(int i = 0; i < n; ++i) {
        ld x, y;
        cin >> x >> y;
        ps[i] = point(x, y);
    }
    auto check = [&](vector<point> const& ps) {
        polygon poly = {ps[0], ps[1]};
        bool res = false;
        for(int i = 2; i < n; ++i) {
            const ld s1 = area(convex_hull(poly));
            poly.push_back(ps[i]);
            const ld s2 = area(convex_hull(poly));
            res |= fabs(s1 - s2) < eps;
        }
        return res;
    };
    bool ng = check(ps);
    reverse(begin(ps), end(ps));
    ng |= check(ps);

    cout << (!ng ? "Possible" : "Impossible") << endl;
}
