#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        if(n == 0) {
            cout << 0 << "\n";
            continue;
        }
        vector<int> h(n);
        for(int i = 0; i < n; ++i) {
            cin >> h[i];
        }
        int ans = 1;
        int l = h[0];
        for(int i = 0; i < n; ++i) {
            if(h[i] - l > 20) {
                ans += 1;
                l = h[i];
            }
        }

        cout << ans << "\n";
    }
}
