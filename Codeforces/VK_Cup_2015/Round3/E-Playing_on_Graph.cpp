
// http://codeforces.com/contest/542/problem/E

// 反省点
// 割とスムーズに考察できた気がする．

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }

    vector<int> col(n, -1);
    bool ok = true;
    function<int(int, int)> dfs_and_bfs = [&] (int v, int c) {
        if(col[v] >= 0) {
            ok &= col[v] == c;
            return 0;
        }
        col[v] = c;
        int res = 0;
        for(auto to : g[v]) {
            res = max(res, dfs_and_bfs(to, !c));
        }

        queue<int> que;
        que.emplace(v);
        vector<int> dist(n, inf);
        dist[v] = 0;
        while(!que.empty()) {
            auto u = que.front();
            que.pop();
            for(auto to : g[u]) {
                if(dist[to] != inf) continue;
                dist[to] = dist[u] + 1;
                que.emplace(to);
            }
        }
        for(int i = 0; i < n; ++i) {
            if(dist[i] == inf) continue;
            res = max(res, dist[i]);
        }
        return res;
    };

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        if(col[i] != -1) continue;
        ans += dfs_and_bfs(i, 0);
    }

    if(ok) {
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }
}
