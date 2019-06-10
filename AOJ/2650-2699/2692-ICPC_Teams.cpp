#include <bits/stdc++.h>
using namespace std;

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

constexpr int default_mod = 1000000009;

template <int Mod = default_mod>
mod_int<Mod, true> fact(int n, bool inv = false) {
    static std::vector<mod_int<Mod, true>> v1 = {1}, v2 = {1};
    if(n >= static_cast<int>(v1.size())) {
        const int from = v1.size(), to = n + 1024;
        v1.reserve(to); v2.reserve(to);
        for(int i = from; i < to; ++i) {
            v1.push_back(v1.back() * mod_int<Mod, true>(i));
            v2.push_back(v2.back() / mod_int<Mod, true>(i));
        }
    }
    return inv ? v2[n] : v1[n];
}

template <int Mod = default_mod>
mod_int<Mod, true> comb(int n, int r) { // nCr
    if(r < 0 || r > n) return 0;
    return fact<Mod>(n) * fact<Mod>(r, true) * fact<Mod>(n - r, true);
}

using mint = mod_int<default_mod, true>; // default

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    int root(int x) {
        return par[x] < 0 ? x : par[x] = root(par[x]);
    }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return;
        if(par[x] < par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
    }

    int size(int x) {
        return -par[root(x)];
    }

private:
    vector<int> par;
};

int main() {
    int n, m; cin >> n >> m;
    n *= 3; // to number of people
    map<int, int> idx;
    vector<int> a(m), b(m), c(m), ban;
    for(int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i] >> c[i];
        if(c[i] == 1) {
            ban.push_back(i);
        }
    }
    const int sz = [&] (){ // compress
        vector<int> xs;
        for(int i = 0; i < m; ++i) {
            xs.push_back(a[i]);
            xs.push_back(b[i]);
        }
        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), xs.end());
        for(int i = 0; i < m; ++i) {
            a[i] = lower_bound(begin(xs), end(xs), a[i]) - begin(xs);
            b[i] = lower_bound(begin(xs), end(xs), b[i]) - begin(xs);
        }
        return xs.size();
    }();

    mint ans = 0;
    vector<mint> inv6_fact(n, mint(1));
    {
        const mint inv6 = mint(6).inverse();
        for(int i = 1; i < n; ++i) {
            inv6_fact[i] = inv6_fact[i - 1] * inv6;
        }
    }
    for(int S = 0; S < (1 << ban.size()); ++S) { // same team
        union_find uf(sz);
        for(int i = 0; i < m; ++i) {
            if(c[i] == 1) continue;
            uf.unite(a[i], b[i]);
        }
        for(int i = 0; i < (int)ban.size(); ++i) {
            if(S & (1 << i)) {
                uf.unite(a[ban[i]], b[ban[i]]);
            }
        }
        int cnt_two = 0, cnt_three = 0;
        {
            bool check = true;
            vector<bool> f(sz);
            for(int i = 0; i < sz; ++i) {
                if(f[uf.root(i)]) continue;
                f[uf.root(i)] = true;
                check &= uf.size(i) <= 3;
                cnt_three += uf.size(i) == 3;
                cnt_two += uf.size(i) == 2;
            }
            check &= (n - cnt_three * 3 - cnt_two * 2) >= cnt_two;
            if(!check) continue; // not count
        }
        int tn = n - cnt_three * 3 - cnt_two * 2;
        mint tans = comb(tn, cnt_two) * fact(cnt_two);
        tn -= cnt_two;
        tans *= fact(tn) * inv6_fact[tn / 3] * fact(tn / 3, true);
        if(__builtin_popcount(S) & 1) {
            ans -= tans;
        } else {
            ans += tans;
        }
    }

    cout << ans << endl;
}
