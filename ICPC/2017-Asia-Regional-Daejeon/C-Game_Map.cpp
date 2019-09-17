#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n, m;
    while(cin >> n >> m) {
        vector<vector<int>> g(n);
        vector<pii> deg(n, make_pair(0, 0));
        for(int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            deg[u].first += 1;
            deg[v].first += 1;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for(int i = 0; i < n; ++i) {
            deg[i].second = i;
        }
        sort(begin(deg), end(deg));

        vector<int> ans(n);
        for(int i = 0; i < n; ++i) {
            const int fst = deg[i].second;
            if(ans[fst] != 0) continue;
            using S = tuple<int, int, int>;
            priority_queue<S, vector<S>, greater<S>> que;
            que.emplace(deg[i].first, -1, fst);
            ans[fst] = -1;
            while(!que.empty()) {
                int cur_d, cur_ans, v;
                tie(cur_d, cur_ans, v) = que.top(); que.pop();
                if(ans[v] < cur_ans) continue;
                for(auto to : g[v]) {
                    if(cur_d < (int)g[to].size() && ans[to] > cur_ans - 1) {
                        ans[to] = cur_ans - 1;
                        que.emplace(g[to].size(), cur_ans - 1, to);
                    }
                }
            }
        }

        cout << -*min_element(begin(ans), end(ans)) << endl;
    }
}
