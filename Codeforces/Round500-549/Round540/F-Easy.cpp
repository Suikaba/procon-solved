#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> col(n);
    for(int i = 0; i < n; ++i) {
        cin >> col[i];
    }
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }

    vector<int> bsum(n), rsum(n);
    function<void(int, int)> dfs = [&] (int v, int p) {
        rsum[v] = col[v] == 1;
        bsum[v] = col[v] == 2;
        for(auto to : g[v]) {
            if(to == p) continue;
            dfs(to, v);
            rsum[v] += rsum[to];
            bsum[v] += bsum[to];
        }
    };
    dfs(0, -1);

    function<int(int, int)> solve = [&] (int v, int p) {
        int res = 0;
        for(auto to : g[v]) {
            if(to == p) continue;
            res += (rsum[to] == rsum[0] && bsum[to] == 0) || (rsum[to] == 0 && bsum[to] == bsum[0]);
            res += solve(to, v);
        }
        return res;
    };

    cout << solve(0, -1) << endl;
}
