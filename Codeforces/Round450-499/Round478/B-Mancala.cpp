#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    vector<ll> a(14);
    for(int i = 0; i < 14; ++i) {
        cin >> a[i];
    }

    ll ans = 0;
    for(int i = 0; i < 14; ++i) {
        if(a[i] == 0) continue;
        auto b = a;
        ll x = a[i] / 14;
        ll y = a[i] % 14;
        b[i] = 0;
        for(int j = 0; j < 14; ++j) {
            b[j] += x;
        }
        for(int j = 1; j <= y; ++j) {
            int idx = (i + j) % 14;
            b[idx] += 1;
        }
        ll tans = 0;
        for(int j = 0; j < 14; ++j) {
            if(b[j] % 2 == 0) {
                tans += b[j];
            }
        }
        ans = max(ans, tans);
    }

    cout << ans << endl;
}
