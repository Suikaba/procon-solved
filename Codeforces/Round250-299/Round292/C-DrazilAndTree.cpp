#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/problemset/problem/516/C

// 反省点
// 実装方針ミスったと思ってたけどそんなこともないらしい．

using ll = long long;

constexpr ll inf = numeric_limits<ll>::max() / 2;

struct rmq {
    using type = array<pair<ll, int>, 2>;
    static type id() {
        return {{ {-inf, -1}, {-inf, -1} }};
    }
    static type op(type const& l, type const& r) {
        type res = id();
        int j1 = 0, j2 = 0;
        for(int i = 0; i < 2; ++i) {
            if(l[j1].first > r[j2].first) {
                res[i].first = l[j1].first;
                res[i].second = l[j1++].second;
            } else {
                res[i].first = r[j2].first;
                res[i].second = r[j2++].second;
            }
        }
        return res;
    }
};

template<typename Monoid>
class segment_tree {
    using T = typename Monoid::type;

public:
    segment_tree(std::vector<T> const& init)
        : sz(init.size()),
          n(expand(init.size()))
    {
        dat.assign(n*2, Monoid::id());
        std::copy(begin(init), end(init), begin(dat) + n);
        for(int i = n - 1; i >= 0; --i) {
            dat[i] = Monoid::op(dat[i * 2], dat[i * 2 + 1]);
        }
    }

    segment_tree(int const n, T const& init = Monoid::id())
        : segment_tree(std::vector<T>(n, init))
    {}

    void update(int p, T val) {
        assert(0 <= p && p < sz);
        dat[p += n] = val;
        while(p /= 2) {
            dat[p] = Monoid::op(dat[p * 2], dat[p * 2 + 1]);
        }
    }

    // [l, r)
    T query(int l, int r) const {
        assert(0 <= l && l <= r && r <= sz);
        l += n;
        r += n;
        T res1 = Monoid::id(),
          res2 = Monoid::id();
        while(l != r) {
            if(l & 1) {
                res1 = Monoid::op(res1, dat[l++]);
            }
            if(r & 1) {
                res2 = Monoid::op(dat[--r], res2);
            }
            l /= 2;
            r /= 2;
        }
        return Monoid::op(res1, res2);
    }

    int size() const {
        return sz;
    }

private:
    int expand(int n) const {
        assert(n >= 1);
        return n == 1 ? n : expand((n + 1) / 2) * 2;
    }

private:
    const int sz;
    const int n;
    std::vector<T> dat;
};


int main() {
    int n, m;
    cin >> n >> m;
    vector<ll> d(n), h(2 * n);
    vector<rmq::type> dat1(2 * n, rmq::id()), dat2(2 * n, rmq::id());
    dat1[0][0].first = dat2[0][0].first = 0;
    for(int i = 0; i < n; ++i) {
        scanf("%lld", &d[i]);
    }
    for(int i = 0; i < n; ++i) {
        scanf("%lld", &h[i]);
    }
    for(int i = 0; i + 1 < 2 * n; ++i) {
        dat1[i + 1][0].first = dat1[i][0].first + d[i % n];
        dat2[i + 1][0].first = dat2[i][0].first - d[i % n];
    }
    for(int i = 0; i < 2 * n; ++i) {
        dat1[i][0].first += 2 * h[i % n];
        dat1[i][0].second = i;
        dat2[i][0].first += 2 * h[i % n];
        dat2[i][0].second = i;
    }

    segment_tree<rmq> seg1(dat1), seg2(dat2);
    while(m--) {
        int a, b;
        cin >> a >> b;
        rmq::type r1, r2;
        if(a <= b) {
            r1 = seg1.query(b, a + n - 1);
            r2 = seg2.query(b, a + n - 1);
        } else {
            r1 = seg1.query(b, a - 1);
            r2 = seg2.query(b, a - 1);
        }
        ll ans = 0;
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                if(r1[i].second != r2[j].second) {
                    ans = max(ans, r1[i].first + r2[j].first);
                }
            }
        }
        printf("%lld\n", ans);
    }
}
