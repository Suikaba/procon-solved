
// 解法
// 普通に式を立てて不等式を考えると詰まる。
// というわけで、風を -w -> w に動かしていったときに、2つの飛行機が同時刻に集まるとはどういうことかを観察する。
// 重要制約 xi * vi < 0 (飛行場に向かってくる) および |vi| > w から、
// -w -> w と動かしていったときの各飛行機の到着時刻は線形、つまり線分となる。
// 飛行機が同時刻に到着しうるとは、線分が交わることである。
// つまり、n 本の線分の交点の個数が答え。
// これは fenwick_tree などで反転数を求める要領で O(nlogn) で解ける。

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
class fenwick_tree {
public:
    fenwick_tree(int n_) : n(n_), dat(n, 0) {}

    void add(int i, T value) {
        for(; i < n; i |= i + 1) {
            dat[i] += value;
        }
    }

    T sum(int i) const {
        T res = 0;
        for(; i >= 0; i = (i & (i + 1)) - 1) {
            res += dat[i];
        }
        return res;
    }
    // [l, r)
    T sum(int l, int r) const {
        return sum(r - 1) - sum(l - 1);
    }

private:
    const int n;
    std::vector<T> dat;
};

struct rational {
    ll n, m;
    rational(ll a, ll b) : n(a), m(b) {
        const ll g = __gcd(a, b);
        n /= g, m /= g;
    }
    bool operator==(const rational& that) const {
        return n == that.n && m == that.m;
    }
    bool operator<(const rational& that) const {
        return n * that.m < that.n * m;
    }
};

int main() {
    int n, w; cin >> n >> w;
    vector<ll> x(n), v(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> v[i];
    }

    vector<rational> t2, ts2;
    vector<tuple<rational, rational, int>> ts;
    vector<int> ti2(n);
    for(int i = 0; i < n; ++i) {
        ts.emplace_back(rational{abs(x[i]), abs(v[i] - w)}, rational{abs(x[i]), abs(v[i] + w)}, i);
        t2.emplace_back(abs(x[i]), abs(v[i] + w));
        ts2.push_back(t2.back());
    }
    sort(begin(ts), end(ts), [] (auto const& p1, auto const& p2) {
        if(get<0>(p1) == get<0>(p2)) {
            return get<1>(p2) < get<1>(p1);
        }
        return get<0>(p1) < get<0>(p2);
    });
    sort(begin(ts2), end(ts2));
    ts2.erase(unique(begin(ts2), end(ts2)), end(ts2));
    for(int i = 0; i < n; ++i) {
        ti2[i] = lower_bound(begin(ts2), end(ts2), t2[i]) - begin(ts2);
    }

    ll ans = 0;
    fenwick_tree<ll> bit(n);
    for(int i = 0; i < n; ++i) {
        bit.add(ti2[i], 1);
    }
    for(int i = 0; i < n; ++i) {
        const int idx = get<2>(ts[i]);
        bit.add(ti2[idx], -1);
        ans += bit.sum(0, ti2[idx] + 1);
    }

    cout << ans << endl;
}