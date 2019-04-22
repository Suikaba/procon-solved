#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

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

struct LIS {
    using type = pll;
    static type id() {
        return make_pair(0, 0);
    }
    static type op(type const& l, type const& r) {
        return max(l, r);
    }
};

int main() {
    int n; cin >> n;
    vector<int> a(n), as;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        as.push_back(a[i]);
    }
    sort(begin(as), end(as));
    as.erase(unique(begin(as), end(as)), end(as));
    for(int i = 0; i < n; ++i) {
        a[i] = lower_bound(begin(as), end(as), a[i]) - begin(as);
    }

    segment_tree<LIS> seg(n);
    for(int i = 0; i < n; ++i) {
        auto ma = seg.query(0, a[i]);
        ma.first += 1;
        ma.second += as[a[i]];
        if(seg.query(a[i], a[i] + 1) < ma) {
            seg.update(a[i], ma);
        }
    }

    cout << seg.query(0, n).second << endl;
}