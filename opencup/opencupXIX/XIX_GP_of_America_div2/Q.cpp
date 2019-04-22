#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, k, z;
    bool first = true;
    while(cin >> n >> k >> z, n != 0 || k != 0 || z != 0) {
        if(!first) {
            cout << "\n";
        }
        first = false;
        vector<int> x(n), y(n);
        for(int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }

        vector<int> dist;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                dist.push_back(abs(x[i] - x[j]) + abs(y[i] - y[j]));
            }
        }
        sort(dist.begin(), dist.end());

        while(k--) {
            int l, r; cin >> l >> r;
            cout << upper_bound(dist.begin(), dist.end(), r) - lower_bound(dist.begin(), dist.end(), l) << "\n";
        }
    }
}
