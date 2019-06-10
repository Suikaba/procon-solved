#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
constexpr int inf = 1e9;

template<typename Monoid>
class segment_tree {
    using T = typename Monoid::type;

public:
    segment_tree(std::vector<T> const& init)
        : sz(init.size()), n(expand(init.size()))
    {
        dat.assign(n*2, Monoid::id());
        std::copy(begin(init), end(init), begin(dat) + n);
        for(int i = n - 1; i >= 0; --i) {
            dat[i] = Monoid::op(dat[i * 2], dat[i * 2 + 1]);
        }
    }

    segment_tree(int const n_, T const& init = Monoid::id())
        : segment_tree(std::vector<T>(n_, init))
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
        l += n, r += n;
        T res1 = Monoid::id(), res2 = Monoid::id();
        while(l != r) {
            if(l & 1) res1 = Monoid::op(res1, dat[l++]);
            if(r & 1) res2 = Monoid::op(dat[--r], res2);
            l /= 2, r /= 2;
        }
        return Monoid::op(res1, res2);
    }

private:
    int expand(int n_) const {
        assert(n_ >= 1);
        return n_ == 1 ? n_ : expand((n_ + 1) / 2) * 2;
    }

private:
    const int sz, n;
    std::vector<T> dat;
};

struct RMQ {
    using type = int;
    static type id() {
        return inf;
    }
    static type op(type const& l, type const& r) {
        return std::min(l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, s, L; cin >> n >> s >> L;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if(L > n) {
        cout << -1 << endl;
        return 0;
    }

    segment_tree<RMQ> dp(n + 1, inf);
    dp.update(0, 0);
    multiset<int> mi;
    multiset<int, greater<>> ma, vals;
    int l = 0;
    vals.insert(0);
    for(int r = 0; r < n;) {
        mi.insert(a[r]), ma.insert(a[r]);
        r += 1;
        while(*ma.begin() - *mi.begin() > s) {
            mi.erase(mi.lower_bound(a[l]));
            ma.erase(ma.lower_bound(a[l]));
            l += 1;
        }
        if(r - L + 1 > l) {
            dp.update(r, dp.query(l, r - L + 1) + 1);
        }
    }

    const int ans = dp.query(n, n + 1);
    if(ans == inf) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}
