#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using point = std::complex<ld>;

constexpr ld eps = 1e-10;
const ld pi = std::acos(-1.0);

bool comp(point a, point b) {
    return std::real(a) < std::real(b) || (std::real(a) <= std::real(b) && std::imag(a) < std::imag(b));
}

ld dot(point const& a, point const& b) {
    return std::real(std::conj(a) * b);
}
ld cross(point const& a, point const& b) {
    return std::imag(std::conj(a) * b);
}

int ccw(point a, point b, point c) {
    b -= a; c -= a;
    if(cross(b, c) > eps) return 1;
    if(cross(b, c) < -eps) return -1;
    if(dot(b, c) < 0) return 2;
    if(std::norm(b) < std::norm(c)) return -2;
    return 0;
}

ld triangle_area(point a, point b, point c) {
    return 0.5 * abs(cross(b - a, c - a));
}

vector<ld> calc_area(vector<point> const& ps, bool rev = false) {
    vector<ld> S(ps.size());
    vector<point> upper = {ps[0]}, lower = {ps[0]};
    for(int i = 1; i < (int)ps.size(); ++i) {
        S[i] = S[i - 1];
        while(upper.size() >= 2u && ccw(upper[upper.size() - 2], upper.back(), ps[i]) == 1) {
            S[i] -= triangle_area(upper[upper.size() - 2], upper.back(), lower.back());
            upper.pop_back();
        }
        while(lower.size() >= 2u && ccw(lower[lower.size() - 2], lower.back(), ps[i]) == -1) {
            S[i] -= triangle_area(lower[lower.size() - 2], lower.back(), upper.back());
            lower.pop_back();
        }
        S[i] += triangle_area(upper.back(), lower.back(), ps[i]);
        upper.push_back(ps[i]);
        lower.push_back(ps[i]);
    }
    if(rev) reverse(begin(S), end(S));
    return S;
}

int main() {
    int n; cin >> n;
    vector<point> ps, rps;
    for(int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        ps.emplace_back(x, y);
        rps.emplace_back(-x, y);
    }
    sort(begin(ps), end(ps), comp);
    sort(begin(rps), end(rps), comp);

    const auto lS = calc_area(ps), rS = calc_area(rps, true);
    ll ans = rS[0];
    for(int i = 0; i + 1 < n; ++i) {
        if(ps[i + 1].real() - ps[i].real() < eps) continue;
        ans = min(ans, (ll)roundl(lS[i] + rS[i + 1]));
    }

    cout << ans << endl;
}
