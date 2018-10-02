// http://codeforces.com/contest/1041/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(begin(a), end(a));
    int ans = 0;
    for(int i = 0; i + 1 < n; ++i) {
        ans += a[i + 1] - a[i] - 1;
    }
    cout << ans << endl;
}
