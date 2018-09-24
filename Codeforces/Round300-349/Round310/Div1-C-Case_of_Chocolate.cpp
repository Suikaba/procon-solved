
// http://codeforces.com/contest/555/problem/C

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

struct RMQ {
    using type = int;
    static type id() {
        return std::numeric_limits<type>::max();
    }
    static type op(type const& l, type const& r) {
        return std::min(l, r);
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


int main() {
    int n, q; cin >> n >> q;
    set<pii> s;
    vector<int> x(q), y(q), xs = {1, n};
    vector<char> d(q);
    for(int i = 0; i < q; ++i) {
        cin >> x[i] >> y[i] >> d[i];
        for(int dx = 0; dx <= 1; ++dx) xs.push_back(x[i] + dx);
        for(int dy = 0; dy <= 1; ++dy) xs.push_back(y[i] + dy);
    }
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    for(int i = 0; i < q; ++i) {
        x[i] = lower_bound(begin(xs), end(xs), x[i]) - begin(xs);
        y[i] = lower_bound(begin(xs), end(xs), y[i]) - begin(xs);
    }
    const int m = xs.size();
    array<segment_tree<RMQ>, 2> seg = {{segment_tree<RMQ>(m), segment_tree<RMQ>(m)}};;
    for(int i = 0; i < q; ++i) {
        if(s.count(make_pair(x[i], y[i]))) {
            cout << 0 << endl;
            continue;
        }
        const bool b = d[i] == 'U';
        s.emplace(x[i], y[i]);
        int lb = -1, ub = (b ? y[i] : x[i]);
        while(ub - lb > 1) {
            const auto mid = (lb + ub) / 2;
            (seg[b].query(mid, ub) <= (b ? x[i] : y[i]) ? lb : ub) = mid;
        }
        cout << xs[(b ? y[i] : x[i])] - xs[ub] + 1 << endl;
        seg[!b].update((b ? x[i] : y[i]), ub);
    }
}
