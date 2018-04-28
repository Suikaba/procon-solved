#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2572

// 時間かかり過ぎ
// ハマったポイント
// -- 自明なNGケース（半径の2倍がそもそも収まらない）
// -- 半径が小さい方を右側にして配置する前提だったのに，swap するのを忘れていた

using ld = long double;
using point = complex<ld>;

constexpr ld eps = 1e-5;
constexpr ld pi = acos(-1.0);

struct circle {
    circle(point p, ld r) : p(p), r(r) {}
    point p;
    ld r;
};

vector<point> is_cc(circle const& c1, circle const& c2) {
    vector<point> res;
    ld d = abs(c1.p - c2.p);
    ld rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
    ld dfr = c1.r * c1.r - rc * rc;
    if(abs(dfr) < eps) {
        dfr = 0;
    } else if(dfr < 0) {
        return res;
    }

    ld rs = sqrt(dfr);
    point diff = (c2.p - c1.p) / d;
    res.push_back(c1.p + diff * point(rc, rs));
    if(dfr != 0) {
        res.push_back(c1.p + diff * point(rc, -rs));
    }
    return res;
}

// assert: c1 is left position
ld intersect_area(circle c1, circle c2) {
    const ld d = abs(c1.p - c2.p);
    if(d >= c1.r + c2.r - eps) return 0;
    if(c1.r < c2.r) swap(c1.r, c2.r);
    if(d < eps) return (c2.r * c2.r * pi);

    auto ps = is_cc(c1, c2);
    assert(!ps.empty());

    ld rad1 = abs(arg(ps[0] - c1.p));
    ld S = c1.r * c1.r * rad1 - 0.5 * c1.r * c1.r * sin(2 * rad1);
    ld rad2 = pi - abs(arg(ps[0] - c2.p));
    S += c2.r * c2.r * rad2 - 0.5 * c2.r * c2.r * sin(2 * rad2);
    return S;
}

int main() {
    cout << fixed << setprecision(10);

    ld w, h, a, b, ab;
    while(cin >> w >> h >> a >> b >> ab) {
        if(w == 0) break;

        const ld ra = sqrt(a / pi);
        const ld rb = sqrt(b / pi);

        if(min(w, h) < ra * 2 || min(w, h) < rb * 2) {
            cout << "impossible" << endl;
            continue;
        }

        circle c1(point(0, 0), ra);
        ld d = 0;
        { // calc dist
            ld lb = abs(ra - rb), ub = ra + rb;
            for(int loop = 0; loop < 100; ++loop) {
                const ld mid = (ub + lb) / 2;
                circle c2(point(mid, 0), rb);
                if(intersect_area(c1, c2) + eps < ab) {
                    ub = mid;
                } else {
                    lb = mid;
                }
            }

            d = lb;
        }
        // check
        bool swapped = ra < rb;
        c1.r = swapped ? rb : ra;
        c1.p = point(c1.r, c1.r);
        circle c2(point(c1.r + d, c1.r), swapped ? ra : rb);
        assert(abs(intersect_area(c1, c2) - ab) < 2 * eps);
        {
            ld lb = 0, ub = pi / 2;
            for(int loop = 0; loop < 60; ++loop) {
                const ld mid = (lb + ub) / 2;
                c2.p = c1.p + point(cos(mid) * d, sin(mid) * d);
                if(imag(c2.p) + c2.r > h + eps || real(c2.p) - c2.r < -eps) {
                    ub = mid;
                } else if(real(c2.p) + c2.r > w + eps || imag(c2.p) - c2.r < -eps) {
                    lb = mid;
                } else {
                    break;
                }
            }
        }

        if(imag(c2.p) + c2.r <= h + eps && real(c2.p) + c2.r <= w + eps
           && imag(c2.p) - c2.r >= -eps && real(c2.p) - c2.r >= -eps) {
            if(swapped) swap(c1, c2);
            cout << real(c1.p) << ' ' << imag(c1.p) << ' ' << c1.r << ' ';
            cout << real(c2.p) << ' ' << imag(c2.p) << ' ' << c2.r << endl;
        } else {
            cout << "impossible" << endl;
        }
    }
}
