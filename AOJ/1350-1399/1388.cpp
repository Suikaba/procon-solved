#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using graph = vector<set<pii>>;

void compress_graph(graph& g, int& uid) {
    const int n = g.size();
    queue<int> que;

    // remove leaves
    for(int v = 0; v < n; ++v) {
        if(g[v].size() == 1u) {
            que.push(v);
        }
    }
    while(!que.empty()) {
        const int v = que.front();
        que.pop();
        if(g[v].size() != 1u) continue;
        const auto e = *g[v].begin();
        g[v].clear();
        g[e.first].erase(make_pair(v, e.second));
        if(g[e.first].size() == 1u) {
            que.push(e.first);
        }
    }

    // constraction
    for(int v = 0; v < n; ++v) {
        if(g[v].size() == 2u) {
            que.push(v);
        }
    }
    while(!que.empty()) {
        const int v = que.front();
        que.pop();
        if(g[v].size() != 2u) continue;
        const int a = g[v].begin()->first, a_uid = g[v].begin()->second;
        const int b = next(g[v].begin())->first, b_uid = next(g[v].begin())->second;
        if(a == b) continue; // self-loop
        g[v].clear();
        g[a].erase(make_pair(v, a_uid));
        g[b].erase(make_pair(v, b_uid));
        ++uid;
        g[a].emplace(b, uid);
        g[b].emplace(a, uid);
        if(g[a].size() == 2u) {
            que.push(a);
        }
        if(g[b].size() == 2u) {
            que.push(b);
        }
    }

    map<int, int> eidx;
    graph tg(n);
    for(int v = 0; v < n; ++v) {
        for(auto& e : g[v]) {
            if(eidx.count(e.second) == 0) {
                const int id = eidx.size();
                eidx[e.second] = id;
            }
            tg[v].emplace(e.first, eidx[e.second]);
        }
    }
    g = move(tg);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    graph g(n);
    int uid = 0;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        a--, b--;
        g[a].emplace(b, uid);
        g[b].emplace(a, uid);
        uid += 1;
    }
    compress_graph(g, uid);

    set<ll> cycles;
    for(int s = 0; s < n; ++s) {
        if(g[s].empty()) continue;
        vector<bool> used_v(n);
        function<void(int, ll)> dfs = [&] (int v, ll used_edge) {
            used_v[v] = true;
            for(auto const& e : g[v]) {
                if(used_edge & (1LL << e.second)) continue;
                used_edge ^= 1LL << e.second;
                if(e.first == s) {
                    cycles.insert(used_edge);
                    used_edge ^= 1LL << e.second;
                    continue;
                }
                if(!used_v[e.first]) {
                    dfs(e.first, used_edge);
                }
                used_edge ^= 1LL << e.second;
            }
            used_v[v] = false;
        };
        dfs(s, 0);
    }

    cout << cycles.size() << endl;
}
