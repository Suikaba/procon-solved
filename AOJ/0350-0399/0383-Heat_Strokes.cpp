// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0383

#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, x;
    cin >> a >> b >> x;
    int ans = 1e9;
    for(int i = 0; i <= (x + 499) / 500; ++i) {
        const int r = max(0, x - i * 500);
        ans = min(ans, i * b + (r + 999) / 1000 * a);
    }
    cout << ans << endl;
}
