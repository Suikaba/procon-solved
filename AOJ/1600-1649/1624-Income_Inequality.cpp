// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1624

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while(cin >> n, n) {
        vector<int> a(n);
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
            sum += a[i];
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            ans += a[i] * n <= sum;
        }
        cout << ans << endl;
    }
}
