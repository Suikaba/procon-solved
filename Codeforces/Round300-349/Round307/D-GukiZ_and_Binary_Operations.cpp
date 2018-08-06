
// http://codeforces.com/contest/551/problem/D

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using matrix = vector<vector<ull>>;

matrix mul(matrix const& a, matrix const& b, const ull mod) {
    const int n = a.size();
    const int m = b[0].size();
    assert((int)a[0].size() == n && (int)b.size() == n);
    matrix res(n, vector<ull>(m));
    for(int i = 0; i < n; ++i) {
        for(int k = 0; k < n; ++k) {
            for(int j = 0; j < m; ++j) {
                (res[i][j] += a[i][k] * b[k][j]) %= mod;
            }
        }
    }
    return res;
}

matrix matpow(matrix A, ull n, const ull mod) {
    const int m = A.size();
    matrix res(m, vector<ull>(m));
    for(int i = 0; i < m; ++i) res[i][i] = 1;
    while(n > 0) {
        if(n & 1) res = mul(move(res), A, mod);
        A = mul(A, A, mod);
        n >>= 1;
    }
    return res;
}

ull modpow(ull x, ull n, const ull mod) {
    ull res = 1;
    x %= mod;
    while(n > 0) {
        if(n & 1) (res *= x) %= mod;
        (x *= x) %= mod;
        n >>= 1;
    }
    return res;
}

int main() {
    ull n, k, l, m;
    cin >> n >> k >> l >> m;
    if(l < 64 && k >= (1ULL << l)) {
        cout << 0 << endl;
        return 0;
    }

    matrix A(2, vector<ull>(2)), b(2, vector<ull>(1));
    A[0][0] = 1, A[0][1] = 1;
    A[1][0] = 1;
    b[0][0] = 1;
    A = matpow(A, n, m);
    auto y = mul(A, b, m);
    const int cnt2 = __builtin_popcountll(k), cnt1 = l - cnt2;
    const ull v1 = (y[0][0] + y[1][0]) % m;
    const ull v2 = (modpow(2, n, m) - v1 + m) % m;
    cout << (modpow(v1, cnt1, m) * modpow(v2, cnt2, m) % m) << endl;
}
