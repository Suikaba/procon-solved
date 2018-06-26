#include <bits/stdc++.h>
using namespace std;

// 反省点
// 実装方針をサボったことにより条件がいろいろ面倒になった．
// しかも実装長すぎだし．幾何だからこそ実装方針はちゃんと詰めたほうがいい．

using ld = long double;
using point = complex<ld>;
using polygon = vector<point>;

constexpr ld eps = 1e-8;
constexpr ld pi = acos(-1.0);

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

bool isis_sp(segment s, point p) {
    return (std::abs(s.a - p) + std::abs(s.b - p) - std::abs(s.b - s.a) < eps);
}

bool isis_ll(line l, line m) {
    return !(abs(cross(l.b - l.a, m.b - m.a)) < eps);
}

bool isis_ls(line l, segment s) {
    return (cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < eps);
}

bool isis_ss(segment s, segment t) {
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0
        && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

point is_ll(line s, line t) {
    point sv = s.b - s.a, tv = t.b - t.a;
    assert(cross(sv, tv) != 0);
    return s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv);
}

// 0 -> on, 1 -> in, 2 -> out
int is_in_polygon(polygon const& poly, point p) {
    int N = poly.size();
    ld sum = 0;
    for(int i=0; i<N; ++i) {
        point p1 = poly[i], p2 = poly[(i+1)%N];
        if(isis_sp(segment(p1, p2), p)) {
            return 0;
        }
        sum += arg((p2 - p) / (p1 - p));
    }
    return std::abs(sum) < pi / 2 ? 2 : 1;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<polygon> polys(n);
    for(int i = 0; i < n; ++i) {
        int l; cin >> l;
        for(int j = 0; j < l; ++j) {
            ld x, y;
            cin >> x >> y;
            polys[i].emplace_back(x, y);
        }
    }
    vector<ld> x(m), y(m);
    for(int i = 0; i < m; ++i) {
        cin >> x[i] >> y[i];
    }

    vector<line> ls;
    vector<point> cand;
    for(int i = 0; i < m; ++i) {
        for(auto& poly : polys) {
            for(auto& p : poly) {
                cand.push_back(p);
                ls.emplace_back(point(x[i], y[i]), p);
            }
        }
    }

    for(int i = 0; i < (int)ls.size(); ++i) {
        for(int j = i + 1; j < (int)ls.size(); ++j) {
            if(isis_ll(ls[i], ls[j])) {
                auto p = is_ll(ls[i], ls[j]);
                bool ok = true;
                for(auto& poly : polys) {
                    ok &= is_in_polygon(poly, p) != 1;
                }
                if(ok) {
                    cand.emplace_back(is_ll(ls[i], ls[j]));
                }
            }
        }
    }

    int ans = 0;
    for(auto& p : cand) {
        int t = 0;
        for(int i = 0; i < m; ++i) {
            segment s1(point(x[i], y[i]), p);
            if(abs(s1.a - p) < eps) continue; // ok
            bool ok = true;
            for(auto& poly : polys) {
                const int sz = poly.size();
                vector<point> cp;
                for(int j = 0; j < sz; ++j) {
                    segment s2(poly[j], poly[(j + 1) % sz]);
                    if(isis_ss(s1, s2)) {
                        cp.push_back(is_ll(line(s1), line(s2)));
                    }
                }
                sort(begin(cp), end(cp),
                     [](auto const& p1, auto const& p2) {
                         return real(p1) < real(p2) || (real(p1) <= real(p2) && imag(p1) < imag(p2));
                     });
                {
                    vector<point> cp2;
                    for(int i = 0; i < (int)cp.size(); ++i) {
                        if(cp2.empty() || abs(cp2.back() - cp[i]) > eps) cp2.push_back(cp[i]);
                    }
                    cp = move(cp2);
                }
                if(cp.size() >= 2u && abs(cp[0] - cp[1]) >= eps) {
                    ok = false;
                }
            }
            t += ok;
        }
        ans = max(ans, t);
    }

    cout << ans << endl;

}
