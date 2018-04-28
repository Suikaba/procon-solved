#include <bits/stdc++.h>
using namespace std;

constexpr double pi = std::acos(-1.0);

using data_type = std::complex<double>;

std::vector<data_type> fft(std::vector<data_type> v, bool inv = false) {
    int const n = v.size();
    double theta = 2 * pi / n * (inv ? -1 : 1);
    for(int m = n; m >= 2; m >>= 1) {
        int mh = m >> 1;
        data_type theta_i(0, theta);
        for(int i = 0; i < mh; ++i) {
            data_type w = std::exp((data_type)i * theta_i);
            for(int j = i; j < n; j += m) {
                data_type x = v[j] - v[j + mh]; // (a_k - a_{k + N/2})
                v[j] = v[j] + v[j + mh];   // (a_k + a_{k + N/2})
                v[j + mh] = w * x;         // (a_k - a_{k + N/2}) * W_N^j
            }
        }
        theta *= 2;
    }
    int i = 0;
    for(int j = 1; j < n - 1; ++j) {
        for(int k = n >> 1; k > (i ^= k); k >>= 1);
        if(j < i) {
            swap(v[i], v[j]);
        }
    }
    if(inv) {
        for(auto& x : v) x /= n;
    }
    return v;
}

std::vector<data_type> convolution(std::vector<data_type> x, std::vector<data_type> y) {
    int sz = 1;
    int t = x.size() + y.size() - 1;
    while(sz < t) {
        sz <<= 1;
    }
    x.resize(sz); y.resize(sz);
    x = fft(std::move(x)); y = fft(std::move(y));
    for(int i = 0; i < sz; ++i) {
        x[i] *= y[i];
    }
    x = fft(std::move(x), true);
    return x;
}

int main() {
    int n, m, k;
    string s, t;
    cin >> n >> m >> k >> s >> t;

    reverse(begin(t), end(t));

    auto calc = [&](char target) {
        vector<data_type> a(n), b(m);
        for(int i = 0; i < n; ++i) {
            if(s[i] == target) {
                a[i] = data_type(1, 0);
                for(int j = i - 1; j >= i - k && j >= 0; --j) {
                    if(real(a[j]) > 0) break;
                    a[j] = data_type(1, 0);
                }
                for(int j = i + 1; j < n && j <= i + k; ++j) {
                    if(real(a[j]) > 0 || s[j] == target) break;
                    a[j] = data_type(1, 0);
                }
            }
        }
        for(int i = 0; i < m; ++i) {
            b[i] = data_type(t[i] == target, 0);
        }

        a = convolution(move(a), move(b));
        vector<int> res(n);
        for(int i = 0; i < n; ++i) {
            res[i] = (int)(real(a[i]) + 0.1);
        }
        return res;
    };

    auto A = calc('A'), C = calc('C'), T = calc('T'), G = calc('G');

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        ans += A[i] + C[i] + T[i] + G[i] == m;
    }

    cout << ans << endl;
}
