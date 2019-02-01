#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x, y; cin >> n >> x >> y;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(begin(a), end(a));

    if(x > y) {
        cout << n << endl;
        return 0;
    }

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        if(i % 2 == 0 && a[i] <= x) {
            ans += 1;
        }
    }

    cout << ans << endl;
}
