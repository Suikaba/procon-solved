
// http://codeforces.com/contest/546/problem/E

#include <bits/stdc++.h>
using namespace std;

using weight = int;

constexpr weight inf = 1e9;

struct edge {
    int to;
    weight cap;
    int rev;
};

using edges = std::vector<edge>;
using graph = std::vector<edges>;

void add_edge(graph& g, int from, int to, weight cap) {
    g[from].push_back(edge{to, cap, static_cast<int>(g[to].size())});
    g[to].push_back(edge{from, 0, static_cast<int>(g[from].size()-1)});
}

void bfs(graph& g, std::vector<int>& level, int s) {
    for(int i = 0; i < (int)level.size(); ++i) {
        level[i] = -1;
    }
    level[s] = 0;
    std::queue<int> que;
    que.push(s);
    while(!que.empty()) {
        int v = que.front(); que.pop();
        for(int i = 0; i < (int)g[v].size(); ++i) {
            edge& e = g[v][i];
            if(e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

weight dfs(graph& g, std::vector<int>& level, std::vector<int>& iter, int v, int t, weight f) {
    if(v == t) {
        return f;
    }
    for(int& i = iter[v]; i < (int)g[v].size(); ++i) {
        edge& e = g[v][i];
        if(e.cap > 0 && level[v] < level[e.to]) {
            weight d = dfs(g, level, iter, e.to, t, std::min(f, e.cap));
            if(d > 0) {
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

weight max_flow(graph& g, int s, int t) {
    weight flow = 0;
    std::vector<int> level(g.size(), -1);
    std::vector<int> iter(g.size(), 0);
    weight INF = 1e9;
    while(true) {
        bfs(g, level, s);
        if(level[t] < 0) {
            return flow;
        }
        for(int i = 0; i < (int)iter.size(); ++i) {
            iter[i] = 0;
        }
        weight f;
        while((f = dfs(g, level, iter, s, t, INF)) > 0) {
            flow += f;
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    const int asum = accumulate(begin(a), end(a), 0);
    const int bsum = accumulate(begin(b), end(b), 0);
    if(asum != bsum) {
        cout << "NO" << endl;
        return 0;
    }

    const int source = 2 * n, sink = 2 * n + 1;
    graph g(2 * n + 2);
    for(int i = 0; i < m; ++i) {
        int p, q;
        cin >> p >> q;
        p--; q--;
        add_edge(g, p, q + n, inf);
        add_edge(g, q, p + n, inf);
    }
    for(int i = 0; i < n; ++i) {
        add_edge(g, source, i, a[i]);
        add_edge(g, i + n, sink, b[i]);
        add_edge(g, i, i + n, inf);
    }

    auto f = max_flow(g, source, sink);
    if(f != asum) {
        cout << "NO" << endl;
    } else {
        vector<vector<int>> ans(n, vector<int>(n));
        for(int i = 0; i < n; ++i) {
            for(auto& e : g[i]) {
                if(e.to == source) continue;
                assert(e.to - n >= 0 && e.to - n < n);
                ans[i][e.to - n] = inf - e.cap;
            }
        }
        cout << "YES" << endl;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                cout << ans[i][j] << " \n"[j + 1 == n];
            }
        }
    }
}
