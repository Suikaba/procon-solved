#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<bool> used(n);
    priority_queue<int, vector<int>, greater<>> que;
    que.push(0);
    vector<int> ans;
    used[0] = true;
    while(!que.empty()) {
        const int v = que.top(); que.pop();
        ans.push_back(v + 1);
        for(auto to : g[v]) {
            if(used[to]) continue;
            used[to] = true;
            que.push(to);
        }
    }

    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
