#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        reverse(begin(a), end(a));
        ll maxi = 0, ans = 0;
        for(int i = 0; i < n; ++i) {
            ans += max(0LL, maxi - a[i]);
            maxi = max(a[i], maxi);
        }
        cout << ans << endl;
    }
}
