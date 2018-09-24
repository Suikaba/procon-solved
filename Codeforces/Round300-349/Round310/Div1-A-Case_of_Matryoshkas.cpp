
// http://codeforces.com/contest/555/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; cin >> n >> k;
    int ans = (n - 1) * 2 - (k - 1);
    for(int i = 0; i < k; ++i) {
        int m; cin >> m;
        vector<int> a(m);
        for(int i = 0; i < m; ++i) cin >> a[i];
        if(a[0] == 1) {
            for(int i = 0; i + 1 < m && a[i + 1] - a[i] == 1; ++i) {
                ans -= 2;
            }
        }
    }
    cout << ans << endl;
}
