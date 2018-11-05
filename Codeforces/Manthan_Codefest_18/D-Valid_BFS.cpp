#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    vector<int> a(n);
    map<int, int> ord;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
        ord[a[i]] = i;
    }

    vector<int> d(n, inf);
    d[0] = 0;
    queue<int> que;
    que.emplace(0);
    vector<int> b;
    while(!que.empty()) {
        const int v = que.front(); que.pop();
        b.push_back(v);
        map<int, int> vs;
        for(auto to : g[v]) {
            if(d[to] != inf) continue;
            d[to] = d[v] + 1;
            vs[ord[to]] = to;
        }
        for(auto& p : vs) {
            que.push(p.second);
        }
    }

    cout << (a == b ? "Yes" : "No") << endl;
}
