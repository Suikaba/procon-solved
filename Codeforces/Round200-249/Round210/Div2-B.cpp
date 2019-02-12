#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; cin >> n >> k;

    if(k == n) {
        cout << -1 << endl;
        return 0;
    }

    if(k == n - 1) {
        for(int i = 0; i < n; ++i) {
            cout << i + 1 << " \n"[i + 1 == n];
        }
        return 0;
    }

    vector<int> ans(n, -1);
    for(int i = 1; i <= k; ++i) {
        ans[i] = i + 1;
    }
    ans[k + 1] = 1;
    for(int i = 0; i < n - k - 1; ++i) {
        const int idx = (i + k + 2) % n;
        ans[idx] = k + i + 2;
    }

    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
