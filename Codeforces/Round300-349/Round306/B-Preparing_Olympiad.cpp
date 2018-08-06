#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, l, r, x;
    cin >> n >> l >> r >> x;
    vector<int> c(n);
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    int ans = 0;
    for(int S = 0; S < (1 << n); ++S) {
        if(__builtin_popcount(S) < 2) continue;
        int mini = 1e6, maxi = -1, sum = 0;
        for(int i = 0; i < n; ++i) {
            if(S & (1 << i)) {
                mini = min(mini, c[i]);
                maxi = max(maxi, c[i]);
                sum += c[i];
            }
        }
        ans += l <= sum && sum <= r && maxi - mini >= x;
    }

    cout << ans << endl;
}
