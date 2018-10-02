// http://codeforces.com/contest/580/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int pre = -1, ans = 0, cur = 0;
    for(int i = 0; i < n; ++i) {
        if(pre <= a[i]) {
            cur++;
        } else {
            pre = a[i];
            ans = max(ans, cur);
            cur = 1;
        }
        pre = a[i];
    }
    ans = max(ans, cur);

    cout << ans << endl;
}
