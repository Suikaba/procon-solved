#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/696/problem/B

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int par;
        cin >> par;
        g[par - 1].push_back(i + 1);
    }

    vector<int> sz(n);
    vector<double> ans(n);
    function<int(int)> dfs = [&](int v) {
        sz[v] = 1;
        for(auto to : g[v]) {
            sz[v] += dfs(to);
        }
        return sz[v];
    };
    function<void(int)> solve = [&](int v) {
        if(v == 0) ans[v] = 1;
        int sum = 0;
        for(auto to : g[v]) {
            sum += sz[to];
        }
        for(auto to : g[v]) {
            ans[to] = ans[v] + (sum - sz[to]) / 2.0 + 1;
            solve(to);
        }
    };
    dfs(0);
    solve(0);

    cout << fixed << setprecision(10);
    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
