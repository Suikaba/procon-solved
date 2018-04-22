#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0340

int main() {
    constexpr int inf = 1e9;

    int n;
    cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    int ans = inf;
    for(int l = 0; l <= p[0]; ++l) {
        for(int r = 0; r <= p[n - 1]; ++r) {
            int tans = l + r;
            auto tp = p;
            tp[0] -= l;
            tp[n - 1] -= r;
            for(int i = 0; i < n; ++i) {
                int x = max(tp[i], 0);
                tans += x * 2;
                tp[i] -= x;
                if(i + 1 < n) tp[i + 1] -= x;
            }
            ans = min(ans, tans);
        }
    }
    cout << ans << endl;
}
