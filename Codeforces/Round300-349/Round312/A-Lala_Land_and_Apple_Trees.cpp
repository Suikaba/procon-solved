
// http://codeforces.com/contest/558/problem/A

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n; cin >> n;
    vector<vector<pii>> a(2, vector<pii>(n));
    for(int i = 0; i < n; ++i) {
        int x, aa; cin >> x >> aa;
        a[x < 0].emplace_back(abs(x), aa);
    }
    sort(begin(a[0]), end(a[0]));
    sort(begin(a[1]), end(a[1]));

    int sz = min(a[0].size(), a[1].size()) + 1;
    int ans = 0;
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < min(sz, (int)a[i].size()); ++j) {
            ans += a[i][j].second;
        }
    }
    cout << ans << endl;
}
