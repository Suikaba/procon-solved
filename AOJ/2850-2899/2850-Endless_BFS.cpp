// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2850

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }

    vector<vector<int>> d(n, vector<int>(2, inf));
    d[0][0] = 0;
    deque<tuple<int, int>> que;
    que.emplace_back(0, 0);
    while(!que.empty()) {
        int v, stable;
        tie(v, stable) = que.front(); que.pop_front();
        if(stable == 0) {
            for(auto to : g[v]) {
                if(d[to][0] == d[v][0]) { // change stable
                    d[v][1] = d[v][0];
                    que.emplace_back(v, 1);
                }
                if(d[to][0] == inf) {
                    d[to][0] = d[v][0] + 1;
                    que.emplace_back(to, 0);
                }
            }
        } else {
            for(auto to : g[v]) {
                if(d[to][1] != inf) continue;
                if((d[to][0] & 1) == (d[v][1] & 1)) {
                    d[to][1] = d[v][1];
                    que.emplace_front(to, 1);
                } else {
                    d[to][1] = d[v][1] + 1;
                    que.emplace_back(to, 1);
                }
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        ans = max(ans, d[i][1]);
    }

    cout << (ans == inf ? -1 : ans) << endl;
}
