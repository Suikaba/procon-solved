#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

struct edge {
    int from, to, idx;
    edge(int s, int t, int i) : from(s), to(t), idx(i) {}
};

using graph = vector<vector<edge>>;

int main() {
    int n, m, k; cin >> n >> m >> k;
    graph g(n);
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        g[a - 1].emplace_back(a - 1, b - 1, i);
        g[b - 1].emplace_back(b - 1, a - 1, i);
    }

    vector<int> d(n, inf);
    vector<vector<int>> prev(n);
    queue<int> que;
    que.push(0);
    d[0] = 0;
    while(!que.empty()) {
        const auto v = que.front(); que.pop();
        for(auto& e : g[v]) {
            if(d[e.to] < d[v] + 1) continue;
            prev[e.to].push_back(e.idx);
            if(d[e.to] > d[v] + 1) {
                d[e.to] = d[v] + 1;
                que.push(e.to);
            }
        }
    }

    vector<string> ans;
    string s(m, '0');
    function<void(int)> dfs = [&] (int v) {
        if((int)ans.size() >= k) return;
        if(v == 0) {
            ans.push_back(s);
            return;
        }
        for(auto j : prev[v]) {
            s[j] = '1';
            dfs(v - 1);
            s[j] = '0';
        }
    };
    dfs(n - 1);

    cout << ans.size() << endl;
    for(auto& t : ans) {
        cout << t << endl;
    }
}
