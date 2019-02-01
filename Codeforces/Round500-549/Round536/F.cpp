#include <bits/stdc++.h>

using ll = long long;

// 解法：
// 結局 f_k の累乗の形になる。指数部分は行列累乗で求まる。これを s とする。
// あとは x^s = m (mod p) を満たす x を求めよ、という問題になる。
// a^x = m (mod p) なら baby-step giant-step などのアルゴリズムで解ける。
// ここで、原始根という概念を導入すれば、うまく変換できる。
// p の原始根 g を用いれば、ある k があって x = g^k とかける（原始根の定義）。
// これを元の式に代入すると (g^k)^s = (g^s)^k = m (mod p) となる。
// 今 p に対して g と s が求まっているなら、これを a として baby-step giant-step で k が求まる。
// これで x = g^k が求まる。今回の p に対する原始根は 3 があるのでそれを使う（他の mod なら自分で探す必要がある）。
// 計算量は O(sqrt(n)log(n))

ll modpow(ll x, ll n, ll mod) {
    ll res = 1;
    while(n > 0) {
        if(n & 1) (res *= x) %= mod;
        (x *= x) %= mod;
        n >>= 1;
    }
    return res;
}

// Problem: find x s.t. a^x = b (mod p) (p is prime number)
// Output: x, but if not exists such x, -1
ll baby_step_giant_step(ll a, ll b, ll p) {
    ll res = -1;
    const ll m = std::sqrt(p) + 1; // ceil(sqrt(p))
    std::map<ll, ll> table;
    for(ll i = 0, z = 1, t = modpow(a, m, p); i < m; ++i) {
        table[z] = i;
        z = (z * t) % p;
    }

    ll z = b * modpow(a, p - m, p) % p;
    for(int i = m - 1; i >= 0; --i) {
        if(table.count(z) == 1) {
            res = m * table[z] + i;
            break;
        }
        z = (z * a) % p;
    }

    return res;
}

using namespace std;

using matrix = vector<vector<ll>>;

constexpr int mod = 998244353;

matrix operator*(matrix const& a, matrix const& b) {
    const int n = a.size();
    matrix res(n, vector<ll>(n));
    for(int k = 0; k < n; ++k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                (res[i][j] += a[i][k] * b[k][j]) %= (mod - 1);
            }
        }
    }
    return res;
}

matrix matpow(matrix x, ll n) {
    matrix res(x.size(), vector<ll>(x.size()));
    for(int i = 0; i < (int)x.size(); ++i) {
        res[i][i] = 1;
    }
    while(n > 0) {
        if(n & 1) res = res * x;
        x = x * x;
        n >>= 1;
    }
    return res;
}

int main() {
    int k; cin >> k;
    vector<ll> b(k);
    for(int i = 0; i < k; ++i) {
        cin >> b[i];
    }
    ll n, m; cin >> n >> m;

    matrix A;
    A.push_back(b);
    for(int i = 0; i < k - 1; ++i) {
        vector<ll> a(k);
        a[i] = 1;
        A.push_back(a);
    }
    const ll s = matpow(A, n - k)[0][0];
    const ll x = modpow(3, s, mod);
    const ll z = baby_step_giant_step(x, m, mod);
    if(z < 0) {
        cout << -1 << endl;
    } else {
        cout << modpow(3, z, mod) << endl;
    }
}
