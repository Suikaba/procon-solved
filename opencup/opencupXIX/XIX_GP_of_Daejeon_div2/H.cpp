#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using graph = std::vector<std::vector<int>>;

// require: input graph is bipartite
class bipartite_matching {
public:
    bipartite_matching(graph const& g)
        : g_(g), match_(g.size(), -1), used_(g.size(), false)
    {}

    int solve() {
        const int n = g_.size();
        int res = 0;
        bool update = true;
        while(update) {
            update = false;
            for(int v = 0; v < n; ++v) {
                if(match_[v] == -1 && dfs(v)) {
                    update = true;
                    ++res;
                }
            }
            if(update) std::fill(used_.begin(), used_.end(), false);
        }
        return res;
    }

    int match(int v) const {
        return match_[v];
    }

private:
    bool dfs(int v) {
        if(used_[v]) return false;
        used_[v] = true;
        for(auto u : g_[v]) {
            if(match_[u] < 0 || dfs(match_[u])) {
                match_[u] = v;
                match_[v] = u;
                return true;
            }
        }
        return false;
    }

private:
    graph g_;
    std::vector<int> match_;
    std::vector<bool> used_;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    graph g(n + n - 1);
    map<pii, int> eidx;
    for(int i = 0; i < m; ++i) {
        int s, t; cin >> s >> t;
        s--, t--;
        g[s].push_back(t + n - 1);
        g[t + n - 1].emplace_back(s); // edge for search
        eidx[make_pair(s, t + n - 1)] = i;
    }
    bipartite_matching bm(g);
    if(bm.solve() != n - 1) {
        cout << -1 << endl;
        return 0;
    }

    vector<vector<int>> ts(n - 1), to_s(n);
    { // search two students for each teacher
        vector<bool> is_in(n - 1);
        function<void(int, bool)> dfs = [&] (int v, bool is_s) {
            if(is_s) {
                const int to = bm.match(v);
                ts[v].push_back(to - (n - 1));
                to_s[to - (n - 1)].push_back(v);
                dfs(to, false);
            } else {
                for(auto const to : g[v]) {
                    if(is_in[to]) continue;
                    is_in[to] = true;
                    ts[to].push_back(v - (n - 1));
                    to_s[v - (n - 1)].push_back(to);
                    dfs(to, true);
                }
            }
        };
        for(int i = 0; i < n; ++i) {
            if(bm.match(i + n - 1) == -1) {
                dfs(i + n - 1, false);
                break;
            }
        }
        for(int i = 0; i < n - 1; ++i) {
            if(ts[i].size() != 2u) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    graph g2(n);
    vector<int> remain(n - 1, n), ans(m);
    for(int i = 0; i < n - 1; ++i) {
        g2[ts[i][0]].push_back(ts[i][1]);
        g2[ts[i][1]].push_back(ts[i][0]);
    }
    function<int(int, int)> solve = [&] (int v, int p) {
        int cur = 0;
        for(auto to : g2[v]) {
            if(to == p) continue;
            const int u = solve(to, v);
            const int idx = eidx[make_pair(u, v + n - 1)];
            ans[idx] = remain[u];
            cur += remain[u];
            remain[u] = 0;
        }
        int res = -1;
        for(auto const to : to_s[v]) {
            if(remain[to] == 0) continue;
            const int idx = eidx[make_pair(to, v + n - 1)];
            ans[idx] = min(n - 1 - cur, remain[to]);
            remain[to] -= ans[idx];
            res = to;
        }
        return res;
    };
    solve(0, -1);

    for(int i = 0; i < m; ++i) {
        cout << ans[i] << "\n";
    }
}