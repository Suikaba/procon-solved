#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int k; cin >> k;
    if(k == 1) {
        cout << 0 << endl;
    } else {
        ll ans = 1;
        for(int i = 0; i < k; ++i) ans *= -2;
        cout << ans << endl;
    }
}