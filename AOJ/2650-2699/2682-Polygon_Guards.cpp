#include <bits/stdc++.h>
using namespace std;

using ld = double;
using ll = long long;
using point = std::complex<ld>;
using polygon = std::vector<point>;

constexpr ld eps = 1e-10;
const ld pi = acos(-1.0);

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

bool isis_ss(segment s, segment t) {
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0
        && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

bool isis_sp(segment s, point p) {
    return (std::abs(s.a - p) + std::abs(s.b - p) - std::abs(s.b - s.a) < eps);
}

point is_ll(line s, line t) {
    point sv = s.b - s.a, tv = t.b - t.a;
    assert(cross(sv, tv) != 0);
    return s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv);
}

vector<point> is_ss(segment s1, segment s2) {
    assert(isis_ss(s1, s2));
    vector<point> res;
    if(cross(s1.b - s1.a, s2.b - s2.a) == 0) {
        if(isis_sp(s1, s2.a)) res.push_back(s2.a);
        if(isis_sp(s1, s2.b)) res.push_back(s2.b);
        if(isis_sp(s2, s1.a)) res.push_back(s1.a);
        if(isis_sp(s2, s1.b)) res.push_back(s1.b);
    } else {
        res.push_back(is_ll(line(s1), line(s2)));
    }
    return res;
}

// 0 -> on, 1 -> in, 2 -> out
int is_in_polygon(polygon const& poly, point p) {
    const int n = poly.size();
    ld sum = 0;
    for(int i = 0; i < n; ++i) {
        point p1 = poly[i], p2 = poly[(i + 1) % n];
        if(isis_sp(segment(p1, p2), p)) {
            return 0;
        }
        sum += arg((p2 - p) / (p1 - p));
    }
    return std::abs(sum) < pi / 2 ? 2 : 1;
}

int dfs(polygon const& ps, int i, ll cur_vis, ll used, vector<ll> const& vis) {
    const int n = ps.size();
    if(cur_vis == (1LL << n) - 1) return __builtin_popcountll(used);
    if(i == n) return 9;
    int res = dfs(ps, i + 1, cur_vis, used, vis);
    if(__builtin_popcountll(used) < 8) {
        res = min(res, dfs(ps, i + 1, cur_vis | vis[i], used | (1LL << i), vis));
    }
    return res;
}

int main() {
    int n; cin >> n;
    polygon ps(n);
    for(int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        ps[i] = point(x, y);
    }

    vector<ll> vis(n);
    for(int i = 0; i < n; ++i) {
        vis[i] = 1LL << i;
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;
            segment s(ps[i], ps[j]);
            bool check = true;
            for(int k = 0; k < n; ++k) {
                segment t(ps[k], ps[(k + 1) % n]);
                if(!isis_ss(s, t)) continue;
                const auto delta = (ps[j] - ps[i]) / abs(ps[i] - ps[j]) * 0.001;
                for(auto p : is_ss(s, t)) {
                    if(abs(s.a - p) > eps && abs(s.b - p) > eps) {
                        check &= is_in_polygon(ps, p + delta) != 2 && is_in_polygon(ps, p - delta) != 2;
                    }
                }
                check &= is_in_polygon(ps, ps[i] + delta) != 2;
                check &= is_in_polygon(ps, ps[j] - delta) != 2;
            }
            if(check) {
                vis[i] |= 1LL << j;
            }
        }
    }

    cout << dfs(ps, 0, 0, 0, vis) << endl;
}
