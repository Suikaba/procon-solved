
// http://codeforces.com/contest/1015/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> l(n), r(n);
    for(int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
    }
    vector<int> ans;
    for(int i = 1; i <= m; ++i) {
        bool f = false;
        for(int j = 0; j < n; ++j) {
            f |= (l[j] <= i && i <= r[j]);
        }
        if(!f) ans.push_back(i);
    }

    cout << ans.size() << endl;
    for(auto x : ans) {
        cout << x << endl;
    }
}
