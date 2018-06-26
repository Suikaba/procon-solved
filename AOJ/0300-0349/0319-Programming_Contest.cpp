#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0319

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int ans = 0;
    for(int i = 1; i <= 100; ++i) {
        int cnt = 0;
        for(int j = 0; j < n; ++j) {
            cnt += a[j] >= i;
        }
        if(cnt >= i) ans = i;
    }
    cout << ans << endl;
}
