#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/problemset/problem/286/E

const double pi = std::acos(-1.0);

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
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> a(n);
    vector<data_type> p(m + 1);
    unordered_set<int> s;
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        p[a[i]] = data_type(1, 0);
        s.insert(a[i]);
    }
    auto p2 = convolution(p, p);

    vector<int> ans;
    bool ok = true;
    for(int i = 0; i <= m; ++i) {
        const int c = real(p2[i]) + 0.1;
        if(c == 0) {
            if(s.count(i) == 1) ans.push_back(i);
            continue;
        }
        ok &= s.count(i);
    }
    if(ok) {
        printf("YES\n%d\n", (int)ans.size());
        for(int i = 0; i < (int)ans.size(); ++i) {
            if(i != 0) printf(" ");
            printf("%d", ans[i]);
        }
        printf("\n");
    } else {
        printf("NO\n");
    }
}
