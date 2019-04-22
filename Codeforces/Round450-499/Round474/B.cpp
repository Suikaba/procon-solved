#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(10);

    int n, U; cin >> n >> U;
    vector<int> E(n);
    for(int i = 0; i < n; ++i) {
        cin >> E[i];
    }

    double ans = -1;
    for(int i = 0; i + 1 < n; ++i) {
        int idx = upper_bound(begin(E), end(E), E[i] + U) - begin(E);
        idx -= 1;
        if(idx - i < 2) continue;
        ans = max(ans, double(E[idx] - E[i + 1]) / (E[idx] - E[i]));
    }

    if(ans < 0) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}