#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 1e9 + 7;
constexpr int inv2 = mod / 2 + 1;

ll calc(ll fst) {
    fst %= mod;
    return fst * (fst + 1) % mod * inv2 % mod;
}

ll memo[100];

ll solve(ll n) {
    if(n <= 7) return 0;
    n -= 7;
    ll ans = 0, prev = 0, fst = 6;
    int itr = 0;
    while(n > 0) {
        prev = ans;
        if(n >= (fst + 1) * 6) {
            if(memo[itr] == -1) {
                memo[itr] = calc(fst) * 21 % mod; // calc(6)
                (memo[itr] += prev * 27) %= mod; // 2 + ... + 7
            }
            //cout << "hoge" << endl;
            ans += memo[itr];
            if(ans >= mod) ans -= mod;
            n -= (fst + 1) * 6;
        } else {
            ll level = 1;
            while(level <= 6 && n >= fst + 1) {
                (ans += calc(fst) * level + prev * (level + 1)) %= mod;
                n -= fst + 1;
                level += 1;
            }
            if(level <= 6) {
                (ans += level * (mod + calc(fst) - calc(fst - n)) + (level + 1) * solve(n)) %= mod;
                return ans;
            }
        }
        fst = 7 * fst + 6;
        itr += 1;
    }
    return ans;
}

int main() {
    memset(memo, -1, sizeof(memo));
    ios_base::sync_with_stdio(false); cin.tie(0);
    // experiment:
    //vector<vector<int>> pascal(201, vector<int>(201));
    //pascal[0][0] = 1;
    //for(int i = 1; i <= 200; ++i) {
    //    for(int j = 0; j <= i; ++j) {
    //        if(j == 0 || j == i) {
    //            pascal[i][j] = 1;
    //        } else {
    //            pascal[i][j] = (pascal[i - 1][j] + pascal[i - 1][j - 1]) % 7;
    //        }
    //    }
    //}
    //for(int i = 0; i <= 200; ++i) {
    //    for(int j = 0; j <= i; ++j) {
    //        cout << pascal[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        ll n; cin >> n;
        n += 1; // 1-indexed
        cout << "Case " << t << ": " << solve(n) << '\n';
    }
}
