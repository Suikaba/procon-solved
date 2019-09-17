#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        sort(begin(v), end(v));
        int ans = 0;
        int a1 = v[0], a2 = v[0];
        for(int i = 1; i < n; ++i) {
            ans = max(ans, v[i] - (i & 1 ? a1 : a2));
            (i & 1 ? a1 : a2) = v[i];
        }
        cout << ans << endl;
    }
}
