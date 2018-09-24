
// http://codeforces.com/contest/553/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n, k; cin >> n >> k;
    vector<int> ans(n);
    iota(begin(ans), end(ans), 1);
    vector<ll> memo(n + 1, -1);
    function<ll(int)> calc = [&] (int len) {
        if(len == 0) return 1LL;
        if(memo[len] != -1) return memo[len];
        memo[len] = 0;
        for(int i = 1; i <= min(len, 2); ++i) {
            memo[len] += calc(len - i);
        }
        return memo[len];
    };

    int i = 0;
    while(i < n) {
        for(int j = i; j < n; ++j) {
            if(calc(n - j - 1) < k) {
                k -= calc(n - j - 1);
                continue;
            }
            reverse(begin(ans) + i, begin(ans) + j + 1);
            i = j + 1;
            break;
        }
    }

    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
