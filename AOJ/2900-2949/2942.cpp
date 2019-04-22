#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, m; cin >> n >> m;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<ll> plus, minus;
    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        if(a[i] < i) {
            plus.push_back(i);
            minus.push_back(a[i]);
        } else {
            plus.push_back(a[i]);
            minus.push_back(i);
        }
        ans += abs(a[i] - i);
    }
    sort(begin(plus), end(plus));
    sort(rbegin(minus), rend(minus));

    for(int i = 0; i < m; ++i) {
        if(plus[i] > minus[i]) break;
        ans += 2 * (minus[i] - plus[i]);
    }

    cout << ans << endl;
}