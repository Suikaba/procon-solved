#include <bits/stdc++.h>
using namespace std;

int main() {
    const int max_a = 1 << 20;
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, k; cin >> n >> k;
    vector<int> r(n);
    for(int i = 0; i < n; ++i) {
        cin >> r[i];
    }
    sort(begin(r), end(r));
    r.erase(unique(begin(r), end(r)), end(r));
    n = r.size();
    vector<int> l(n);
    for(int i = 0; i < n; ++i) {
        l[i] = max(1, r[i] - k);
    }

    vector<int> min_v(max_a, -1), max_v(max_a, -1);
    for(int i = 1; i < max_a; ++i) {
        const int idx1 = lower_bound(begin(r), end(r), i) - begin(r);
        if(idx1 != n && l[idx1] <= i) {
            min_v[i] = idx1;
        }
        if(min_v[i] == -1) continue;
        const int idx2 = upper_bound(begin(l), end(l), i) - begin(l) - 1;
        if(idx2 >= 0) {
            max_v[i] = idx2;
        }
    }

    int ans = 1;
    for(int x = 2; x < max_a; ++x) {
        int cur = -1;
        for(int i = x; i < max_a; i += x) {
            if(min_v[i] == -1) continue;
            if(cur + 1 < min_v[i]) {
                cur = -1;
                break;
            }
            cur = max(cur, max_v[i]);
        }
        if(cur == n - 1) ans = x;
    }

    cout << ans << endl;
}
