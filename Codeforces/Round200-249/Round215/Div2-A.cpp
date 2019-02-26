#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, d; cin >> n >> d;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int m; cin >> m;
    sort(begin(a), end(a));

    cout << accumulate(begin(a), begin(a) + min(m, n), 0) - d * max(0, m - n) << endl;
}
