#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    const int ans = max(*min_element(begin(a), end(a)) * 2, *max_element(begin(a), end(a)));
    for(int i = 0; i < m; ++i) {
        if(b[i] <= ans) {
            cout << "-1" << endl;
            return 0;
        }
    }
    cout << ans << endl;
}
