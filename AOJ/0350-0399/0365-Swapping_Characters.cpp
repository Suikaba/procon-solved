// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0365

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
    using type = pii;
    static type id() {
        return make_pair(inf, inf);
    }
    static type op(type const& l, type const& r) {
        return std::min(l, r);
    }
};

struct RSQ {
    using type = int;
    static type id() { return 0; }
    static type op(type const& l, type const& r) { return l + r; }
};


int main() {
    string s; cin >> s;
    int k; cin >> k;
    const int n = s.size();
    segment_tree<RMQ> seg(n);
    segment_tree<RSQ> rsq(n, 1);
    for(int i = 0; i < n; ++i) {
        seg.update(i, make_pair(s[i] - 'a', i));
    }

    string ans;
    for(int i = 0; i < n; ++i) {
        int lb = 0, ub = n;
        while(ub - lb > 1) {
            const int mid = (lb + ub) / 2;
            (rsq.query(0, mid) <= k ? lb : ub) = mid;
        }
        auto p = seg.query(0, ub);
        ans += p.first + 'a';
        k -= rsq.query(0, p.second);
        seg.update(p.second, make_pair(inf, inf));
        rsq.update(p.second, 0);
    }

    cout << ans << endl;
}
