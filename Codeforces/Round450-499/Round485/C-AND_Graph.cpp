#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<bool> appear(1 << n);
    for(int i = 0; i < m; ++i) {
        int a; cin >> a;
        appear[a] = true;
    }

    vector<bool> used(1 << (n + 1));
    function<void(int)> dfs = [&] (int v) {
        used[v] = true;
        if(v & (1 << n)) {
            int nv = (1 << (n + 1)) - 1 - v;
            if(!used[nv] && appear[nv]) {
                dfs(nv);
            }
            for(int i = 0; i < n; ++i) {
                if(used[v | (1 << i)]) continue;
                dfs(v | (1 << i));
            }
        } else {
            if(used[v | (1 << n)]) return;
            used[v | (1 << n)] = true;
            dfs(v | (1 << n));
        }
    };

    int ans = 0;
    for(int i = 0; i < (1 << n); ++i) {
        if(appear[i] && !used[i]) {
            dfs(i);
            ans += 1;
        }
    }

    cout << ans << endl;
}
