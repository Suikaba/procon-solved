#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll l[1 << 23], r[1 << 23];

int main() {
    int n, d; cin >> n >> d;
    for(int a = 1; a <= n; ++a) {
        for(int b = 1; b <= n; ++b) {
            l[a * a + b * b] += 1;
            if(a * a - b * b + d >= 0) {
                r[a * a - b * b + d] += 1;
            }
        }
    }

    ll ans = 0;
    for(int i = 0; i < 1 << 23; ++i) {
        ans += l[i] * r[i];
    }
    
    cout << ans << endl;
}