#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n, k; cin >> n >> k;
    vector<int> b(n), g(n);
    int cb = 0, cg = 0;
    set<pii> s;
    for(int i = 0; i < n; ++i) {
        if(cb == 0) cg += 1;
        b[i] = cb + 1;
        g[i] = cg + 1;
        s.emplace(b[i], g[i]);
        cb = (cb + 1) % k;
        cg = (cg + 1) % k;
    }

    bool ok = (int)s.size() == n;
    for(int i = 0; i < n; ++i) {
        ok &= b[i] != g[i];
        if(i != 0) {
            ok &= b[i] != b[i - 1] && g[i] != g[i - 1];
            ok &= b[i] <= k && g[i] <= k;
        }
    }

    if(ok) {
        cout << "YES" << endl;
        for(int i = 0; i < n; ++i) {
            cout << b[i] << ' ' << g[i] << endl;
        }
    } else {
        cout << "NO" << endl;
    }
}
