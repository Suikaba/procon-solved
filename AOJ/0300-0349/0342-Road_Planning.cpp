
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0342

#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using point = complex<ld>;
using polygon = vector<point>;

constexpr ld eps = 1e-8;

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

polygon convex_hull(std::vector<point> ps) {
    std::sort(std::begin(ps), std::end(ps),
              [](point const& p1, point const& p2) {
                  return std::real(p1) < std::real(p2)
                                         || (std::real(p1) <= std::real(p2) && std::imag(p1) < std::imag(p2));
              });
    const int n = ps.size();
    int k = 0;
    polygon qs(2 * n);
    for(int i = 0; i < n; ++i) {
        while(k > 1 && ccw(qs[k - 2], qs[k - 1], ps[i]) <= 0) k--;
        qs[k++] = ps[i];
    }
    for(int i = n - 2, t = k; i >= 0; --i) {
        while(k > t && ccw(qs[k - 2], qs[k - 1], ps[i]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}

class union_find {
public:
    union_find(int n) : par(n, -1) {}
    int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]); }
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }
private:
    vector<int> par;
};

struct edge {
    int u, v;
    ld cost;
    bool operator<(const edge& other) const {
        return cost < other.cost;
    }
};

int main() {
    int v, r;
    cin >> v >> r;
    vector<point> ps(v);
    for(int i = 0; i < v; ++i) {
        ld x, y;
        cin >> x >> y;
        ps[i] = point(x, y);
    }
    vector<edge> es;
    for(int i = 0; i < r; ++i) {
        int s, t;
        cin >> s >> t;
        es.push_back(edge{s - 1, t - 1, abs(ps[s - 1] - ps[t - 1])});
    }
    sort(begin(es), end(es));
    auto hull = convex_hull(ps);
    ld ans = 0;
    const int n = hull.size();
    union_find uf(v);
    for(int i = 0; i < n; ++i) {
        ans += abs(hull[i] - hull[(i + 1) % n]);
        int s = 0, t = 0;
        for(int j = 0; j < v; ++j) {
            if(abs(hull[i] - ps[j]) < eps) s = j;
            if(abs(hull[(i + 1) % n] - ps[j]) < eps) t = j;
        }
        uf.unite(s, t);
    }
    for(auto& e : es) {
        if(uf.unite(e.u, e.v)) {
            ans += e.cost;
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
}
