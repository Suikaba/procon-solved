#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<vector<int>> g(n);
        for(int i = 0; i < n; ++i) {
            int p; cin >> p;
            g[i].push_back(p - 1);
            g[p - 1].push_back(i);
        }

        vector<bool> visited(n);
        function<void(int, int)> dfs = [&] (int v, int p) {
            visited[v] = true;
            for(auto to : g[v]) {
                if(to == p || visited[to]) continue;
                dfs(to, v);
            }
        };

        int ans = 0;
        for(int i = 0; i < n; ++i) {
            if(visited[i]) continue;
            ans += 1;
            dfs(i, -1);
        }

        cout << ans << endl;
    }
}
