#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

struct edge {
    int from, to;
    edge(int f, int t) : from(f), to(t) {}
};

using edges = vector<edge>;
using graph = vector<edges>;

vector<int> scc(const graph& g) {
    const int n = g.size();
    int idx = 0, k = 0, s = 0;
    vector<int> ord(n, -1), low(n), onS(n), cmp(n), stk(n);
    function<void(int)> dfs =
        [&] (int v) {
            ord[v] = low[v] = idx++;
            stk[s++] = v;
            onS[v] = true;
            for(auto& e : g[v]) {
                int w = e.to;
                if(ord[w] == -1) {
                    dfs(w);
                    low[v] = min(low[v], low[w]);
                } else if(onS[w]) {
                    low[v] = min(low[v], ord[w]);
                }
            }
            if(low[v] == ord[v]) {
                while(true) {
                    int w = stk[--s];
                    onS[w] = false;
                    cmp[w] = k;
                    if(w == v) break;
                }
                ++k;
            }
        };
    for(int v = 0; v < n; ++v) {
        if(ord[v] == -1) dfs(v);
    }
    return cmp;
}

int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        graph g(n);
        for(int i = 0; i < n; ++i) {
            int p; cin >> p;
            g[i].push_back(edge{i, p - 1});
        }
        auto cmp = scc(g);
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            if(cmp[i] != cmp[g[i][0].to]) ans += 1;
        }
        cout << ans << endl;
    }
}
