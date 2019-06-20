
// 回転して同じものはとりあえず重複して数える。
// というのも、もし周期 s の並べ方があったとしたら、回転して同じとみなせるものは s 通りだとわかるからだ。
//
// まず、先頭を A に固定して、ループを考慮しない数え上げをする。
// 次に、ループを考慮して数え上げるが、これは先頭と末尾の A の個数を決め打ちして、間に B から始まって B で終わるものを考えればOK.
// これで先頭 A でループも考慮したものが得られて、先頭を B にしたものも同じなので 2 倍する。
//
// さっきので求まったテーブルを dp[i] とすると、周期が i で長さも i であるような列の総数 dp2[i] は
// 　dp2[i] = dp[i] - (i のすべての約数 j に対して dp2[j] の総和)
// となる。
//
// 求める答えは、n のすべての約数について dp2[i] / i の総和となる。
// 計算量は O(N^2)

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 1000003;

ll inv(ll n) {
    ll a = n, b = mod, u = 1, v = 0;
    while(b) {
        ll t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if(u < 0) u += mod;
    return u;
}

int main() {
    int n, k;
    while(cin >> n >> k, n) {
        if(n == 1) {
            cout << 2 << endl;
            continue;
        }
        ll ans = 0;
        if(k >= n) {
            ans += 2;
            k = n - 1;
        }

        vector<vector<vector<int>>> dp1(n + 1, vector<vector<int>>(k + 1, vector<int>(2)));
        dp1[1][1][0] = 1; // start with A
        for(int i = 1; i < n; ++i) {
            for(int j = 1; j <= k; ++j) {
                for(int pre = 0; pre < 2; ++pre) {
                    if(j + 1 <= k) {
                        (dp1[i + 1][j + 1][pre] += dp1[i][j][pre]) %= mod;
                    }
                    (dp1[i + 1][1][!pre] += dp1[i][j][pre]) %= mod;
                }
            }
        }

        vector<ll> dp2(n + 1), sum(n + 1);
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= k; ++j) {
                (dp2[i] += dp1[i][j][1]) %= mod; // ends with B
                (sum[i] += dp1[i][j][0]) %= mod;
            }
            for(int loop = 2; loop <= min(k, i); ++loop) {
                (dp2[i] += 1LL * sum[i - loop] * (loop - 1)) %= mod;
            }
            (dp2[i] += dp2[i]) %= mod; // consider starting with B
        }

        vector<int> dp3(n + 1);
        for(int i = 1; i <= n; ++i) {
            dp3[i] = dp2[i];
            for(int j = 1; j < i; ++j) {
                if(i % j == 0) {
                    (dp3[i] += mod - dp3[j]) %= mod;
                }
            }
        }
        for(int i = 1; i <= n; ++i) {
            if(n % i != 0) continue;
            (ans += dp3[i] * inv(i)) %= mod;
        }

        cout << ans << endl;
    }
}
