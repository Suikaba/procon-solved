#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

using pii = pair<int, int>;

class strongly_connected_component {
    using graph = vector<vector<int>>;
public:
    strongly_connected_component(int n) : g(n), rg(n), cmp(n), K(0) {}

    void add_edge(int s, int t) {
        g[s].push_back(t);
        rg[t].push_back(s);
    }

    void build() {
        const int n = g.size();
        vector<bool> used(n);
        for(int v = 0; v < n; ++v) {
            if(!used[v]) dfs(v, used);
        }
        fill(begin(used), end(used), false);
        int k = 0;
        for(int i = (int)vs.size() - 1; i >= 0; --i) {
            if(!used[vs[i]]) rdfs(vs[i], k++, used);
        }
        K = k;
    }

    int belongs(int v) const { return cmp[v]; }

private:
    void dfs(int v, vector<bool>& used) {
        used[v] = true;
        for(auto to : g[v]) {
            if(!used[to]) dfs(to, used);
        }
        vs.push_back(v);
    }
    void rdfs(int v, int k, vector<bool>& used) {
        used[v] = true;
        cmp[v] = k;
        for(auto to : rg[v]) if(!used[to]) rdfs(to, k, used);
    }

    graph g, rg;
    vector<int> cmp, vs;
    int K;
};

int main() {
    int T; cin >> T;
    while(T--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> g(n);
        strongly_connected_component scc(n);
        for(int i = 0; i < m; ++i) {
            int a, b; cin >> a >> b;
            g[a - 1].push_back(b - 1);
            scc.add_edge(a - 1, b - 1);
        }
        scc.build();

        vector<vector<int>> dist(n, vector<int>(2, inf));
        vector<vector<int>> prev(n, vector<int>(2, -1));
        for(int i = 0; i < n; ++i) {
            if(dist[i][0] != inf || dist[i][1] != inf) continue;
            dist[i][0] = 0;
            queue<pii> que;
            que.emplace(i, 0);
            while(!que.empty()) {
                const int v = que.front().first;
                const int p = que.front().second;
                que.pop();
                for(auto to : g[v]) {
                    if(scc.belongs(v) != scc.belongs(to)) continue;
                    if(dist[to][p ^ 1] == inf) {
                        dist[to][p ^ 1] = dist[v][p] + 1;
                        prev[to][p ^ 1] = v;
                        que.emplace(to, p ^ 1);
                    }
                }
            }
        }

        vector<int> ans;
        for(int i = 0; i < n; ++i) {
            if(dist[i][0] == inf || dist[i][1] == inf) continue;
            int cur_v = i, cur_p = (prev[i][0] != -1 ? 0 : 1);
            while(cur_v != -1) {
                ans.push_back(cur_v);
                cur_v = prev[cur_v][cur_p];
                cur_p ^= 1;
            }
            ans.pop_back();
            reverse(begin(ans), end(ans));
            break;
        }

        if(ans.empty()) {
            cout << -1 << endl;
        } else {
            cout << 1 << endl;
            cout << ans.size() << endl;
            for(auto v : ans) {
                cout << v + 1 << endl;
            }
        }
    }
}
