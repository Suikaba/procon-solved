#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    const int sz1 = n / 2, sz2 = n - sz1;
    vector<int> v1;
    for(int S = 0; S < (1 << sz1); ++S) {
        int cur = 0;
        for(int i = 0; i < sz1; ++i) {
            if(S & (1 << i)) (cur += a[i]) %= m;
        }
        v1.push_back(cur);
    }
    sort(begin(v1), end(v1));
    v1.erase(unique(begin(v1), end(v1)), end(v1));
    int ans = *max_element(begin(v1), end(v1));
    for(int S = 0; S < (1 << sz2); ++S) {
        int cur = 0;
        for(int i = 0; i < sz2; ++i) {
            if(S & (1 << i)) (cur += a[i + sz1]) %= m;
        }
        const int idx = lower_bound(begin(v1), end(v1), m - cur) - begin(v1) - 1;
        ans = max(ans, cur);
        if(idx < 0) continue;
        ans = max(ans, cur + v1[idx]);
    }

    cout << ans << endl;
}
