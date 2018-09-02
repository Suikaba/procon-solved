
// http://codeforces.com/contest/557/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }

    {
        int max_deg = 0;
        for(int i = 0; i < n; ++i) {
            max_deg = max(max_deg, (int)g[i].size());
        }
        if(max_deg == 0) {
            cout << 3 << ' ' << 1LL * n * (n - 1) * (n - 2) / 6 << endl;
            return 0;
        } else if(max_deg == 1) {
            ll cnt = 0;
            for(int i = 0; i < n; ++i) {
                cnt += g[i].size() == 1u;
            }
            cnt /= 2;
            cout << 2 << ' ' << (n - 2) * cnt << endl;
            return 0;
        }
    }

    vector<int> col(n, -1);
    function<bool(int, int, int, vector<int>&)> coloring = [&] (int v, int p, int c, vector<int>& cnt) {
        if(col[v] != -1 && col[v] != c) return true; // not bipartite
        if(col[v] != -1) return false;
        col[v] = c;
        cnt[c] += 1;
        bool res = false;
        for(auto to : g[v]) {
            if(to == p) continue;
            res |= coloring(to, v, !c, cnt);
        }
        return res;
    };

    ll w = 0;
    for(int i = 0; i < n; ++i) {
        if(col[i] == -1) {
            vector<int> cnt(2);
            if(coloring(i, -1, 0, cnt)) {
                cout << 0 << ' ' << 1 << endl;
                return 0;
            }
            w += 1LL * cnt[0] * (cnt[0] - 1) / 2;
            w += 1LL * cnt[1] * (cnt[1] - 1) / 2;
        }
    }

    cout << 1 << ' ' << w << endl;
}
