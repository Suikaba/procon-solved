#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <int Mod, bool IsPrime = false>
class mod_int {
    using ll = long long;

public:
    constexpr mod_int() : n(0) {}
    constexpr mod_int(int n_) : n(n_) {
        if(n >= Mod)     n %= Mod;
        else if(n < 0) n = (n % Mod + Mod) % Mod;
    }
    constexpr mod_int(ll n_) : n(n_) { n = (n + Mod) % Mod; }

    constexpr operator int() const { return n; }
    constexpr operator ll() const  { return n; }

    constexpr bool operator==(mod_int const& other) const { return n == other.n; }
    constexpr mod_int& operator+=(mod_int const& other) {
        if((n += other.n) >= Mod) n -= Mod;
        return *this;
    }
    constexpr mod_int& operator-=(mod_int const& other) {
        if((n += Mod - other.n) >= Mod) n -= Mod;
        return *this;
    }
    constexpr mod_int& operator*=(mod_int const& other) {
        n = (unsigned long long)n * other.n % Mod;
        return *this;
    }
    constexpr typename std::enable_if<IsPrime, mod_int>::type& operator/=(mod_int const& other) {
        return *this *= other.inverse();
    }
    constexpr mod_int operator+(mod_int other) const { return mod_int(*this) += other; }
    constexpr mod_int operator-(mod_int other) const { return mod_int(*this) -= other; }
    constexpr mod_int operator*(mod_int other) const { return mod_int(*this) *= other; }
    constexpr mod_int operator/(mod_int other) const { return mod_int(*this) /= other; }

    constexpr typename std::enable_if<IsPrime, mod_int>::type inverse() const {
        ll a = n, b = Mod, u = 1, v = 0;
        while(b) {
            ll t = a / b;
            a -= t * b; std::swap(a, b);
            u -= t * v; std::swap(u, v);
        }
        return mod_int(u);
    }

private:
    ll n;
};

template <int Mod, bool IsPrime>
std::ostream& operator<<(std::ostream& os, mod_int<Mod, IsPrime> const& n) {
    os << (int)n;
    return os;
}

constexpr int default_mod = 1000000007;

using mint = mod_int<default_mod, true>; // default

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

struct data_type {
    bool op; // 0: +, 1: *
    bool total; // all multiple ?
    mint l, r, val; // from_l, from_r, otherwise
    data_type(bool op_, bool t, mint l_, mint r_, mint val_) : op(op_), total(t), l(l_), r(r_), val(val_) {}
};

struct RMQ {
    using type = data_type;
    static type id() {
        return {false, true, mint(0), mint(0), mint(0)};
    }
    static type op(type const& l, type const& r) {
        if(!l.op && l.total) return r;
        if(!r.op && r.total) return l;
        auto res = id();
        res.op = l.op;
        res.val = l.val + r.val;
        if(r.op) {
            res.total = l.total && r.total;
            if(l.total) {
                res.l = l.l * r.l;
            } else {
                res.l = l.l;
            }
            if(r.total) {
                res.r = l.r * r.l;
            } else {
                res.r = r.r;
            }
            if(!l.total && !r.total) {
                res.val += l.r * r.l;
            }
        } else {
            res.total = false;
            res.l = l.l;
            if(r.total) {
                res.r = l.r * r.l;
            } else {
                res.r = r.r;
            }
            if(!l.total) {
                res.val += l.r;
            }
            res.val += r.l;
        }
        return res;
    }
};

using pii = pair<int, int>;

int main() {
    int n; cin >> n;
    vector<mint> a(n);
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        a[i] = x;
    }
    segment_tree<RMQ> seg(n);
    string s; cin >> s;
    seg.update(0, data_type{false, false, 0, a[0], 0});
    for(int i = 1; i < n; ++i) {
        if(s[i - 1] == '*') {
            seg.update(i, data_type{true, true, a[i], a[i], 0});
        } else {
            seg.update(i, data_type{false, false, 0, a[i], 0});
        }
    }


    int q; cin >> q;
    while(q--) {
        int t, x, y; cin >> t >> x >> y;
        if(t == 1) {
            x--;
            a[x] = y;
            if(seg.query(x, x + 1).op) { // "*"
                seg.update(x, data_type{true, true, a[x], a[x], 0});
            } else {
                seg.update(x, data_type{false, false, 0, a[x], 0});
            }
        } else if(t == 2) {
            if(seg.query(x, x + 1).op) {
                seg.update(x, data_type{false, false, 0, a[x], 0});
            } else {
                seg.update(x, data_type{true, true, a[x], a[x], 0});
            }
        } else { // output
            auto res = seg.query(x - 1, y);
            if(res.total) {
                cout << res.l << endl;
            } else {
                cout << res.l + res.val + res.r << endl;
            }
        }
    }
}
