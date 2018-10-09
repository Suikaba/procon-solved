// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1616&lang=jp

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while(cin >> n >> m, n) {
        vector<int> a(n);
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        int ans = -1;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                if(a[i] + a[j] <= m) {
                    ans = max(ans, a[i] + a[j]);
                }
            }
        }
        if(ans == -1) cout << "NONE" << endl;
        else          cout << ans << endl;
    }
}
