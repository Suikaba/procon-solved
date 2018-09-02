
// http://codeforces.com/contest/557/problem/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e18;

int main() {
    int n; cin >> n;
    vector<vector<int>> ds(1 << 18);
    vector<int> l(n), d(n);
    for(int i = 0; i < n; ++i) {
        cin >> l[i];
    }
    ll sum = 0;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        sum += d[i];
    }
    for(int i = 0; i < n; ++i) {
        ds[l[i]].push_back(d[i]);
    }

    ll ans = inf;
    vector<int> cnt(256);
    for(int i = 1; i < (int)ds.size(); ++i) {
        if(ds[i].size() == 0u) continue;
        int can_use = ds[i].size() - 1;
        ll use_v = accumulate(begin(ds[i]), end(ds[i]), 0LL);
        for(int j = 255; j >= 0; --j) {
            int use = min(can_use, cnt[j]);
            use_v += j * use;
            can_use -= use;
        }
        ans = min(ans, sum - use_v);
        for(auto x : ds[i]) {
            cnt[x] += 1;
        }
    }

    cout << ans << endl;
}
