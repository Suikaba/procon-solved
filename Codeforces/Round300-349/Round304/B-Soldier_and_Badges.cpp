
// http://codeforces.com/contest/546/problem/B

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(begin(a), end(a));
    int ans = 0;
    for(int i = 1; i < n; ++i) {
        if(a[i] <= a[i - 1]) {
            ans += (a[i - 1] - a[i] + 1);
            a[i] += (a[i - 1] - a[i] + 1);
        }
    }
    cout << ans << endl;
}
