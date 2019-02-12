#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, q; cin >> n >> q;
    vector<int> t(q), l(q), r(q), v(q);

    vector<int> added(n), ub(n, inf);
    for(int j = 0; j < q; ++j) {
        cin >> t[j] >> l[j] >> r[j] >> v[j];
        l[j]--;
        if(t[j] == 1) {
            for(int i = l[j]; i < r[j]; ++i) {
                added[i] += v[j];
            }
        } else {
            for(int i = l[j]; i < r[j]; ++i) {
                ub[i] = min(ub[i], v[j] - added[i]);
            }
        }
    }

    vector<int> ans = ub;
    for(int i = 0; i < q; ++i) {
        if(t[i] == 1) {
            for(int j = l[i]; j < r[i]; ++j) {
                ans[j] += v[i];
            }
        } else {
            int maxi = -inf;
            for(int j = l[i]; j < r[i]; ++j) {
                maxi = max(maxi, ans[j]);
            }
            if(maxi != v[i]) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }

    cout << "YES" << endl;
    for(int i = 0; i < n; ++i) {
        cout << ub[i] << " \n"[i + 1 == n];
    }
}
