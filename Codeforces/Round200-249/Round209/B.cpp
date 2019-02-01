#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; cin >> n >> k;

    vector<int> ans(2 * n);
    for(int i = 0; i < k; ++i) {
        ans[2 * i] = 2 * i + 1;
        ans[2 * i + 1] = 2 * i + 2;
    }
    for(int i = k; i < n; ++i) {
        ans[2 * i] = 2 * i + 2;
        ans[2 * i + 1] = 2 * i + 1;
    }

    for(int i = 0; i < 2 * n; ++i) {
        cout << ans[i] << " \n"[i + 1 == 2 * n];
    }
}
