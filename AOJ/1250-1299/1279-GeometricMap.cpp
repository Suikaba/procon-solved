#include <bits/stdc++.h>
using namespace std;

// AOJ1279 Geometry Map
// 反省点：
// 問題文読解が甘い．intersection の定義を読めていなかった．
// 実装方針はどうだろう．特にやばい実装をしたという感じはないが……．この問題だとこんなものかな？

using pii = pair<int, int>;
using ld = long double;
using point = complex<ld>;

constexpr ld eps = 1e-8;
constexpr ld pi = acos(-1.0);

constexpr int inf = 1e9;

ld dist(pii const& p1, pii const& p2) {
    point a(p1.first, p1.second);
    point b(p2.first, p2.second);
    return abs(a - b);
}

struct segment {
    segment(pii a, pii b, int ai, int bi) : a(a), b(b), ai(ai), bi(bi) {}
    pii a, b;
    int ai, bi;
};

bool isis_sp(segment const& s, pii const& p) {
    return abs(dist(s.a, p) + dist(s.b, p) - dist(s.a, s.b)) < eps;
}

// segment is not cross, so this is ok
bool isis_ss(segment const& s1, segment const& s2) {
    return isis_sp(s1, s2.a) || isis_sp(s1, s2.b) || isis_sp(s2, s1.a) || isis_sp(s2, s1.b);
}

struct edge {
    int to, cost;
};

using edges = vector<edge>;
using graph = vector<edges>;

void add_edge(graph& g, int from, int to, int cost) {
    g[from].push_back({to, cost});
}

int main() {
    int n;
    while(cin >> n, n) {
        pii sp, gp;
        cin >> sp.first >> sp.second >> gp.first >> gp.second;
        vector<pii> ps = {sp, gp};
        vector<pii> p1(n), p2(n);
        for(int i = 0; i < n; ++i) {
            cin >> p1[i].first >> p1[i].second >> p2[i].first >> p2[i].second;
            ps.push_back(p1[i]);
            ps.push_back(p2[i]);
        }
        sort(begin(ps), end(ps));
        ps.erase(unique(begin(ps), end(ps)), end(ps));
        const int m = ps.size();

        auto get_idx = [&](pii p) {
            return lower_bound(begin(ps), end(ps), p) - begin(ps);
        };

        vector<segment> segs;
        for(int i = 0; i < n; ++i) {
            segs.emplace_back(p1[i], p2[i], get_idx(p1[i]), get_idx(p2[i]));
        }

        auto segment_arrangement = [&]() {
            vector<segment> res;
            for(int i = 0; i < n; ++i) {
                vector<pair<ld, int>> v;
                for(int j = 0; j < m; ++j) {
                    if(isis_sp(segs[i], ps[j])) {
                        v.emplace_back(dist(segs[i].a, ps[j]), j);
                    }
                }
                sort(begin(v), end(v));
                for(int j = 0; j + 1 < (int)v.size(); ++j) {
                    int p1 = v[j].second, p2 = v[j + 1].second;
                    res.emplace_back(ps[p1], ps[p2], p1, p2);
                }
            }
            return res;
        };
        segs = segment_arrangement();
        n = segs.size();

        vector<int> on_seg(m);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                on_seg[i] += isis_sp(segs[j], ps[i]);
            }
        }
        vector<bool> is_road(n); // is_mark is !is_road
        for(int i = 0; i < n; ++i) {
            is_road[i] = on_seg[segs[i].ai] > 1 && on_seg[segs[i].bi] > 1;
        }
        vector<int> is_intersection(m);
        vector<int> is_sign_intersection(m);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(is_road[j]) {
                    is_intersection[i] += isis_sp(segs[j], ps[i]);
                } else {
                    is_sign_intersection[i] |= isis_sp(segs[j], ps[i]);
                }
            }
        }
        for(int i = 0; i < m; ++i) {
            is_intersection[i] -= is_sign_intersection[i];
        }

        vector<vector<bool>> can_use(m, vector<bool>(m, false));
        for(int i = 0; i < n; ++i) {
            can_use[segs[i].ai][segs[i].bi] = true;
            can_use[segs[i].bi][segs[i].ai] = true;
        }
        for(int i = 0; i < n; ++i) {
            if(is_road[i]) continue; // select sign
            point pa = point(segs[i].a.first, segs[i].a.second);
            point pb = point(segs[i].b.first, segs[i].b.second);
            auto vec = (on_seg[segs[i].ai] > 1 ? pb - pa : pa - pb);
            for(int j = 0; j < n; ++j) {
                if(!is_road[j] || !isis_ss(segs[i], segs[j])) continue; // select related road
                auto v = point(segs[j].b.first - segs[j].a.first, segs[j].b.second - segs[j].a.second); // a to b
                if(abs(abs(arg(v / vec)) - pi / 2) < eps) {
                    can_use[segs[j].ai][segs[j].bi] = false;
                    can_use[segs[j].bi][segs[j].ai] = false;
                } else if(abs(arg(v / vec)) + eps < pi / 2) {
                    can_use[segs[j].ai][segs[j].bi] = false;
                } else {
                    can_use[segs[j].bi][segs[j].ai] = false;
                }
            }
        }

        graph g(m);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < m; ++j) {
                if(i == j) continue;
                if(can_use[i][j]) {
                    add_edge(g, i, j, dist(ps[i], ps[j]));
                }
            }
        }
        vector<int> d(m, inf);
        vector<int> prev(m, -1);
        d[get_idx(sp)] = 0;
        priority_queue<pii, vector<pii>, greater<pii>> que;
        que.emplace(0, get_idx(sp));
        while(!que.empty()) {
            int cur_d, v;
            tie(cur_d, v) = que.top();
            que.pop();
            if(cur_d > d[v]) continue;
            for(auto const& e : g[v]) {
                if(d[e.to] > cur_d + e.cost) {
                    d[e.to] = cur_d + e.cost;
                    prev[e.to] = v;
                    que.emplace(cur_d + e.cost, e.to);
                }
            }
        }

        if(d[get_idx(gp)] == inf) {
            cout << -1 << endl;
        } else {
            int now = get_idx(gp);
            vector<pii> ans;
            while(now != -1) {
                if(is_intersection[now] >= 2) {
                    ans.push_back(ps[now]);
                }
                now = prev[now];
            }
            reverse(begin(ans), end(ans));
            for(auto& p : ans) {
                cout << p.first << ' ' << p.second << endl;
            }
            cout << 0 << endl;
        }
    }
}
