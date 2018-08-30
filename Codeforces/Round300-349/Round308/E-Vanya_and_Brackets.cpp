
// http://codeforces.com/contest/552/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> parse(string const& s, int p, int ub) {
    vector<ll> res;
    bool multi_f = false;
    while(ub != p) {
        if(isdigit(s[p])) {
            if(multi_f) {
                ll v = res.back();
                res.pop_back();
                res.push_back(v * (s[p] - '0'));
            } else {
                res.push_back(s[p] - '0');
            }
            multi_f = false;
        } else {
            multi_f = s[p] == '*';
        }
        p += 1;
    }
    return res;
}

ll sum(vector<ll> const& v, int offset_f = 0, int offset_b = 0) {
    return accumulate(begin(v) + offset_f, end(v) - offset_b, 0LL);
}

int main() {
    string s; cin >> s;
    const int n = s.size();
    vector<int> midx;
    for(int i = 0; i < n; ++i) {
        if(s[i] == '*') midx.push_back(i);
    }
    const int m = midx.size();

    ll ans = sum(parse(s, 0, n));
    for(int i = 0; i < m; ++i) {
        {
            auto front_v = parse(s, 0, midx[i]);
            auto back_v = parse(s, midx[i] + 1, n);
            ans = max({ans, sum(front_v) * back_v[0] + sum(back_v, 1, 0), sum(front_v, 0, 1) + front_v.back() * sum(back_v)});
        }

        for(int j = i + 1; j < m; ++j) {
            auto front_v = parse(s, 0, midx[i]);
            auto mid_val = sum(parse(s, midx[i] + 1, midx[j]));
            auto back_v = parse(s, midx[j] + 1, n);
            ans = max(ans, front_v.back() * mid_val * back_v[0] + sum(front_v, 0, 1) + sum(back_v, 1, 0));
        }
    }

    cout << ans << endl;
}
