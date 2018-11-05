#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to, cap, rev;
};

using graph = vector<vector<edge>>;

void add_edge(graph& g, int from, int to, int cap) {
    g[from].push_back(edge{to, cap, static_cast<int>(g[to].size())});
    g[to].push_back(edge{from, 0, static_cast<int>(g[from].size() - 1)});
}

void bfs(graph& g, vector<int>& level, int s) {
    for(int i = 0; i < (int)level.size(); ++i) {
        level[i] = -1;
    }
    level[s] = 0;
    queue<int> que;
    que.push(s);
    while(!que.empty()) {
        int v = que.front(); que.pop();
        for(int i = 0; i < (int)g[v].size(); ++i) {
            auto& e = g[v][i];
            if(e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

int dfs(graph& g, vector<int>& level, vector<int>& iter, int v, int t, int f) {
    if(v == t) return f;
    for(int& i = iter[v]; i < (int)g[v].size(); ++i) {
        auto& e = g[v][i];
        if(e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(g, level, iter, e.to, t, min(f, e.cap));
            if(d > 0) {
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(graph& g, int s, int t) {
    int flow = 0;
    vector<int> level(g.size(), -1);
    vector<int> iter(g.size(), 0);
    int inf = 1e9;
    while(true) {
        bfs(g, level, s);
        if(level[t] < 0) return flow;
        for(int i = 0; i < (int)iter.size(); ++i) {
            iter[i] = 0;
        }
        int f = 0;
        while((f = dfs(g, level, iter, s, t, inf)) > 0) {
            flow += f;
        }
    }
}

int main() {
    int n, m;
    while(cin >> n >> m) {
        using E = tuple<int, int, int>;
        vector<E> es;
        for(int i = 0; i < m; ++i) {
            int u, v, cost;
            cin >> u >> v >> cost;
            es.emplace_back(cost, u - 1, v - 1);
        }
        sort(begin(es), end(es));

        int ans = 0;
        for(int i = 0; i < m; ++i) {
            graph g(n);
            for(int j = 0; get<0>(es[j]) < get<0>(es[i]); ++j) {
                add_edge(g, get<1>(es[j]), get<2>(es[j]), 1);
                add_edge(g, get<2>(es[j]), get<1>(es[j]), 1);
            }
            ans += max_flow(g, get<1>(es[i]), get<2>(es[i]));
        }

        cout << ans << endl;
    }
}
