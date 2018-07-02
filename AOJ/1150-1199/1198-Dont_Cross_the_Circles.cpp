#include <bits/stdc++.h>

// 反省点
// unique がバグってた．直せたのでよし（今までよく通ってたな…）

using ld = long double;

constexpr ld eps = 1e-8;
constexpr ld pi = std::acos(-1.0);

using point = std::complex<long double>;
using polygon = std::vector<point>;

bool comp(point a, point b) {
    return std::real(a) < std::real(b) || (std::real(a) <= std::real(b) && std::imag(a) < std::imag(b));
}

std::vector<point> unique(std::vector<point> ps) {
    std::sort(std::begin(ps), std::end(ps), comp);
    std::vector<point> res;
    for(auto& p : ps) {
        if(res.empty() || abs(res.back() - p) > eps) {
            res.push_back(p);
        }
    }
    return res;
}


class segment {
public:
    segment()
        : a(point(0, 0)),
          b(point(0, 0))
    {}
    segment(point a_, point b_)
        : a(a_), b(b_)
    {}

    point a, b;
};

bool isis_sp(segment s, point p) {
    return (std::abs(s.a - p) + std::abs(s.b - p) - std::abs(s.b - s.a) < eps);
}

// 0 -> on, 1 -> in, 2 -> out
int is_in_polygon(polygon const& poly, point p) {
    int N = poly.size();
    ld sum = 0;
    for(int i = 0; i < N; ++i) {
        point p1 = poly[i], p2 = poly[(i + 1) % N];
        if(isis_sp(segment(p1, p2), p)) {
            return 0;
        }
        sum += std::arg((p2 - p) / (p1 - p));
    }
    return std::abs(sum) < pi / 2 ? 2 : 1;
}

struct edge {
    int from, to;
};

using edges = std::vector<edge>;
using graph = std::vector<edges>;

struct dual_graph_data {
    graph g; // vertex id is polygon index
    std::vector<std::vector<int>> polys; // point ps[poly[i][j]]
};
// ss: segments, ps: segment endpoints
// [required] any two segments must not cross
dual_graph_data dual_graph(std::vector<segment> const& ss, std::vector<point> const& ps) {
    const int n = ps.size();
    std::vector<std::vector<int>> poly;
    std::vector<std::vector<std::tuple<ld, int, bool>>> tup(n);
    std::vector<std::vector<std::vector<int>>> seg2p(n, std::vector<std::vector<int>>(n));
    for(auto& s : ss) {
        int a = -1, b = -1;
        for(int i = 0; i < n; ++i) {
            if(std::abs(s.a - ps[i]) < eps) {
                a = i;
            }
            if(std::abs(s.b - ps[i]) < eps) {
                b = i;
            }
        }
        assert(a >= 0 && b >= 0);
        tup[a].emplace_back(std::arg(s.b - s.a), b, false);
        tup[b].emplace_back(std::arg(s.a - s.b), a, false);
    }
    for(int i = 0; i < n; ++i) {
        std::sort(std::begin(tup[i]), std::end(tup[i]));
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (int)tup[i].size(); ++j) {
            ld angle;
            int pos = j, src = i, dst;
            bool flag;
            std::tie(angle, dst, flag) = tup[i][j];
            if(flag) continue;
            std::vector<int> ps2;
            while(!flag) {
                ps2.push_back(src);
                std::get<2>(tup[src][pos]) = true;
                seg2p[src][dst].push_back(poly.size());
                seg2p[dst][src].push_back(poly.size());
                angle += pi + eps;
                if(angle > pi) angle -= 2 * pi;
                auto it = std::lower_bound(std::begin(tup[dst]), std::end(tup[dst]), std::make_tuple(angle, 0, false));
                if(it == tup[dst].end()) it = tup[dst].begin();
                src = dst;
                std::tie(angle, dst, flag) = *it;
                pos = it - tup[src].begin();
            }
            poly.push_back(ps2);
        }
    }

    graph g(poly.size());
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < i; ++j) {
            if(seg2p[i][j].size() == 2u) {
                int src = seg2p[i][j][0], dst = seg2p[i][j][1];
                g[src].push_back(edge{src, dst});
                g[dst].push_back(edge{dst, src});
            }
        }
    }
    return dual_graph_data { g, poly };
}

using namespace std;

int main() {
    int n, m;
    while(cin >> n >> m, n) {
        vector<point> cp(n);
        vector<ld> r(n), px(m), py(m), qx(m), qy(m);
        for(int i = 0; i < n; ++i) {
            ld cx, cy;
            cin >> cx >> cy >> r[i];
            cp[i] = point(cx, cy);
        }
        for(int i = 0; i < m; ++i) {
            cin >> px[i] >> py[i] >> qx[i] >> qy[i];
        }

        vector<segment> segs;
        vector<point> ps;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                if(abs(cp[i] - cp[j]) <= r[i] + r[j]) {
                    segs.emplace_back(cp[i], cp[j]);
                    ps.push_back(cp[i]);
                    ps.push_back(cp[j]);
                }
            }
        }
        ps = unique(move(ps));

        auto polys = dual_graph(segs, ps).polys;
        for(int i = 0; i < m; ++i) {
            auto pp = point(px[i], py[i]), qp = point(qx[i], qy[i]);
            vector<int> s1, s2;
            for(int j = 0; j < n; ++j) {
                if(abs(cp[j] - pp) <= r[j]) s1.push_back(j);
                if(abs(cp[j] - qp) <= r[j]) s2.push_back(j);
            }
            bool ng = s1 != s2;
            polygon debug;
            point d1, d2;
            if(s1.empty() && s2.empty()) {
                for(auto& poly : polys) {
                    polygon pol;
                    for(auto pi : poly) {
                        pol.push_back(ps[pi]);
                    }
                    int in1 = is_in_polygon(pol, pp);
                    int in2 = is_in_polygon(pol, qp);
                    ng |= (in1 == 1 && in2 == 2) || (in1 == 2 && in2 == 1);
                }
            }

            cout << (ng ? "NO" : "YES") << " \n"[i + 1 == m];
        }
    }
}
