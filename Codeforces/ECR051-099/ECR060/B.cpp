#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n, m, k; cin >> n >> m >> k;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(begin(a), end(a));

    ll ans = (a.back() * k + a[n - 2]) * (m / (k + 1));
    m %= (k + 1);
    ans += a.back() * m;

    cout << ans << endl;
}
