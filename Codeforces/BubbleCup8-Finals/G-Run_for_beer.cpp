#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

constexpr int inf = 1e9;

struct edge {
    int to, cost;
};

using graph = vector<vector<edge>>;

int main() {
    int n, m; cin >> n >> m;
    graph g(n);
    for(int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        g[a].push_back(edge{b, c});
        g[b].push_back(edge{a, c});
    }
    vector<int> to(n, -1), len(n, inf);
    {
        queue<int> que;
        que.push(n - 1);
        len[n - 1] = 0;
        while(!que.empty()) {
            const auto v = que.front(); que.pop();
            for(auto& e : g[v]) {
                if(e.cost != 0 || len[e.to] != inf) continue;
                to[e.to] = v;
                len[e.to] = len[v] + 1;
                que.push(e.to);
            }
        }
    }

    using S = tuple<int, int, int, int>;
    priority_queue<S, vector<S>, greater<>> que;
    que.emplace(0, 0, len[0], 0);
    vector<pii> d(n, make_pair(inf, inf));
    d[0] = make_pair(0, 0);
    vector<vector<pii>> prev(n);
    int last_v = -1;
    while(!que.empty()) {
        int dn, pre_d, zero_len, v;
        tie(dn, pre_d, zero_len, v) = que.top(); que.pop();
        if(d[v] < make_pair(dn, pre_d)) continue;
        if(to[v] != -1 || v == n - 1) { // answer
            last_v = v;
            break;
        }
        for(auto& e : g[v]) {
            if(d[e.to] > make_pair(dn + 1, e.cost)) {
                d[e.to] = make_pair(dn + 1, e.cost);
                prev[e.to].clear();
                prev[e.to].emplace_back(v, e.cost);
                que.emplace(dn + 1, e.cost, len[e.to], e.to);
            } else if(d[e.to] == make_pair(dn + 1, e.cost)) {
                prev[e.to].emplace_back(v, e.cost);
            }
        }
    }

    string ans;
    vector<int> cur = {last_v}, prev2(n, -1);
    while(!cur.empty()) {
        int mini = 10;
        vector<int> nxt;
        for(auto v : cur) {
            for(auto& p : prev[v]) {
                if(mini > p.second) {
                    mini = p.second;
                    nxt.clear();
                    nxt.push_back(p.first);
                    prev2[p.first] = v;
                } else if(mini == p.second) {
                    prev2[p.first] = v;
                    nxt.push_back(p.first);
                }
            }
        }
        if(mini != 10) {
            ans += mini + '0';
        }
        cur = move(nxt);
    }
    if(ans.empty()) ans = "0";
    vector<int> path;
    {
        int now = 0;
        while(now != -1) {
            path.push_back(now);
            now = prev2[now];
        }
        now = last_v;
        while(to[now] != -1) {
            path.push_back(to[now]);
            now = to[now];
        }
    }

    const int sz = path.size();
    cout << ans << endl;
    cout << sz << endl;
    for(int i = 0; i < sz; ++i) {
        cout << path[i] << " \n"[i + 1 == sz];
    }
}
