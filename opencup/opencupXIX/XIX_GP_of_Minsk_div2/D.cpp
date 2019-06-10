#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

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
    using type = pii; // (last val, idx)
    static type id() {
        return make_pair(0, -1);
    }
    static type op(type const& l, type const& r) {
        return max(l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, k; cin >> n >> k;
    vector<pii> vs;
    for(int i = 0; i < n; ++i) {
        int m; cin >> m;
        for(int j = 0; j < m; ++j) {
            int x; cin >> x;
            vs.emplace_back(x, i);
        }
    }
    sort(begin(vs), end(vs));
    vs.erase(unique(begin(vs), end(vs)), end(vs));
    const int m = vs.size();

    segment_tree<RMQ> seg(n);
    vector<int> prev(m, -1);
    vector<tuple<int, int, int, int>> updates; // (update_idx, val, idx, prev);
    for(int i = 0; i < m; ++i) {
        int val, idx; tie(val, idx) = vs[i];
        int l = idx - k - 1;
        auto ma = seg.query(max(0, l), idx);
        if(l < 0) {
            ma = max(ma, seg.query(n + l, n));
        }
        if(seg.query(idx, idx + 1).first < ma.first + 1) {
            if(ma.first != 0 || idx <= k) {
                updates.emplace_back(idx, ma.first + 1, i, ma.second);
            }
        }
        if(i == m - 1 || vs[i].first != vs[i + 1].first) {
            for(auto const [upd_idx, upd_val, vidx, pre_idx] : updates) {
                seg.update(upd_idx, make_pair(upd_val, vidx));
                prev[vidx] = pre_idx;
            }
            updates.clear();
        }
    }
    assert(updates.empty());

    auto [ans_v, cur] = seg.query(0, n);
    vector<pii> seq;
    while(cur != -1) {
        seq.emplace_back(vs[cur].second + 1, vs[cur].first);
        cur = prev[cur];
    }
    reverse(begin(seq), end(seq));

    cout << ans_v << endl;
    assert(ans_v == (int)seq.size());
    for(auto const [idx, val] : seq) {
        cout << idx << " " << val << endl;
    }
}