// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2847

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n * n);
    for(int i = 0; i < 2 * n * n - 2 * n; ++i) {
        int a, b; cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }

    vector<bool> used(n * n);
    vector<vector<int>> ans(n, vector<int>(n, -1));
    for(int i = 0; i < n * n; ++i) { // r1
        if(g[i].size() == 2u) {
            int cur = i;
            ans[0][0] = cur;
            used[cur] = true;
            for(int j = 0; j < n - 1; ++j) {
                int nxt = -1;
                for(auto to : g[cur]) {
                    if(used[to] || (nxt != -1 && g[nxt].size() < g[to].size())) continue;
                    nxt = to;
                }
                cur = ans[0][j + 1] = nxt;
                used[nxt] = true;
            }
            break;
        }
    }
    for(int i = 0; i < n - 1; ++i) {
        for(int j = 0; j < n; ++j) {
            for(auto to : g[ans[i][j]]) {
                if(used[to]) continue;
                ans[i + 1][j] = to;
                used[to] = true;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << ans[i][j] + 1 << " \n"[j + 1 == n];
        }
    }
}
