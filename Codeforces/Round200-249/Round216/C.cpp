#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to;
    bool broken;
};

using graph = vector<vector<edge>>;

int main() {
    int n; cin >> n;
    graph g(n);
    for(int i = 0; i < n - 1; ++i) {
        int x, y, t; cin >> x >> y >> t;
        g[x - 1].push_back(edge{y - 1, t == 2});
        g[y - 1].push_back(edge{x - 1, t == 2});
    }

    function<vector<int>(int, int)> solve = [&] (int v, int p) {
        vector<int> res;
        for(const auto& e : g[v]) {
            if(e.to == p) continue;
            auto vs = solve(e.to, v);
            if(e.broken && vs.empty()) {
                vs.push_back(e.to + 1);
            }
            if(vs.empty()) continue;
            if(res.size() < vs.size()) swap(res, vs);
            for(auto u : vs) res.push_back(u);
        }
        return res;
    };

    const auto ans = solve(0, -1);
    cout << ans.size() << endl;
    for(int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
    }
}
