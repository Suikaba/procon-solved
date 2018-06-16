#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/605/problem/C

// 反省点
// 嘘解法を生やしました．
// 二分探索ごとに convex hull しててTLE．オーダーは変わらないけど定数倍が違いすぎる．
// 外に出せる重い処理は外に出そう．

using ld = long double;
using point = complex<ld>;
using polygon = vector<point>;

constexpr ld eps = 1e-12;
constexpr ld pi = acos(-1.0);
constexpr ld inf = 1e18;

struct segment {
    segment(point a, point b) : a(a), b(b) {}
    point a, b;
};

long double dot(point a, point b) {
    return std::real(std::conj(a) * b);
}

long double cross(point a, point b) {
    return std::imag(std::conj(a) * b);
}

int ccw(point a, point b, point c) {
    b -= a; c -= a;
    if(cross(b, c) > eps)           return 1;  // a -> b -> c : counterclockwise
    if(cross(b, c) < -eps)          return -1; // a -> b -> c : clockwise
    if(dot(b, c) < 0)               return 2;  // c -> a -> b : line
    if(std::norm(b) < std::norm(c)) return -2; // a -> b -> c : line
    return 0;                                  // a -> c -> b : line
}

bool isis_sp(segment s, point p) {
    return (std::abs(s.a - p) + std::abs(s.b - p) - std::abs(s.b - s.a) < eps);
}

polygon convex_hull(std::vector<point> ps) {
    const int n = ps.size();
    int k = 0;
    polygon qs(2*n);
    for(int i=0; i<n; ++i) {
        while(k > 1 && ccw(qs[k-2], qs[k-1], ps[i]) <= 0) {
            k--;
        }
        qs[k++] = ps[i];
    }
    for(int i=n-2, t = k; i>=0; --i) {
        while(k > t && ccw(qs[k-2], qs[k-1], ps[i]) <= 0) {
            k--;
        }
        qs[k++] = ps[i];
    }
    qs.resize(k-1);
    return qs;
}

int is_in_polygon(polygon const& poly, point p) {
    int N = poly.size();
    ld sum = 0;
    for(int i = 0; i < N; ++i) {
        point p1 = poly[i], p2 = poly[(i + 1) % N];
        if(isis_sp(segment(p1, p2), p)) {
            return 0;
        }
        sum += arg((p2 - p) / (p1 - p));
    }
    return std::abs(sum) < pi / 2 ? 2 : 1;
}

int main() {
    int n;
    ld p, q;
    cin >> n >> p >> q;
    vector<point> ps;
    ps.emplace_back(0, 0);
    ld ans = inf;
    for(int i = 0; i < n; ++i) {
        ld x, y;
        cin >> x >> y;
        ans = min(ans, max(p / x, q / y));
        ps.emplace_back(x, y);
    }
    std::sort(ps.begin(), ps.end(), [&](point const& p1, point const& p2) {
            if(real(p1) == real(p2)) {
                return imag(p1) < imag(p2);
            }
            return real(p1) < real(p2);
    });

    auto hull = convex_hull(ps);
    ld lb = 0, ub = 1e6;
    for(int lp = 0; lp < 55; ++lp) {
        const ld mid = (lb + ub) / 2;
        if(is_in_polygon(hull, point(p / mid, q / mid)) <= 1) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    ans = min(ans, lb);

    cout << fixed << setprecision(10) << ans << endl;
}
