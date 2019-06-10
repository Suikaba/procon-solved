#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    vector<set<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        g[u - 1].insert(v - 1);
        g[v - 1].insert(u - 1);
    }

    queue<int> que;
    for(int i = 0; i < n; ++i) {
        if(g[i].size() == 2u) {
            que.push(i);
        }
    }

    while(!que.empty()) {
        const auto v = que.front(); que.pop();
        if(g[v].size() != 2u) continue;
        const int a = *g[v].begin(), b = *next(g[v].begin());
        g[v].clear();
        g[a].erase(v);
        g[b].erase(v);
        g[a].insert(b);
        g[b].insert(a);
        if(g[a].size() == 2u) {
            que.push(a);
        }
        if(g[b].size() == 2u) {
            que.push(b);
        }
    }

    int cnt = 0;
    for(auto const& es : g) {
        cnt += es.size();
    }

    cout << (cnt == 2 ? "Yes" : "No") << endl;
}

