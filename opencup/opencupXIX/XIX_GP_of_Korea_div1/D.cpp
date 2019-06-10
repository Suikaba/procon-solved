#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

vector<int> topo(vector<vector<int>> const& g) {
    const int n = g.size();
    vector<int> in(n);
    for(int i = 0; i < n; ++i) {
        for(auto to : g[i]) {
            in[to] += 1;
        }
    }

    vector<int> s;
    for(int i = 0; i < n; ++i) {
        if(in[i] == 0) {
            s.push_back(i);
        }
    }

    vector<int> res;
    while(!s.empty()) {
        const int v = s.back();
        s.pop_back();
        res.push_back(v);
        for(auto to : g[v]) {
            --in[to];
            if(in[to] == 0) {
                s.push_back(to);
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        if(in[i] != 0) return {};
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    vector<int> l(n), r(n);
    for(int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
    }
    vector<vector<int>> g(n), rg(n);
    vector<int> in(n);
    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        g[u - 1].push_back(v - 1);
        rg[v - 1].push_back(u - 1);
        in[v - 1] += 1;
    }

    const auto ord = topo(g);
    if(ord.empty()) {
        cout << -1 << endl;
        return 0;
    }

    for(int i = 0; i < n; ++i) {
        const int v1 = ord[i];
        for(auto to : g[v1]) {
            l[to] = max(l[to], l[v1] + 1);
        }
        const int v2 = ord[n - i - 1];
        for(auto from : rg[v2]) {
            r[from] = min(r[from], r[v2] - 1);
        }
    }

    vector<vector<int>> lv(n + 1);
    for(int v = 0; v < n; ++v) {
        if(l[v] > r[v]) {
            cout << -1 << endl;
            return 0;
        }
        lv[l[v]].push_back(v);
    }

    priority_queue<pii, vector<pii>, greater<>> que;
    vector<int> ans(n);
    for(int i = 1; i <= n; ++i) {
        for(auto v : lv[i]) que.emplace(r[v], v);
        if(que.empty()) {
            cout << -1 << endl;
            return 0;
        }
        const auto [limit, v] = que.top();
        que.pop();
        if(limit < i) {
            cout << -1 << endl;
            return 0;
        }
        ans[i - 1] = v + 1;
    }

    for(auto v : ans) {
        cout << v << "\n";
    }
}
