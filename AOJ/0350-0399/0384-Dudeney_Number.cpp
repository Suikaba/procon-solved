// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0384

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll a, n, m; cin >> a >> n >> m;
    int ans = 0;
    for(ll y = 1; ; ++y) {
        ll val = 1;
        for(int i = 0; val < m && i < n; ++i) val *= (y + a);
        if(val > m) break;
        int y2 = 0;
        while(val > 0) {
            y2 += val % 10;
            val /= 10;
        }
        ans += y == y2;
    }
    cout << ans << endl;
}
