
// http://codeforces.com/contest/551/problem/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    auto check = [&](ll X) {
        vector<ll> v(m, X);
        int idx = 0;
        for(int i = 0; i < n; ++i) {
            ll now = a[i];
            while(idx < m && now > 0) {
                ll use = min(now, v[idx] - (i + 1));
                now -= use;
                v[idx] -= use;
                if(v[idx] == (i + 1)) idx++;
            }
            if(now > 0) return false;
        }
        return true;
    };
    ll lb = 0, ub = 1e18;
    while(ub - lb > 1) {
        const auto mid = (lb + ub) / 2;
        (check(mid) ? ub : lb) = mid;
    }
    cout << ub << endl;
}

