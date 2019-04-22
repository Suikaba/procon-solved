#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int q; cin >> q;
    while(q--) {
        ll n, a, b; cin >> n >> a >> b;
        ll ans = 0;
        if(2 * a <= b) {
            ans = a * n;
        } else {
            ans = n / 2 * b + (n & 1) * a;
        }
        cout << ans << endl;
    }
}
