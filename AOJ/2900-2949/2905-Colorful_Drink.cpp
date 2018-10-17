// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2905

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    map<string, vector<int>> d;
    for(int i = 0; i < n; ++i) {
        string col; cin >> col;
        int den; cin >> den;
        d[col].push_back(den);
    }
    for(auto& p : d) sort(begin(p.second), end(p.second));

    int m; cin >> m;
    int cur_den = 0;
    bool ans = true;
    for(int i = 0; i < m; ++i) {
        string col; cin >> col;
        if(d.count(col) == 0) {
            ans = false;
            continue;
        }
        const int idx = upper_bound(begin(d[col]), end(d[col]), cur_den) - begin(d[col]);
        if(idx == (int)d[col].size()) {
            ans = false;
        } else {
            cur_den = d[col][idx];
        }
    }

    cout << (ans ? "Yes" : "No") << endl;
}
