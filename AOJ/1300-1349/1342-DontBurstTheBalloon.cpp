#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1342

// îΩè»ì_
// ì¡Ç…Ç»ÇµÅDÇ»ÇÒÇ©Ç§Ç‹Ç≠åæÇ¡Çƒ15ï™Ç≈Ç©ÇØÇΩÅD

using ld = long double;
using point = complex<ld>;

constexpr ld eps = 1e-8;
constexpr ld pi = acos(-1.0);

ld dot(point a, point b) {
    return real(conj(a) * b);
}

ld cross(point a, point b) {
    return imag(conj(a) * b);
}

struct segment {
    segment() : a(0, 0), b(0, 0) {}
    segment(point a, point b) : a(a), b(b) {}

    point a, b;
};

struct circle {
    circle() : p(0, 0), r(0) {}
    circle(point p, ld r) : p(p), r(r) {}
    point p;
    ld r;
};

point proj(segment s, point p) {
    ld t = dot(p - s.a, s.a - s.b) / norm(s.a - s.b);
    return s.a + t * (s.a - s.b);
}

vector<point> is_sc(circle const& c, segment const& s) {
    vector<point> res;
    const point p = proj(s, c.p);
    const point vec = p - c.p;
    if(abs(vec) > c.r + eps) return res;
    if(abs(vec) < eps) {
        point v = abs(s.a - c.p) < eps ? s.b - c.p : s.a - c.p;
        point vv = v / abs(v) * c.r;
        res.push_back(vv);
        res.push_back(-vv);
    } else {
        const ld t = sqrt(c.r * c.r - norm(vec));
        res.push_back(p + vec / abs(vec) * point(0, -1) * t);
        res.push_back(p + vec / abs(vec) * point(0, 1) * t);
    }
    return res;
}

vector<point> is_cc(circle const& c1, circle const& c2) {
    vector<point> res;
    ld d = abs(c1.p - c2.p);
    ld rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
    ld dfr = c1.r * c1.r - rc * rc;
    if(abs(dfr) < eps) {
        dfr = 0;
    } else if(dfr < 0.0) {
        return res;
    }

    ld rs = sqrt(dfr);
    point diff = (c2.p - c1.p) / d;
    res.push_back(c1.p + diff * point(rc, rs));
    if(dfr != 0.0) {
        res.push_back(c1.p + diff * point(rc, -rs));
    }
    return res;
}

int main() {
    int n, w;
    while(cin >> n >> w, n) {
        vector<ld> x(n), y(n), h(n);
        for(int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i] >> h[i];
        }

        auto check = [&](const ld R) {
            vector<circle> cs(n);
            for(int i = 0; i < n; ++i) {
                if(h[i] <= R) cs[i].r = sqrt(2 * R * h[i] - h[i] * h[i]);
                else          cs[i].r = R;
                cs[i].p = point(x[i], y[i]);
            }

            const ld margin = (w <= R ? sqrt(2 * R * w - w * w) : R);
            if(margin >= 50) return false;

            vector<segment> ss;
            ss.emplace_back(point(margin, margin), point(100 - margin, margin));
            ss.emplace_back(point(margin, margin), point(margin, 100 - margin));
            ss.emplace_back(point(100 - margin, margin), point(100 - margin, 100 - margin));
            ss.emplace_back(point(margin, 100 - margin), point(100 - margin, 100 - margin));

            vector<point> ps = {point(margin, margin), point(margin, 100 - margin),
                                point(100 - margin, margin), point(100 - margin, 100 - margin)};
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < 4; ++j) {
                    for(auto&& p : is_sc(cs[i], ss[j])) ps.push_back(p);
                }
                for(int j = i + 1; j < n; ++j) {
                    for(auto&& p : is_cc(cs[i], cs[j])) ps.push_back(p);
                }
            }

            bool ok = false;
            for(auto& p : ps) {
                bool b = true;
                for(auto& c : cs) {
                    b &= abs(p - c.p) >= c.r - eps;
                }
                b &= real(p) >= margin - eps && real(p) - eps <= 100 - margin;
                b &= imag(p) >= margin - eps && imag(p) - eps <= 100 - margin;

                ok |= b;
            }

            return ok;
        };

        ld lb = 0, ub = 1e9;
        for(int lp = 0; lp < 50; ++lp) {
            const ld mid = (ub + lb) / 2;
            if(check(mid)) lb = mid;
            else           ub = mid;
        }

        cout << fixed << setprecision(10) << lb << endl;
    }
}
