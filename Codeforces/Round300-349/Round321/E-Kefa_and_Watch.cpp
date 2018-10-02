// http://codeforces.com/contest/580/problem/E

#include <bits/stdc++.h>
using namespace std;

template <typename Monoid>
class lazy_segment_tree {
    using T1 = typename Monoid::type1;
    using T2 = typename Monoid::type2;

public:
    lazy_segment_tree(std::vector<T1> const& init)
        : sz(init.size()), n(expand(init.size())), h(std::ceil(std::log2(init.size()))),
          data(n * 2, Monoid::id1()), lazy(n * 2, Monoid::id2())
    {
        std::copy(std::begin(init), std::end(init), std::begin(data) + n);
        for(int i = n - 1; i >= 1; --i) {
            data[i] = Monoid::op1(data[i * 2], data[i * 2 + 1]);
        }
    }
    lazy_segment_tree(int n_, T1 init = Monoid::id1())
        : lazy_segment_tree(std::vector<T1>(n_, init))
    {}

    T1 query(int l, int r) {
        l += n, r += n;
        for(int i = h; i > 0; --i) {
            push(l >> i), push(r >> i);
        }
        T1 res1 = Monoid::id1(), res2 = Monoid::id1();
        while(l < r) {
            if(l & 1) res1 = Monoid::op1(res1, Monoid::op2(data[l], lazy[l])), ++l;
            if(r & 1) --r, res2 = Monoid::op1(res2, Monoid::op2(data[r], lazy[r]));
            l /= 2, r /= 2;
        }
        return Monoid::op1(res1, res2);
    }

    void update(int l, int r, T2 val) {
        assert(0 <= l && l <= r && r <= sz);
        l += n, r += n;
        for(int i = h; i > 0; --i) {
            push(l >> i), push(r >> i);
        }
        int tl = l, tr = r;
        while(l < r) {
            if(l & 1) lazy[l] = Monoid::op3(lazy[l], val), ++l;
            if(r & 1) --r, lazy[r] = Monoid::op3(lazy[r], val);
            l /= 2, r /= 2;
        }
        while(tr /= 2, tl /= 2) {
            if(lazy[tl] == Monoid::id2()) update(tl);
            if(lazy[tr] == Monoid::id2()) update(tr);
        }
    }

private:
    int expand(int n_) const {
        int res = 1;
        while(res < n_) res <<= 1;
        return res;
    }

    void push(int node) {
        if(lazy[node] == Monoid::id2()) return;
        if(node < n) {
            lazy[node * 2] = Monoid::op3(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = Monoid::op3(lazy[node * 2 + 1], lazy[node]);
        }
        data[node] = Monoid::op2(data[node], lazy[node]);
        lazy[node] = Monoid::id2();
    }

    void update(int node) {
        if(node * 2 + 1 >= (int)data.size()) return; // for n == max_r
        data[node] = Monoid::op1(Monoid::op2(data[node * 2], lazy[node * 2]),
                                 Monoid::op2(data[node * 2 + 1], lazy[node * 2 + 1]));
    }

private:
    int const sz, n, h;
    std::vector<T1> data;
    std::vector<T2> lazy;
};


using ll = long long;
using pll = pair<ll, ll>;

constexpr ll b[2] = {17LL, 19LL};
constexpr ll mod[2] = {999999937LL, 1000000007LL};
constexpr ll mod_inv[2] = {937499941, 55555556};

ll mod_pow(ll n, int i) {
    static vector<vector<ll>> res(2, vector<ll>(1, 1));
    while((int)res[0].size() <= n) {
        res[0].push_back(res[0].back() * b[0] % mod[0]);
        res[1].push_back(res[1].back() * b[1] % mod[1]);
    }
    return res[i][n];
}

struct RHash {
    struct type1 {
        type1(int v, int idx) : hs{{v, v}}, sz(1), lidx(idx) {}
        type1(array<ll, 2> h, ll sz_, int idx) : hs(h), sz(sz_), lidx(idx) {}
        bool operator==(type1 const& that) const {
            return hs == that.hs && sz == that.sz;
        }
        array<ll, 2> hs;
        ll sz, lidx;
    };
    using type2 = int;
    static type1 id1() {
        return type1({{-1, -1}}, 0, 0);
    }
    static type2 id2() { return -1; }
    static type1 op1(type1 const& l, type1 const& r) {
        if(l.sz == 0) return r;
        if(r.sz == 0) return l;
        array<ll, 2> hs;
        for(int i = 0; i < 2; ++i) {
            if(l.lidx < r.lidx) {
                hs[i] = (l.hs[i] + r.hs[i] * mod_pow(l.sz, i)) % mod[i];
            } else {
                hs[i] = (r.hs[i] + l.hs[i] * mod_pow(r.sz, i)) % mod[i];
            }
        }
        return type1(hs, l.sz + r.sz, min(l.lidx, r.lidx));
    }
    static type1 op2(type1 const& l, type2 const& r) {
        if(r == id2()) return l;
        array<ll, 2> hs;
        for(int i = 0; i < 2; ++i) {
            hs[i] = (r * ((mod_pow(l.sz, i) - 1 + mod[i]))) % mod[i];
            hs[i] = hs[i] * mod_inv[i] % mod[i];
        }
        return type1(hs, l.sz, l.lidx);
    }
    static type2 op3(type2 const& l, type2 const& r) {
        return r != id2() ? r : l;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    const int q = m + k;
    string s; cin >> s;
    vector<RHash::type1> a(n, RHash::id1());
    for(int i = 0; i < n; ++i) {
        a[i] = RHash::type1(s[i] - '0' + 1, i);
    }
    lazy_segment_tree<RHash> seg(a);
    for(int i = 0; i < q; ++i) {
        int qtype; cin >> qtype;
        if(qtype == 1) {
            int l, r, c; cin >> l >> r >> c;
            seg.update(l - 1, r, c + 1);
        } else {
            int l, r, d; cin >> l >> r >> d;
            l--;
            if(seg.query(l, r - d) == seg.query(l + d, r)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
}
