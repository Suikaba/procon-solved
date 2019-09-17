#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; ++i) cin >> p[i];

    int ans = 100;
    for(int i = 1; i <= 100; ++i) {
        bool ok = true;
        for(int j = 0; j < n; ++j) {
            bool check = false;
            for(int k = 0; k <= i; ++k) {
                int m = 100 * k;
                check |= m / i + (m % i >= (i + 1) / 2) == p[j];
            }
            ok &= check;
        }
        if(ok) {
            ans = i;
            break;
        }
    }

    cout << ans << endl;
}
