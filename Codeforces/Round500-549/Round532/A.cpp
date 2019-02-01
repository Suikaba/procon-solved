#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    int ans = -inf;
    for(int b = 1; b <= n; ++b) {
        vector<bool> use(n, true);
        for(int i = -n; i <= n; ++i) {
            if(0 <= b + i * k - 1 && b + i * k - 1 < n) {
                use[b + i * k - 1] = false;
            }
        }
        int tans = 0;
        for(int i = 0; i < n; ++i) {
            if(use[i]) {
                tans += v[i];
            }
        }
        ans = max(ans, abs(tans));
    }

    cout << ans << endl;
}
