// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2882

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, l, r;
    while(cin >> n >> l >> r, n) {
        vector<int> a(n);
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        int ans = 0;
        for(int i = l; i <= r; ++i) {
            int idx = -1;
            for(int j = 0; j < n; ++j) {
                if(i % a[j] == 0) {
                    idx = j;
                    break;
                }
            }
            if(idx == -1) {
                ans += n % 2 == 0;
            } else {
                ans += idx % 2 == 0;
            }
        }
        cout << ans << endl;
    }
}
