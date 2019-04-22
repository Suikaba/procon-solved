#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    while(q--) {
        int x; cin >> x;

        int lb = lower_bound(begin(a), end(a), x) - begin(a), ub = n;
        while(ub - lb > 1) {
            const int mid = (ub + lb) >> 1;
        }
    }
}
