#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(begin(a), end(a));

    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        const int j = n - i - 1;
        if(j < i) break;
        if(i == j) {
            ans += a[i] * a[i];
        } else {
            ans += (a[i] + a[j]) * (a[i] + a[j]);
        }
    }

    cout << ans << endl;
}
