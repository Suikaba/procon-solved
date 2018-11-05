#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(m), b(m);
    vector<set<int>> g(n);
    for(int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
        g[a[i]].insert(b[i]);
        g[b[i]].insert(a[i]);
    }

    int cur = n;
    vector<int> ans(m);
    vector<bool> erased(n);
    queue<int> que;
    for(int i = 0; i < n; ++i) {
        if((int)g[i].size() < k) {
            que.push(i);
            erased[i] = true;
        }
    }
    for(int i = m - 1; i >= 0; --i) {
        while(!que.empty()) {
            auto v = que.front(); que.pop();
            cur--;
            for(auto to : g[v]) {
                if(erased[to]) continue;
                g[to].erase(v);
                if((int)g[to].size() < k) {
                    que.push(to);
                    erased[to] = true;
                }
            }
            g[v].clear();
        }
        ans[i] = cur;
        if(g[a[i]].count(b[i])) {
            g[a[i]].erase(b[i]);
            if((int)g[a[i]].size() < k) {
                que.push(a[i]);
                erased[a[i]] = true;
            }
        }
        if(g[b[i]].count(a[i])) {
            g[b[i]].erase(a[i]);
            if((int)g[b[i]].size() < k) {
                que.push(b[i]);
                erased[b[i]] = true;
            }
        }
    }

    for(auto x : ans) {
        cout << x << endl;
    }
}
