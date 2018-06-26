#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0318

int main() {
    int n;
    cin >> n;
    set<int> s[3];
    for(int i = 0; i < 3; ++i) {
        int m; cin >> m;
        for(int j = 0; j < m; ++j) {
            int a; cin >> a;
            s[i].insert(a);
        }
    }

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        if((s[0].count(i + 1) == 0 || s[1].count(i + 1)) && s[2].count(i + 1)) {
            ans++;
        }
    }
    cout << ans << endl;
}
