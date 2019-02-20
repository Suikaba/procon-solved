#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(4), b(4), c(4), d(4);
    for(int i = 0; i < 4; ++i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    for(int i = 0; i < 4; ++i) {
        if(a[i] + c[i] <= n || a[i] + d[i] <= n) {
            cout << i + 1 << ' ' << a[i] << ' ' << n - a[i] << endl;
            return 0;
        }
        if(b[i] + c[i] <= n || b[i] + d[i] <= n) {
            cout << i + 1 << ' ' << b[i] << ' ' << n - b[i] << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
