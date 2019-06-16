#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while(cin >> n >> m) {
        vector<int> s(n);
        for(int i = 0; i < n; ++i) {
            cin >> s[i];
        }
        vector<set<int>> g(n);
        int ans = 0;
        for(int i = 0; i < m; ++i) {
            int a, b; cin >> a >> b;
            a--, b--;
            g[a].insert(b);
            g[b].insert(a);
            ans = max(ans, s[a] + s[b]);
        }

        for(int v1 = 0; v1 < n; ++v1) {
            for(auto v2 : g[v1]) {
                set<int> common;
                set_intersection(g[v1].begin(), g[v1].end(), g[v2].begin(), g[v2].end(), inserter(common, common.begin()));
                for(auto v3 : common) {
                    ans = max(ans, s[v1] + s[v2] + s[v3]);
                    set<int> c2;
                    set_intersection(common.begin(), common.end(), g[v3].begin(), g[v3].end(), inserter(c2, c2.begin()));
                    for(auto v4 : c2) {
                        ans = max(ans, s[v1] + s[v2] + s[v3] + s[v4]);
                    }
                }
            }
        }

        cout << ans << endl;
    }
}
