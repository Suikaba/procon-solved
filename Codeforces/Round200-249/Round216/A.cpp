#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        if(a[i] == 1) {
            ans += m == 0;
            m = max(0, m - 1);
        } else {
            if(k == 0) {
                ans += m == 0;
                m = max(0, m - 1);
            } else {
                k = max(k - 1, 0);
            }
        }
    }

    cout << ans << endl;
}
