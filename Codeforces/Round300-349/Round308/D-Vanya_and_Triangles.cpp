
// http://codeforces.com/contest/552/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

constexpr int inf = 1e9;

pair<pii, pii> create_line(int x1, int y1, int x2, int y2) {
    if(x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }
    const int dx = x2 - x1, dy = y2 - y1;
    if(dx == 0) return make_pair(make_pair(x1, inf), make_pair(inf, inf));
    const int n1 = x2 * y1 - x1 * y2;
    const int g = __gcd(abs(dx), abs(dy));
    const int g2 = __gcd(abs(n1), abs(dx));
    return make_pair(make_pair(dy / g, dx / g), make_pair(n1 / g2, dx / g2));
}

int main() {
    int n; cin >> n;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    map<pair<pii, pii>, pair<ll, vector<int>>> cnt;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            auto line = create_line(x[i], y[i], x[j], y[j]);
            auto& p = cnt[line];
            p.first += 1;
            p.second.push_back(i), p.second.push_back(j);
        }
    }

    ll ans = 0;
    for(auto& pp : cnt) {
        auto c = pp.second.first;
        auto& v = pp.second.second;
        sort(begin(v), end(v));
        v.erase(unique(begin(v), end(v)), end(v));
        ans += c * (n - v.size());
    }
    ans /= 3;
    cout << ans << endl;
}
