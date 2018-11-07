#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, d, k; cin >> n >> d >> k;

    if(n <= d || (k == 1 && d >= 2)) {
        cout << "NO" << endl;
        return 0;
    }

    int viter = 1;
    vector<pii> ans;
    vector<vector<int>> g(n + 1);
    auto add_edge = [&] (int from, int to) {
        g[from].push_back(to);
        g[to].push_back(from);
        ans.emplace_back(from, to);
    };
    function<void(int, int)> sub_tree = [&] (int v, int dlimit) {
        if(dlimit <= 0) return;
        while(viter < n && (int)g[v].size() < k) {
            add_edge(v, ++viter);
            sub_tree(viter, dlimit - 1);
        }
    };
    function<void(int, int, int)> dfs = [&] (int v, int p, int depth) {
        for(auto to : g[v]) {
            if(to == p) continue;
            dfs(to, v, depth + 1);
        }
        if(min(d - depth, depth) <= 0) return;
        while(viter < n && (int)g[v].size() < k) {
            add_edge(v, ++viter);
            sub_tree(viter, min(d - depth, depth) - 1);
        }
    };
    for(int i = 0; i < d; ++i, ++viter) {
        add_edge(viter, viter + 1);
    }
    dfs(1, -1, 0);

    if((int)ans.size() != n - 1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for(auto& e : ans) {
            cout << e.first << ' ' << e.second << endl;
        }
    }
}
