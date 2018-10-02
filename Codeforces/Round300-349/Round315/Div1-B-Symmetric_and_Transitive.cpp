// http://codeforces.com/contest/568/problem/B

// 条件を満たすのは、
// いくつかのクリーク（自己辺を含む）+ 自己辺を含まない1頂点のみからなるグラフの集合
// である。
// クリークに含まれる頂点数を m とすると、m の選び方で nCm 通り、クリークへの分け方で S(n, 1) + ... + S(n, n) (stirling) 通り
// これを m = 1, ..., n - 1 まで足し合わせれば答えになる

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 1e9 + 7;

int main() {
    int n; cin >> n;
    vector<vector<ll>> nCr(n + 1, vector<ll>(n + 1));
    vector<vector<ll>> stir(n + 1, vector<ll>(n + 1));
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= i; ++j) {
            if(j == 0 || i == j) nCr[i][j] = 1;
            else                 nCr[i][j] = (nCr[i - 1][j] + nCr[i - 1][j - 1]) % mod;
        }
    }
    for(int i = 1; i <= n; ++i) {
        stir[i][1] = stir[i][i] = 1;
        for(int j = 2; j < n; ++j) {
            stir[i][j] = (stir[i - 1][j - 1] + j * stir[i - 1][j]) % mod;
        }
    }

    vector<ll> stir_sum(n + 1);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            (stir_sum[i] += stir[i][j]) %= mod;
        }
    }

    ll ans = 1;
    for(int i = 1; i < n; ++i) {
        (ans += nCr[n][i] * stir_sum[n - i]) %= mod;
    }

    cout << ans << endl;
}
