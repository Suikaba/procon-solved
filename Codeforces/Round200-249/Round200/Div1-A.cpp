#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll a, b; cin >> a >> b;
    ll ans = 0;
    while(true) {
        if(a == 1 || b == 1) {
            ans += max(a, b);
            break;
        }
        if(a > b) {
            ans += a / b;
            a %= b;
        } else {
            ans += b / a;
            b %= a;
        }
    }

    cout << ans << endl;
}
