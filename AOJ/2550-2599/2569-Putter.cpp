#include <bits/stdc++.h>
using namespace std;

using ld = double;
using point = std::complex<ld>;
using polygon = std::vector<point>;

struct line {
    line() : a(0, 0), b(0, 0) {}
    line(point a_, point b_) : a(a_), b(b_) {}
    point a, b;
};

ld dot(point const& a, point const& b) {
    return std::real(std::conj(a) * b);
}
ld cross(point const& a, point const& b) {
    return std::imag(std::conj(a) * b);
}

point proj(line const& l, point const& p) {
    ld t = dot(p - l.a, l.a - l.b) / std::norm(l.a - l.b);
    return l.a + t * (l.a - l.b);
}

point reflect(line const& l, point const& p) {
    return p + (proj(l, p) - p) * 2.0;
}

point read_point() {
    ld x, y; cin >> x >> y;
    return point{x, y};
}

int main() {
    int n;
    while(cin >> n, n) {
        const auto sp = read_point();
        polygon ps;
        for(int i = 0; i < n; ++i) {
            ps.emplace_back(read_point());
        }

        vector<int> ord(n);
        iota(begin(ord), end(ord), 0);
        int ans = 0;
        do {
            auto ts = ps;
            vector<point> lvs, rvs;
            for(auto i : ord) {
                const auto a = ts[i], b = ts[(i + 1) % n];
                lvs.push_back(a + (b - a) / abs(b - a) * 1e-6 - sp);
                rvs.push_back(b + (a - b) / abs(b - a) * 1e-6 - sp);
                if(cross(rvs.back(), lvs.back()) < 0) swap(lvs.back(), rvs.back());
                for(int j = 0; j < n; ++j) {
                    if(j == i || (i + 1) % n == j) continue;
                    ts[j] = reflect(line{a, b}, ts[j]);
                }
            }
            auto lv = lvs[0], rv = rvs[0];
            bool check = true;
            for(int i = 1; i < n; ++i) {
                if(cross(lv, lvs[i]) <= 0) swap(lv, lvs[i]);
                if(cross(rv, rvs[i]) >= 0) swap(rv, rvs[i]);
                check &= cross(rv, lv) >= 0;
            }
            ans += check;
        } while(next_permutation(begin(ord), end(ord)));

        cout << ans << endl;
    }
}
