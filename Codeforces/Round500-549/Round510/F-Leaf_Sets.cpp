#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    int root = 0;
    for(int i = 0; i < n; ++i) {
        if(g[i].size() != 1u) root = i;
    }

    int ans = 0;
    function<int(int, int)> solve = [&] (int v, int p) {
        if(g[v].size() == 1u) return 0;
        vector<int> vs;
        for(auto to : g[v]) {
            if(to == p) continue;
            vs.push_back(solve(to, v) + 1);
        }
        sort(begin(vs), end(vs));
        while(vs.size() >= 2u && vs.back() + vs[vs.size() - 2] > k) {
            ++ans;
            vs.pop_back();
        }
        return vs.back();
    };
    solve(root, -1);

    cout << ans + 1 << endl;
}
