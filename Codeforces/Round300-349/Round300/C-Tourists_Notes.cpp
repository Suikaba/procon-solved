
// http://codeforces.com/contest/538/problem/C

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> d(m), h(m);
    for(int i = 0; i < m; ++i) {
        cin >> d[i] >> h[i];
    }

    int ans = max(h[0] + d[0] - 1, h.back() + (n - d.back()));
    for(int i = 0; i + 1 < m; ++i) {
        if(abs(h[i] - h[i + 1]) > d[i + 1] - d[i]) {
            ans = -1;
            break;
        }
        ans = max(ans, (d[i + 1] - d[i] - abs(h[i] - h[i + 1])) / 2 + max(h[i], h[i + 1]));
    }

    if(ans == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << ans << endl;
    }
}
