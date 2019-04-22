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

template <int Mod = default_mod>
mod_int<Mod, true> fact(int n) {
    static std::vector<mod_int<Mod, true>> v = {1};
    if(n >= static_cast<int>(v.size())) {
        const int from = v.size(), to = n + 1024;
        v.reserve(to);
        for(int i = from; i < to; ++i) {
            v.push_back(v.back() * mod_int<Mod, true>(i));
        }
    }
    return v[n];
}

template <int Mod = default_mod>
mod_int<Mod, true> comb(int n, int r) { // nCr
    if(r < 0 || r > n) return 0;
    return fact<Mod>(n) / fact<Mod>(r) / fact<Mod>(n - r);
}

using mint = mod_int<default_mod, true>; // default

struct rational {
    mint p, q; // p / q
};

rational operator+(rational const& r1, rational const& r2) {
    rational res;
    res.p = r1.p * r2.q + r2.p * r1.q;
    res.q = r1.q * r2.q;
    return res;
}

rational operator-(rational const& r1, rational const& r2) {
    rational res{mint(0)-r2.p, r2.q};
    return r1 + res;
}

rational operator*(rational const& r1, rational const& r2) {
    return rational{r1.p * r2.p, r1.q * r2.q};
}

rational operator/(rational const& r1, rational const& r2) {
    rational t{r2.q, r2.p};
    return r1 * t;
}

int main() {
    int m; cin >> m;

    vector<bool> is_prime(m + 1, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= m; ++i) {
        if(!is_prime[i]) continue;
        for(int j = i + i; j <= m; j += i) {
            is_prime[j] = false;
        }
    }

    rational ans{1, m};
    set<ll> pss;
    for(int i = 2; i <= m; ++i) {
        ll tmp = i;
        ll pcnt = 0, v = 1;
        for(ll x = 2; x * x <= tmp; ++x) {
            if(!is_prime[x] || i % x != 0) continue;
            pcnt += 1;
            (v *= x) %= default_mod;
            while(tmp % x == 0) tmp /= x;
        }
        if(tmp > 1) {
            pcnt += 1;
            (v *= tmp) %= default_mod;
        }
        if(pss.count(v)) continue;
        pss.insert(v);
        const int cnt = m / i;
        const rational t{mint(m - cnt), mint(m)};
        if(pcnt & 1) {
            ans = ans + (rational{1, 1} - t * t) / t;
        } else {
            ans = ans - (rational{1, 1} - t * t) / t;
        }
    }
    cout << ans.p / ans.q << endl;
}