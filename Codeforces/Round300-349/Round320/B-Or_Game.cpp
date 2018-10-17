#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, k, x; cin >> n >> k >> x;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<ll> left(n), right(n);
    for(int i = 1; i < n; ++i) {
        left[i] = left[i - 1] | a[i - 1];
    }
    for(int i = n - 2; i >= 0; --i) {
        right[i] = right[i + 1] | a[i + 1];
    }

    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        ll b = a[i];
        for(int j = 0; j < k; ++j) {
            b *= x;
        }
        ans = max(ans, b | left[i] | right[i]);
    }

    cout << ans << endl;
}
