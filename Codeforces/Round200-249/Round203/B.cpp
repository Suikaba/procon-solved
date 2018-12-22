#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> k(n);
    for(int i = 0; i < n; ++i) cin >> k[i];
    vector<vector<int>> rg(n);
    vector<int> out_deg(n);
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        if(a == 0) continue;
        rg[i].push_back(a - 1);
        out_deg[a - 1] += 1;
    }
    vector<bool> used(n);
    for(int i = 0; i < n; ++i) {
        if(out_deg[i] >= 2) used[i] = true;
    }

    vector<int> ans;
    for(int i = 0; i < n; ++i) {
        if(k[i] == 0) continue;
        vector<int> tpath;
        function<void(int)> dfs = [&] (int v) {
            used[v] = true;
            tpath.push_back(v);
            bool extend = false;
            for(auto to : rg[v]) {
                if(used[to]) continue;
                dfs(to);
                extend = true;
            }
            if(!extend && ans.size() < tpath.size()) {
                ans = move(tpath);
            }
        };
        dfs(i);
    }
    reverse(begin(ans), end(ans));
    const int sz = ans.size();
    cout << sz << endl;
    for(int i = 0; i < sz; ++i) {
        cout << ans[i] + 1 << " \n"[i + 1 == sz];
    }
}
