#include <bits/stdc++.h>
using namespace std;

// Sugoroku
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0642

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 2);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int ans = n + 1;
    for(int tans = 1; tans <= n; ++tans) {
        vector<bool> reach(n + 2);
        function<bool(int)> dfs = [&](int now) {
            reach[now] = true;
            if(now == n + 1) return true;
            bool res = false;
            for(int mv = 1; mv <= tans && now + mv <= n + 1; ++mv) {
                const int nxt = now + mv;
                if(reach[nxt] || a[nxt] == 1) continue;
                res |= dfs(nxt);
            }
            return res;
        };
        if(dfs(0)) {
            ans = tans;
            break;
        }
    }
    cout << ans << endl;
}
