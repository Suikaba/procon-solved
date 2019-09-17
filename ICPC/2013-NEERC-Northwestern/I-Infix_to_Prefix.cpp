#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll inf = 1e18;

// 0: max, 1: min
ll dp[1024][1024][2];

void init() {
    for(int i = 0; i < 1024; ++i) {
        for(int j = 0; j < 1024; ++j) {
            for(int k = 0; k < 2; ++k) {
                dp[i][j][k] = inf / 2;
            }
        }
    }
}

ll number(int l, int r, string const& s) {
    if(r - l >= 10 || r <= l) return inf;
    if(r - l != 1 && s[l] == '0') return inf;
    ll res = 0;
    bool check = true;
    for(int i = l; i < r; ++i) {
        check &= isdigit(s[i]);
        res *= 10;
        res += s[i] - '0';
    }
    if(!check) return inf;
    return res;
}

ll solve(int l, int r, string const& s, bool is_max) {
    if(dp[l][r][is_max] != inf / 2) return dp[l][r][is_max];
    ll& res = dp[l][r][is_max];
    res = (is_max ? -inf : inf);
    if(s[l] == '-') {
        if(ll num = solve(l + 1, r, s, !is_max); abs(num) != inf) {
            res = -num;
        }
        for(int i = l + 2; i < r; ++i) {
            const ll lval = solve(l + 1, i, s, is_max), rval = solve(i, r, s, !is_max);
            if(abs(lval) == inf || abs(rval) == inf) continue;
            if(is_max) res = max(res, lval - rval);
            else       res = min(res, lval - rval);
        }
    } else if(s[l] == '+') {
        for(int i = l + 2; i < r; ++i) {
            const ll lval = solve(l + 1, i, s, is_max), rval = solve(i, r, s, is_max);
            if(abs(lval) == inf || abs(rval) == inf) continue;
            if(is_max) res = max(res, lval + rval);
            else       res = min(res, lval + rval);
        }
    } else {
        res = number(l, r, s);
    }
    return res;
}

int main() {
    string s;
    while(cin >> s) {
        init();
        cout << solve(0, s.size(), s, false) << ' ' << solve(0, s.size(), s, true) << endl;
    }
}
