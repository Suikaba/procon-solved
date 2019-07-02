#include <bits/stdc++.h>
using namespace std;

using ld = double;
using point = std::complex<ld>;
using polygon = std::vector<point>;

constexpr ld inf = 1e20;
constexpr ld eps = 1e-10;

bool comp(point a, point b) {
    return std::real(a) < std::real(b) || (std::real(a) <= std::real(b) && std::imag(a) < std::imag(b));
}

ld dot(point const& a, point const& b) {
    const ld r1 = real(a), r2 = real(b);
    const ld i1 = imag(a), i2 = imag(b);
    return r1 * r2 + i1 * i2;
}
ld cross(point const& a, point const& b) {
    const ld r1 = real(a), r2 = real(b);
    const ld i1 = imag(a), i2 = imag(b);
    return r2 * i1 - r1 * i2;
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

point proj(line l, point p) {
    ld t = dot(p - l.a, l.a - l.b) / std::norm(l.a - l.b);
    return l.a + t * (l.a - l.b);
}

polygon convex_hull(std::vector<point> ps) {
    std::sort(ps.begin(), ps.end(), comp);
    const int n = ps.size();
    int k = 0;
    polygon qs(2 * n);
    for(int i = 0; i < n; ++i) {
        while(k > 1 && ccw(qs[k - 2], qs[k - 1], ps[i]) <= 0) {
            k--;
        }
        qs[k++] = ps[i];
    }
    for(int i = n - 2, t = k; i >= 0; --i) {
        while(k > t && ccw(qs[k - 2], qs[k - 1], ps[i]) <= 0) {
            k--;
        }
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(10);

    int n;
    while(cin >> n) {
        polygon ps(n);
        for(int i = 0; i < n; ++i) {
            int x, y; cin >> x >> y;
            ps[i] = point(x, y);
        }
        ps = convex_hull(ps);
        n = ps.size();

        int most_far = 1, most_right = 1, most_left = 0;
        ld ans = inf;
        { // find initial right
            const auto vec = (ps[1] - ps[0]);
            while(true) {
                const auto cur = dot(vec, ps[most_left] - ps[1]);
                const auto v1 = dot(vec, ps[(most_left + n - 1) % n] - ps[1]);
                if(v1 - eps <= cur) {
                    most_left = (most_left + n - 1) % n;
                } else {
                    break;
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            const auto vec = ps[(i + 1) % n] - ps[i];
            const auto a = abs(vec);
            while(true) { // search most far
                const auto cur_d = abs(cross(vec, ps[most_far] - ps[i]));
                const auto nxt_d = abs(cross(vec, ps[(most_far + 1) % n] - ps[i]));
                if(nxt_d + eps < cur_d) break;
                most_far = (most_far + 1) % n;
            }
            while(true) { // search left
                const auto v1 = dot(vec, ps[most_left] - ps[i]);
                const auto v2 = dot(vec, ps[(most_left + 1) % n] - ps[i]);
                if(v2 > v1 + eps) break;
                most_left = (most_left + 1) % n;
            }
            while(true) { // search right
                const auto v1 = dot(vec, ps[most_right] - ps[i]);
                const auto v2 = dot(vec, ps[(most_right + 1) % n] - ps[i]);
                if(v2 + eps < v1) break;
                most_right = (most_right + 1) % n;
            }

            const auto d1 = abs(dot(vec, ps[most_left] - ps[i])) / a;
            const auto d2 = abs(dot(vec, ps[most_right] - ps[i])) / a;
            const auto d3 = abs(cross(vec, ps[most_far] - ps[i])) / a;
            ans = min(ans, 2 * (d1 + d2 + d3));
        }

        cout << ans << "\n";
    }
}
