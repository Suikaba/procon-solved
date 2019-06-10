#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e18;

ll ten[13];

void init() {
    ten[0] = 1;
    for(int i = 1; i <= 12; ++i) {
        ten[i] = ten[i - 1] * 10;
    }
}

vector<ll> solve(ll cur) {
    if(cur == 0) return {inf};
    if(cur < 10) return {cur};
    auto s = to_string(cur);
    const int n = s.size();
    vector<ll> res = {inf};
    ll n1 = s[0] - '0', n2 = stoll(s.substr(1));
    for(int l = 1; l < n; ++l) {
        auto t = solve(abs(n1 - n2));
        if(res[0] > t[0]) {
            res = move(t);
        }
        if(res[0] == 1) break;
        n1 = n1 * 10 + (s[l] - '0');
        n2 -= ten[n - l - 1] * (s[l] - '0');
    }
    if(res[0] == inf) {
        res = {cur};
    } else {
        res.push_back(cur);
    }
    return res;
}

int main() {
    init();

    int T; cin >> T;
    while(T--) {
        ll n; cin >> n;
        auto ans = solve(n);
        reverse(begin(ans), end(ans));
        cout << ans.size() << " ";
        for(int i = 0; i < (int)ans.size(); ++i) {
            cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
        }
    }
}