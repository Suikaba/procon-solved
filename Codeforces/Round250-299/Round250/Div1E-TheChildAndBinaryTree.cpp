#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 7 * 17 * (1 << 23) + 1; // == 998244353 !!

ll mod_inv(ll a, ll m) {
    ll b = mod, u = 1, v = 0;
    while(b > 0) {
        ll t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    return (u % m + m) % m;
}

class FMT {
public:
    FMT() {
        omega.resize(omega_max + 1);
        int x = primitive_root;
        for(int i = omega_max; i >= 0; --i) {
            omega[i] = x;
            x = (1LL * x * x) % mod;
        }
    }

    // assertion: v.size() == 2 ^ m
    std::vector<int> fft(std::vector<int> v, bool inv) const {
        const int n = v.size();
        int logn = 0;
        {
            int sz = 1;
            while(sz < n) sz *= 2, logn++;
        }
        assert(1 << logn == n);
        assert(omega_max >= logn);
        int ww = omega[logn];
        if(inv) ww = mod_inv(ww, mod);
        for(int m = n; m >= 2; m >>= 1) {
            const int mh = m >> 1;
            int w = 1;
            for(int i = 0; i < mh; ++i) {
                for(int j = i; j < n; j += m) {
                    const int k = j + mh;
                    int x = v[j] - v[k];
                    if(x < 0) x += mod;
                    v[j] += v[k];
                    if(v[j] >= mod) v[j] -= mod;
                    v[k] = (1LL * w * x) % mod;
                }
                w = (1LL * w * ww) % mod;
            }
            ww = (1LL * ww * ww) % mod;
        }

        int i = 0;
        for(int j = 1; j < n - 1; ++j) {
            for(int k = n >> 1; k > (i ^= k); k >>= 1);
            if(j < i) swap(v[i], v[j]);
        }
        if(inv) {
            const int inv_n = mod_inv(n, mod);
            for(auto& x : v) {
                x = (1LL * x * inv_n) % mod;
            }
        }
        return v;
    }
    std::vector<int> convolution(std::vector<int> f, std::vector<int> g) const {
        int sz = 1;
        const int m = f.size() + g.size() - 1;
        while(sz < m) sz *= 2;
        f.resize(sz), g.resize(sz);
        f = this->fft(std::move(f), false); g = this->fft(std::move(g), false);
        for(int i = 0; i < sz; ++i) {
            f[i] = (1LL * f[i] * g[i]) % mod;
        }

        return this->fft(std::move(f), true);
    }

private:
    static const int omega_max = 23;
    static const int primitive_root = 31;
    std::vector<int> omega;
};


void expand(vector<int>& f) {
    int sz = 1;
    while(sz < (int)f.size()) sz *= 2;
    f.resize(sz);
}

constexpr int inv2 = (mod + 1) / 2;

vector<int> poly_inv(vector<int> f) {
    const int n = f.size();
    assert((n ^ (n & -n)) == 0);
    FMT fmt;
    vector<int> r(1, mod_inv(f[0], mod));
    for(int k = 2; k <= n; k <<= 1) {
        vector<int> nr = fmt.convolution(fmt.convolution(r, r), vector<int>(begin(f), begin(f) + k));
        nr.resize(k);
        for(int i = 0; i < k / 2; ++i) {
            nr[i] = (2 * r[i] - nr[i] + mod) % mod;
            nr[i + k/2] = (mod - nr[i + k/2]) % mod;
        }
        r = move(nr);
    }
    return r;
}

vector<int> poly_sqrt(vector<int> f) {
    const int n = f.size();
    assert((n ^ (n & -n)) == 0);
    FMT fmt;
    vector<int> s(1, 1);
    for(int k = 2; k <= n; k <<= 1) {
        s.resize(k);
        vector<int> ns = fmt.convolution(poly_inv(s), vector<int>(begin(f), begin(f) + k));
        ns.resize(k);
        for(int i = 0; i < k; ++i) {
            s[i] = 1LL * (s[i] + ns[i]) * inv2 % mod;
        }
    }
    return s;
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> f(m + 1);
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        if(x > m) continue;
        f[x] = mod - 4;
    }
    f[0] = 1;
    expand(f);
    f = poly_sqrt(move(f));
    f[0] += 1;
    f = poly_inv(move(f));
    for(int i = 0; i <= m; ++i) {
        f[i] = (1LL * f[i] * 2) % mod;
    }
    for(int i = 1; i <= m; ++i) {
        cout << f[i] << endl;
    }
}
