//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1288

#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using point = complex<ld>;

constexpr ld eps = 1e-10;

bool comp(point a, point b) {
    return (real(a - b) * 1.347589 + imag(a - b)) > 0;
}

ld dot(point a, point b) {
    return real(conj(a) * b);
}

ld cross(point a, point b) {
    return imag(conj(a) * b);
}

vector<point> unique(vector<point> ps) {
    sort(begin(ps), end(ps), comp);
    vector<point> res;
    for(auto& p : ps) {
        if(res.empty() || abs(res.back() - p) > eps) {
            res.push_back(p);
        }
    }
    return res;
}

struct segment {
    segment(point a, point b) : a(a), b(b) {}
    bool operator<(segment other) const {
        return min(real(a), real(b)) < min(real(other.a), real(other.b));
    }
    point a, b;
};

int ccw(point a, point b, point c) {
    b -= a; c -= a;
    if(cross(b, c) > eps)           return 1;  // a -> b -> c : counterclockwise
    if(cross(b, c) < -eps)          return -1; // a -> b -> c : clockwise
    if(dot(b, c) < 0)               return 2;  // c -> a -> b : line
    if(std::norm(b) < std::norm(c)) return -2; // a -> b -> c : line
    return 0;                                  // a -> c -> b : line
}

bool isis_ss(segment s, segment t) {
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0
        && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

point rotate(point p, ld theta) {
    const ld x = real(p), y = imag(p);
    return point(x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta));
}

int main() {
    int n;
    while(cin >> n, n) {
        vector<segment> ss;
        for(int i = 0; i < n; ++i) {
            ld x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            ss.emplace_back(point(x1, y1), point(x2, y2));
        }
        vector<vector<int>> g(n, vector<int>(n));
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                if(isis_ss(ss[i], ss[j])) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }
        vector<vector<segment>> digits;
        vector<bool> used(n);
        function<void(int, vector<segment>&)> dfs = [&](int v, vector<segment>& d) {
            used[v] = true;
            d.push_back(ss[v]);
            for(auto to : g[v]) {
                if(used[to]) continue;
                dfs(to, d);
            }
        };
        for(int i = 0; i < n; ++i) {
            if(used[i]) continue;
            vector<segment> digit;
            dfs(i, digit);
            digits.push_back(move(digit));
        }

        vector<int> ans(10);
        for(auto& d : digits) {
            if(d.size() == 1) {
                ans[1]++;
            } else if(d.size() == 3 || d.size() == 4) {
                vector<point> ps;
                for(auto& s : d) {
                    ps.push_back(s.a);
                    ps.push_back(s.b);
                }
                ps = unique(ps);
                if(ps.size() == 4) {
                    ans[d.size() == 3 ? 7 : 0]++;
                } else if(ps.size() == 5) {
                    ans[d.size() == 3 ? 4 : 9]++;
                } else if(ps.size() == 6) {
                    ans[3]++;
                } else {
                    assert(false); // !unreachable()
                }
            } else {
                int is_eight_or_six = 0;
                for(auto& s : d) {
                    int cnt = 0;
                    for(auto& s2 : d) {
                        cnt += isis_ss(s, s2);
                    }
                    is_eight_or_six += cnt == 4;
                }
                if(is_eight_or_six == 2) {
                    ans[8] += 1;
                } else if(is_eight_or_six == 1) {
                    ans[6] += 1;
                } else {
                    const ld rad = -arg(d[0].a - d[0].b);
                    vector<segment> hori, vert;
                    for(auto& s : d) {
                        s.a = rotate(s.a, rad);
                        s.b = rotate(s.b, rad);
                        if(abs(real(s.a) - real(s.b)) < eps) {
                            vert.push_back(s);
                        } else {
                            hori.push_back(s);
                        }
                    }

                    if(hori.size() == 2) {
                        if(hori[1] < hori[0]) swap(hori[0], hori[1]);
                        if(imag(hori[0].a) > imag(hori[1].a)) {
                            ans[2] += 1;
                        } else {
                            ans[5] += 1;
                        }
                    } else if(vert.size() == 2) {
                        if(vert[1] < vert[0]) swap(vert[0], vert[1]);
                        if(min(imag(vert[0].a), imag(vert[0].b)) > min(imag(vert[1].a), imag(vert[1].b))) {
                            ans[5] += 1;
                        } else {
                            ans[2] += 1;
                        }
                    } else {
                        assert(false); // !unreachable()
                    }
                }
            }
        }
        for(int i = 0; i < 10; ++i) {
            cout << ans[i] << " \n"[i + 1 == 10];
        }
    }
}