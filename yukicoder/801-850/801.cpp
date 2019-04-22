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

constexpr int default_mod = 1000000007;

using mint = mod_int<default_mod, true>; // default


int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> l(m), r(m);
    for(int i = 0; i < m; ++i) {
        cin >> l[i] >> r[i];
        l[i]--;
    }

    vector<mint> dp(n + 1);
    dp[0] = 1;
    for(int lp = 0; lp < k; ++lp) {
        vector<mint> sum(n + 1), ndp(n + 1);
        for(int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + dp[i];
        }
        for(int i = 0; i < m; ++i) {
            ndp[l[i]] += sum[r[i]] - sum[l[i]];
            ndp[r[i]] -= sum[r[i]] - sum[l[i]];
        }
        for(int i = 0; i < n; ++i) {
            ndp[i + 1] += ndp[i];
        }
        dp = move(ndp);
    }
    cout << dp[n - 1] << endl;
}