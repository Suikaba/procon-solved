#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 998244353;

int mod_inv(ll a, ll m) {
    ll b = m, u = 1, v = 0;
    while(b > 0) {
        ll t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    return (u % m + m) % m;
}

class FMT {
    static const int root = 31;
    static int omega(int idx) {
        static const int omega_max = 23;
        static vector<int> ws;
        if(ws.empty()) {
            ws.resize(omega_max + 1);
            for(int x = root, i = omega_max; i >= 0; --i) {
                ws[i] = x;
                x = (1LL * x * x) % mod;
            }
        }
        return ws[idx];
    }

public:
    static vector<int> fft(vector<int> v, bool inv) {
        const int n = v.size();
        assert((n ^ (n & -n)) == 0);
        int ww = [&] () {
            int logn = 0, sz = 1;
            while(sz < n) sz *= 2, logn++;
            return omega(logn);
        }();
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
        for(int i = 0, j = 1; j < n - 1; ++j) {
            for(int k = n >> 1; k > (i ^= k); k >>= 1);
            if(j < i) swap(v[i], v[j]);
        }
        if(inv) {
            const int inv_n = mod_inv(n, mod);
            for(int j = 0; j < (int)v.size(); ++j) {
                v[j] = (1LL * v[j] * inv_n) % mod;
            }
        }
        return v;
    }
    static vector<int> convolution(vector<int> f, vector<int> g) {
        int sz = 1;
        const int m = f.size() + g.size() - 1;
        while(sz < m) sz *= 2;
        f.resize(sz), g.resize(sz);
        f = fft(move(f), false); g = fft(move(g), false);
        for(int i = 0; i < sz; ++i) {
            f[i] = (1LL * f[i] * g[i]) % mod;
        }
        return fft(move(f), true);
    }
};

int main() {
    int n, m;
    while(cin >> n >> m) {
        string s1, s2; cin >> s1 >> s2;
        reverse(begin(s1), end(s1));
        vector<int> R1(n), P1(n), S1(n);
        vector<int> R2(m), P2(m), S2(m);
        for(int i = 0; i < n; ++i) {
            R1[i] = s1[i] == 'R';
            P1[i] = s1[i] == 'P';
            S1[i] = s1[i] == 'S';
        }
        for(int i = 0; i < m; ++i) {
            R2[i] = s2[i] == 'R';
            P2[i] = s2[i] == 'P';
            S2[i] = s2[i] == 'S';
        }
        auto w1 = FMT::convolution(R1, P2), w2 = FMT::convolution(P1, S2), w3 = FMT::convolution(S1, R2);
        int ans = 0;
        for(int i = n - 1; i >= 0; --i) {
            //cout << w1[i] << ' ' << w2[i] << ' ' << w3[i] << endl;
            ans = max(ans, w1[i] + w2[i] + w3[i]);
        }
        cout << ans << endl;
    }
}
