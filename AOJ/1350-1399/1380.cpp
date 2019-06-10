#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t; cin >> n >> t;
    vector<int> h(n);
    for(int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    vector<int> ans(n);
    ans[0] = t / h[0] + 1;
    int longest = h[0], st = 0;
    for(int i = 1; i < n; ++i) {
        st += h[i - 1];
        longest = max(longest, h[i]);
        const int tt = max(0, t - st);
        if(tt % longest >= h[i]) {
            ans[i] = min(ans[i - 1], tt / longest + 2);
        } else {
            ans[i] = min(ans[i - 1], tt / longest + 1);
        }
    }

    for(int i = 0; i < n; ++i) {
        cout << ans[i] << '\n';
    }
}
